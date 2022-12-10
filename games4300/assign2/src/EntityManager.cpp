#include "EntityManager.h"

#include <algorithm>          // remove_if


EntityManager::EntityManager() :
   m_entities(),        // calling default constructor due to 
                        // -Weffc++ warning when not included 
                        // in initialiazation list
   m_toAdd(),
   m_entityMap(),
   m_totalEntities(0) 
{

}

std::ostream& operator << (std::ostream& os, const EntityManager& em)
{
   os << "total Entities: " << em.m_totalEntities << "\n";

   os << "m_entities\n";
   os << "   capacity: " << em.m_entities.capacity() << "\n";
   os << "   size:     " << em.m_entities.size() << "\n";
   os << "   data:     " << em.m_entities.data() << "\n";

   return os;
}


std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
   /* create a new Entity object
      give each entity an increasing integer id
      
      Cannot use make_shared because Entity has private constructor 
      auto e = std::make_shared<Entity>(tag, m_totalEntities++);
   */
   auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));

   // store new entity in the vector of all new entities to be added later
   m_toAdd.push_back(e);

   // return the shared pointer pointing to that entry
   return e;
}


/* Iterator Invalidation

   - Caused by modifying the contents of a collection as we are iterating through it.
   - Happens all the time in games
      - Adding: while iterating through all entities to check for collisions, and explosion happens
        and we spawn an explosion entity. The behavior is undefined. May crash, may work.
      - Removing: iterating to check collisions, one dies, so we remove it.

   - Vector functions may cause reallocation
      - Adding to vector: push_back, insert, etc
      - Vector may resize, recreating the internal array
      - Invalidates all pointers and iterators

   - Erasing elements may invalidate too
      - Remove from vector: erase, pop_back
      - Invalidates the iterators and references at or after the point of erasing in the internal array

*/

/* Returns true when Entity is not active
*/
/* bool EntityManager::remove_entity(Entity const &e)
{ 
   return !(e.isActive());
}*/



/* Delayed Effects

   One way to avoid iterator invalidations is to delay the effects of actions that modify collections
   until it is safe to do so.

   With the EntityManager handling Entity creation and destruction, this becomes easy

   Idea: Only add or remove entities at the beginning of a frame when it is safe
*/

// called at beginning of each frame by game engine
// entities added will now be available to use this frame
void EntityManager::update()
{
   // Add new entities 
   for(auto e : m_toAdd)
   {
      m_entities.push_back(e);
      
      // store it in the map of tag->entityVector
      // if the tag does not already exist in the map, it will automatically be added
      // m_entityMap[tag].push_back(e);
      m_entityMap[e->tag()].push_back(e);
   }

   m_toAdd.clear();  // clear list of entities to add 

   // Remove inactive entities from m_entities
   /* m_entities.erase(
      std::remove_if(m_entities.begin(), m_entities.end(), remove_entity),
      m_entities.end());
   */

   // Remove inactive entities from m_entityMap;
   // iterate through the map by tag
   /*
   for(auto it = m_entityMap.begin();  it != m_entityMap.end(); )
   {
      // Access this tag's EntityVectore
      EntityVector ev = it->second;

      // remove inactive Entities within the tag's EntityVector
      ev.erase(
         std::remove_if(ev.begin(), ev.end(), remove_entity),
         ev.end());
     
   } */
}


size_t EntityManager::getTotalEntities()
{ 
   return m_totalEntities;
}



/* Entity Manager Usage example


   EntityManager m_entities;

   void spawnEnemy()
   {
      auto e = m_entities.addEntity("enemy");
      e->cTranform = std::make_shared<CTransform>(args);
      e->cShape = std::make_share<cShape>(args);
   }

   void collisions()
   {
      for(auto b : m_entities.getEntities("bullet"))
      {
         for(auto e : m_entities.getEntities("enemy"))
         {
            // check for collision between bullett and enemy
            if(Physics::CheckCollision(b,e))
            {
               b->destroy();     // destroy bullett
               e->destroy();     // destroy enemy

               the destroy function should simply set the isAlive variable to false.
               Removal will occur later when update is called
            }
         }
      }
   }
*/