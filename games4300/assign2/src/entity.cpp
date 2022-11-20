#include "entity.h"

/* For private class constructors we can no long use
   std::make_shared<Entity>(args)

   A workaround is 
   auto e = std::shared_ptr<Entity>(new Entity(args))

*/
Entity::Entity(const std::string& tag, const size_t id) : 
   m_tag(tag), 
   m_id(id)
{
   // intentionally blank
}

bool Entity::isActive()
{
   return m_active;
}

const std::string & Entity::tag() const
{
   return m_tag;
}

const size_t Entity::id() const
{
   return m_id;
}

void Entity::destroy()
{
   m_active = false;
}