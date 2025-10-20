#include <fstream>
#include <iostream>

#include "../include/randomNumberGenerator.hpp"
#include "../include/gameConfigTest.h"


void GameConfigTest::runTests()
{
    testBulletConfig(1);
    testEnemyConfig();
    testFontConfig();
    testPlayerConfig();
    testWindowConfig();
}

void GameConfigTest::testBulletConfig(int numRandomTests)
{   
    {   
        const char* filename = "configBullet.txt";
        BulletConfig expected = {10, 10, 20, {255, 155, 75}, {50, 90, 150}, 2, 10, 90};
        testReadBulletConfig(filename, expected);
    }

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

    std::string filename = "randomBulletConfig.txt";
    std::string path = GameConfig::CONFIG_DIR_PATH;
    path.append("/");
    path.append(filename);
    
    std::ofstream outfile(path, std::ios::out);
    if(!outfile.is_open())
    {
        std::cerr << "[FILE OPEN FAILURE] " << __func__ 
            << ", file name: " << path << "\n";
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
            << bc.outlineThickness << " "
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
                std::cerr << "\n[ERROR COUNT EXCEEDED] Exiting test\n";
                std::exit(EXIT_FAILURE);
            }
        }
    });
}


BulletConfig GameConfigTest::generateRandomBulletConfig()
{
    BulletConfig bc;
    RandomNumberGenerator rg;

    bc.shapeRadius = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.collisionRadius = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    // round to two decimal places
    bc.speed = std::round(rg.generate(MIN_RANDOM_FLOAT, MAX_RANDOM_FLOAT) * 100.0f) / 100.f;
    bc.fillColor.red = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.fillColor.green = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.fillColor.blue = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.outlineColor.red = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.outlineColor.green = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.outlineColor.blue = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.outlineThickness = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.shapeVertices = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    bc.lifespan = rg.generate(MIN_RANDOM_INT, MAX_RANDOM_INT);
    return bc;
}

void GameConfigTest::testFontConfig()
{
    {   
        const char* filename = "configFont.txt";
        FontConfig expected = {"tech.ttf", 24, {255, 242, 100}};
        testReadFontConfig(filename, expected);
    }
}

void GameConfigTest::testReadFontConfig(const char* filename, const FontConfig& expected)
{
    static int errorCount = 0;

    GameConfig gc;
    if(!gc.readConfigFile(filename))
    {
        std::cerr << "[FILE OPEN FAILURE] filename: " << filename << "\n";
        std::exit(EXIT_FAILURE);
    }

    FontConfig actual = gc.getFontConfig();
    visit_font_members(actual, expected, [](const char* name, auto& actual, auto& expected)
    {
        if(actual != expected)
        {
            ++errorCount;
            std::cerr << "[INEQUALITY ERROR] field name: " << name 
                << ", actual: " << actual << " != "
                << " expected: " << expected << "\n";
            if(errorCount > 1)
            {
                std::cerr << "\n[ERROR COUNT EXCEEDED] Exiting test\n";
                std::exit(EXIT_FAILURE);
            }
        }
    });
}

void GameConfigTest::testEnemyConfig()
{
    {   
        const char* filename = "configEnemy.txt";
        // 32 32 3 8 255 255 255 2 3 8 90 60
        EnemyConfig expected = {32, 32, 3, 8, {255, 255, 255}, 2, 3, 8, 90, 60};
        testReadEnemyConfig(filename, expected);
    }

}

void GameConfigTest::testReadEnemyConfig(const char* filename, const EnemyConfig& expectedConfig)
{
    static int errorCount = 0;

    GameConfig gc;
    if(!gc.readConfigFile(filename))
    {
        std::cerr << "[FILE OPEN FAILURE] filename: " << filename << "\n";
        std::exit(EXIT_FAILURE);
    }

    
    EnemyConfig actual = gc.getEnemyConfig();
    visit_enemy_members(actual, expectedConfig, [](const char* name, auto& actual, auto& expected)
    {
        if(actual != expected)
        {
            ++errorCount;
            std::cerr << "[INEQUALITY ERROR] field name: " << name 
                << ", actual: " << actual << " != "
                << " expected: " << expected << "\n";
            if(errorCount > 1)
            {
                std::cerr << "\n[ERROR COUNT EXCEEDED] Exiting test\n";
                std::exit(EXIT_FAILURE);
            }
        }
    });
}



void GameConfigTest::testPlayerConfig()
{
    {   
        const char* filename = "configPlayer.txt";
        PlayerConfig expected = {32, 32, 4, {250, 200, 150}, {255, 255, 255}, 2, 8};
        testReadPlayerConfig(filename, expected);
    }

}

void GameConfigTest::testReadPlayerConfig(const char* filename, const PlayerConfig& expectedConfig)
{
    static int errorCount = 0;

    GameConfig gc;
    if(!gc.readConfigFile(filename))
    {
        std::cerr << "[FILE OPEN FAILURE] filename: " << filename << "\n";
        std::exit(EXIT_FAILURE);
    }

    
    PlayerConfig actual = gc.getPlayerConfig();
    visit_player_members(actual, expectedConfig, [](const char* name, auto& actual, auto& expected)
    {
        if(actual != expected)
        {
            ++errorCount;
            std::cerr << "[INEQUALITY ERROR] field name: " << name 
                << ", actual: " << actual << " != "
                << " expected: " << expected << "\n";
            if(errorCount > 1)
            {
                std::cerr << "\n[ERROR COUNT EXCEEDED] Exiting test\n";
                std::exit(EXIT_FAILURE);
            }
        }
    });
}


void GameConfigTest::testWindowConfig()
{
    {   
        const char* filename = "configWindow.txt";
        WindowConfig expected = {1280U, 720U, 60, 0};
        testReadWindowConfig(filename, expected);
    }
}

void GameConfigTest::testReadWindowConfig(const char* filename, const WindowConfig& expected)
{
    static int errorCount = 0;

    GameConfig gc;
    if(!gc.readConfigFile(filename))
    {
        std::cerr << "[FILE OPEN FAILURE] filename: " << filename << "\n";
        std::exit(EXIT_FAILURE);
    }

    
    WindowConfig actual = gc.getWindowConfig();
    visit_window_members(actual, expected, [](const char* name, auto& actual, auto& expected)
    {
        if(actual != expected)
        {
            ++errorCount;
            std::cerr << "[INEQUALITY ERROR] field name: " << name 
                << ", actual: " << actual << " != "
                << " expected: " << expected << "\n";
            if(errorCount > 1)
            {
                std::cerr << "\n[ERROR COUNT EXCEEDED] Exiting test\n";
                std::exit(EXIT_FAILURE);
            }
        }
    });
}
