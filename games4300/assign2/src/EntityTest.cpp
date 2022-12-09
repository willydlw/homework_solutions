#include "EntityTest.h"
#include "Entity.h"

#include <cassert>


void EntityTest::testDefaultConstructor()
{
	Entity e;
	assert(e.m_tag == "default" && e.m_id == 0 && e.m_active == true);
}

void EntityTest::testConstructor(const std::string& tag, const size_t id)
{
	Entity e(tag, id);
	assert(e.m_tag == tag && e.m_id == id && e.m_active == true);
}
