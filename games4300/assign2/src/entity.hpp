#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>       // shared_ptr
#include <string>



class Entity
{
   private:
      const size_t      m_id     = 0;     // unique identifier
      const std::string m_tag    = "Default";
      bool              m_alive  = true;

      // Ensure safe creation of Entity objects by only allowing
      // them to be created by the EntityManager class

      // Constructor is private to ensure safe creation of Entity objects 
      Entity(const std::string& tag, size_t id);

      // TODO: make EntityManager a friend of Entity so EntityManager has access
      // to Entity's private constructor

 
   public:
      std::shared_ptr<CTransform> cTransform;
      std::shared_ptr<CName>      cName;
      std::shared_ptr<CShape>     cShape;
      std::shared_ptr<CBBox>      cBBox;
   
      

      void destroy() { m_alive = false;}

      const std::string& tag() {return m_tag;}
};

#endif 