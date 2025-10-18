#include "../include/gameConfigTest.h"
#include "../include/myAssert.h"

#include <sstream>




void GameConfigTest::testReadBulletConfig(const char* filename, const BulletConfig& expected)
{
    GameConfig gc;
    if(!gc.readConfigFile(filename))
    {
        std::cerr << "[FILE OPEN FAILURE] filename: " << filename << "\n";
    }

    
    BulletConfig actual = gc.getBulletConfig();
    visit_bullet_members(actual, expected, [](const char* name, auto& actual, auto& expected)
    {
        if(actual != expected)
        {
            std::cerr << "[INEQUALITY ERROR] field name: " << name 
                << ", actual: " << actual << " != "
                << " expected: " << expected << "\n";
            //std::exit(EXIT_FAILURE);
        }
    });
}
