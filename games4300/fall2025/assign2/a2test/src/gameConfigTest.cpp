#include <iostream>


#include "gameConfigTest.h"


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
