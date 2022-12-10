#pragma once 

#include "components.h"
#include <memory>
#include <string>
#include <cstdlib>         // size_t
#include <iostream>

#define ENTITY_TEST 1

class Entity
{
   #ifdef ENTITY_TEST
      friend class EntityTest;
   #endif

   friend class EntityManager;

   std::string    m_tag;
   size_t         m_id;
   bool           m_active;

   Entity();
  
   // constructor is private so that only the friend EntityManager 
   // can construct Entity objects
   Entity(const std::string& tag, size_t id);

   public:

      // component pointers
      std::shared_ptr<CTransform>      cTransform;
      std::shared_ptr<CShape>          cShape;
      std::shared_ptr<CCollision>      cCollision;
      std::shared_ptr<CScore>          cScore;
      std::shared_ptr<CLifespan>       cLifespan;
      std::shared_ptr<CInput>          cInput;

      // private member access functions 
      bool isActive() const;
      const std::string & tag() const;
      size_t id() const;
      void destroy();

      friend std::ostream& operator << (std::ostream& os, const Entity &entity);
};