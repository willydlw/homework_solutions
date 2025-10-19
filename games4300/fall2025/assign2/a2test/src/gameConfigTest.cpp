#include <fstream>
#include <iostream>

#include "../include/randomNumberGenerator.hpp"
#include "../include/gameConfigTest.h"


void GameConfigTest::runTests()
{
    testBulletConfig(5);
}

void GameConfigTest::testBulletConfig(int numRandomTests)
{   
    #if 0
    {   
        const char* filename = "configBullet.txt";
        BulletConfig expected = {10, 10, 20, {255, 155, 75}, {50, 90, 150}, 2, 10, 90};
        testReadBulletConfig(filename, expected);
    }
    #endif

    {   // random value testing
        for(int i = 0; i < numRandomTests; i++)
        {
            testRandomBulletConfig();
        }
    }
}

void GameConfigTest::testRandomBulletConfig()
{
    // random number testing 
    BulletConfig bc = generateRandomBulletConfig();

    // write to file 
    std::string filename = "randomBulletConfig.txt";
    std::ofstream outfile(filename, std::ios::out);

    if(!outfile.is_open())
    {
        std::cerr << "[FILE OPEN FAILURE] " << __func__ 
            << ", file name: " << filename << "\n";
        std::exit(EXIT_FAILURE);
    }

    outfile << "Bullet " 
            << bc.shapeRadius << " "
            << bc.collisionRadius << " "
            << bc.speed << " "
            << bc.fillColor.red << " "
            << bc.fillColor.green << " "
            << bc.fillColor.blue << " "
            << bc.outlineColor.red << " "
            << bc.outlineColor.green << " "
            << bc.outlineColor.blue << " "
            << bc.outLineThickness << " "
            << bc.shapeVertices << " "
            << bc.lifespan << "\n";
    outfile.close();

    testReadBulletConfig(filename.c_str(), bc);
}

void GameConfigTest::testReadBulletConfig(const char* filename, const BulletConfig& expected)
{
    static int errorCount = 0;

    GameConfig gc;
    if(!gc.readConfigFile(filename))
    {
        std::cerr << "[FILE OPEN FAILURE] filename: " << filename << "\n";
        std::exit(EXIT_FAILURE);
    }

    
    BulletConfig actual = gc.getBulletConfig();
    visit_bullet_members(actual, expected, [](const char* name, auto& actual, auto& expected)
    {
        if(actual != expected)
        {
            ++errorCount;
            std::cerr << "[INEQUALITY ERROR] field name: " << name 
                << ", actual: " << actual << " != "
                << " expected: " << expected << "\n";
            if(errorCount > 1)
            {
                std::exit(EXIT_FAILURE);
            }
        }
    });
}


BulletConfig GameConfigTest::generateRandomBulletConfig()
{
    BulletConfig bc;
    RandomNumberGenerator rg;

    bc.shapeRadius = rg.generate(BulletConfig::MIN_SHAPE_RADIUS, BulletConfig::MAX_SHAPE_RADIUS);
    bc.collisionRadius = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.speed = rg.generate(MIN_RANDOM_FLOAT, MAX_RANDOM_FLOAT);
    bc.fillColor.red = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.fillColor.green = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.fillColor.blue = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.outlineColor.red = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.outlineColor.green = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.outlineColor.blue = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.outLineThickness = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.shapeVertices = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.lifespan = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    return bc;
}
