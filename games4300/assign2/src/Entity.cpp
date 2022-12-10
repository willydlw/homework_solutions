#include "Entity.h"

/* For private class constructors we can no long use
   std::make_shared<Entity>(args)

   A workaround is 
   auto e = std::shared_ptr<Entity>(new Entity(args))

*/

Entity::Entity() : 
   m_tag("default"), 
   m_id(0),
   m_active(true),
   cTransform(nullptr),
   cShape(nullptr),
   cCollision(nullptr),
   cScore(nullptr),
   cLifespan(nullptr),
   cInput(nullptr)
{
   // intentionally blank
}


Entity::Entity(const std::string& tag, size_t id) : 
   m_tag(tag), 
   m_id(id),
   m_active(true),
   cTransform(nullptr),
   cShape(nullptr),
   cCollision(nullptr),
   cScore(nullptr),
   cLifespan(nullptr),
   cInput(nullptr)
{
   // intentionally blank
}

bool Entity::isActive() const
{
   return m_active;
}

const std::string & Entity::tag() const
{
   return m_tag;
}

size_t Entity::id() const
{
   return m_id;
}

void Entity::destroy()
{
   m_active = false;
}


std::ostream& operator << (std::ostream& os, const Entity &entity)
{
   os << "tag:    " << entity.m_tag << "\n"
      << "id:     " << entity.m_id << "\n"
      << "active: " << std::boolalpha << entity.m_active << "\n";

   os << "cTransform\n";
   os << "   use count: " << entity.cTransform.use_count() << "\n";

   os << "cShape\n";
   os << "   use count: " << entity.cShape.use_count() << "\n";

   os << "cCollision\n";
   os << "   use count: " << entity.cCollision.use_count() << "\n";

   os << "cScore\n";
   os << "   use count: " << entity.cScore.use_count() << "\n";

   os << "cLifespan\n";
   os << "   use count: " << entity.cLifespan.use_count() << "\n";

   os << "cInput\n";
   os << "   use count: " << entity.cInput.use_count() << "\n";
   
   return os;
}