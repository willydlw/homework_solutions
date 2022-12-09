#include "testUtility.h"
#include <random>


size_t random_sizet(size_t min, size_t max)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<size_t> range(min, max);
	return range(generator);
}

int random_integer(int min, int max)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<> range(min, max);
	return range(generator);
}


std::string random_string(std::size_t length)
{
	const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::random_device rd; 
	std::mt19937 generator(rd());
	std::uniform_int_distribution<> distribution(0, static_cast<int>(CHARACTERS.size()) - 1);

	std::string rstring;

	for (std::size_t i = 0; i < length; ++i)
	{
		rstring += CHARACTERS[distribution(generator)];
	}

	return rstring;
}