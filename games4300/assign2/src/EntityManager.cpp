#include "EntityManager.h"

#include <algorithm>          // remove_if


EntityManager::EntityManager() :
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
   m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), 
      [](auto &e){return !e->isActive();}), m_entities.end());


   // Compact version of above block removes inactive entities from the map
   for(auto itMap = m_entityMap.begin(); itMap != m_entityMap.end(); ++itMap)
   {
      itMap->second.erase(
        std::remove_if(itMap->second.begin(), itMap->second.end(), [](auto &e){return !e.get()->isActive();}),
         itMap->second.end());
   }

}

EntityVector& EntityManager::getEntities()
{
   return m_entities;
}

EntityVector& EntityManager::getEntities(const std::string& tag)
{
   return m_entityMap.find(tag)->second;
}


size_t EntityManager::getTotalEntities()
{ 
   return m_totalEntities;
}



/* 
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