#include "EntityManagerTest.h"
#include <iostream>

int main()
{
    {
        EntityManagerTest emt;
        emt.testConstructor();
    }

    {
        EntityManagerTest emt;
        emt.testAddEntity();
    }
    return 0;
} 