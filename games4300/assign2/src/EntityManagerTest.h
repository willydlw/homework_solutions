#include "EntityManagerTest.h"
#include "EntityManager.h"
#include "testUtility.h"

#include <cassert>

void EntityManagerTest::testConstructor()
{
	EntityManager em;
	assert(em.m_totalEntities == 0);
}


void EntityManagerTest::testAddEntity()
{
	EntityManager em;
	std::string tag = random_string(4);
	em.addEntity(tag);
	assert(em.m_toAdd.size() == 1 && em.getTotalEntities() == 1);
	std::cout << em << std::endl;

}