#pragma once
#include <string>
#include <cstdlib>		// size_t

class EntityTest
{
public:
	EntityTest() = default;

	void testDefaultConstructor();
	void testConstructor(const std::string& tag, const size_t id);
};
