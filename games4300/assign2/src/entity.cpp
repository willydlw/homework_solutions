#include "entity.h"

/* For private class constructors we can no long use
   std::make_shared<Entity>(args)

   A workaround is 
   auto e = std::shared_ptr<Entity>(new Entity(args))

*/
Entity(const std::string& tag, size_t id) : 
   m_tag(tag), 
   m_id(id)
{
   // intentionally blank
}