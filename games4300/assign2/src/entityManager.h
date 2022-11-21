
/* Entity Manager

   - uses the Factory design pattern
   - handles the creation, storage, and lifetime of all entity objects

   Entity Manager Functions
      - addEntity
      - removeEntity
      - storage
      - bookkeeping

   Factory should somehow ensure that user cannot create its own Entities

*/


/* Data Management

   Separate logic and data
   Create data structures which manage data so your logic code doesn't worry about it
   Complex algorithm shouldn't have to know whether set, vector, map implementation

   Entity Manager will be responsible for data manager

*/


/* Entity Tags

   We may want to group Entities by functionality

   Entity is "tagged" by string
      - Tile, Player, Bullet, Enemy
      Typically in a AAA game tags would be an integer enum type.
      Professor's design decision to use a string for this course
      due to ease of use at this level of learning. Will not cause a 
      bottleneck in slowing code execution.

   Entity Manger should have functionality for quickly getting Entities of a given tag
      Example: loop over all bullets

*/


#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <map>
#include <memory>    // shared_ptr
#include <string>
#include "entity.h"

// Will trade some memory for functionality (ease of use)
// Storing shared_ptr to Entities versus Enity objects
// If we stored vector of Enity objects, then we have to shift
// and copy a lot of dataa when deleting an Entity from the vector
// Faster (less data overhead) when removing entities from the vector.
typedef std::vector<std::shared_ptr<Entity>> EntityVector;

// Will store separate vectors fo Entity objects by their tag for quick retrieval
// We store double the number of pointers to save on computation in the engine
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
   EntityVector   m_entities;
   EntityVector   m_toAdd;                   // waiting room, entity objects to add
   EntityMap      m_entityMap;
   size_t         m_totalEntities = 0;       // total Entities ever created
   bool           remove_entity(const Entity &e); 

public:
   EntityManager();
   void update();
   std::shared_ptr<Entity> addEntity(const std::string& tag);
   EntityVector& getEntities();
   EntityVector& getEntities(const std::string& tag);

};



#endif 