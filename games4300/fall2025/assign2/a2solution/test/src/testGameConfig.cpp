#include "gameConfigTest.h"


void runTests()
{
    {
        const char* filename = "configBullet.txt";
        BulletConfig expected = {10, 10, 255.0f, {155, 75, 50}, {90, 150, 2}, 10, 90, 20};
        GameConfigTest gct; 
        gct.testReadBulletConfig(filename, expected);
    }
}


int main()
{
    runTests();
    return 0;
}