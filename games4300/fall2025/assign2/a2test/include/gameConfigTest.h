#pragma once 

#include "../../a2solution/include/gameConfig.h"

class GameConfigTest 
{
    public:

    static constexpr int MIN_RANDOM_INT = 0;
    static constexpr int MAX_RANDOM_INT = 255;

    static constexpr float MIN_RANDOM_FLOAT = 0.0f;
    static constexpr float MAX_RANDOM_FLOAT = 255.0f;

    GameConfigTest() = default;

    void runTests();
    void testBulletConfig(int numRandomTests);
    void testRandomBulletConfig();
    void testReadBulletConfig(const char* filename, const BulletConfig& expectedConfig);

    void testFontConfig();
    void testReadFontConfig(const char* filename, const FontConfig& expectedConfig);

    void testEnemyConfig();
    void testReadEnemyConfig(const char* filename, const EnemyConfig& expectedConfig);

    void testPlayerConfig();
    void testReadPlayerConfig(const char* filename, const PlayerConfig& expectedConfig);

    void testWindowConfig();
    void testReadWindowConfig(const char* filename, const WindowConfig& expectedConfig);

    private:

    template<typename Visitor>
    void visit_bullet_members(const BulletConfig& a, const BulletConfig& b, Visitor v)
    {
        v("shapeRadius",         a.shapeRadius, b.shapeRadius);
        v("collisionRadius",     a.collisionRadius, b.collisionRadius);
        v("speed",               a.speed, b.speed);
        v("fill color red",      a.fillColor.red, b.fillColor.red);
        v("fill color green",    a.fillColor.green, b.fillColor.green);
        v("fill color blue",     a.fillColor.blue, b.fillColor.blue);
        v("outline color red",   a.outlineColor.red , b.outlineColor.red);
        v("outline color green", a.outlineColor.green, b.outlineColor.green);
        v("outline color blue",  a.outlineColor.blue, b.outlineColor.blue);
        v("outline thickness",   a.outlineThickness, b.outlineThickness);
        v("shape vertices",      a.shapeVertices, b.shapeVertices);
        v("lifespan",            a.lifespan, b.lifespan);
    }

    template<typename Visitor>
    void visit_font_members(const FontConfig& a, const FontConfig& b, Visitor v)
    {
        v("file name",          a.fileName, b.fileName);
        v("height",             a.size, b.size);
        v("color red",          a.color.red, b.color.red);
        v("color green",        a.color.green, b.color.green);
        v("color blue",         a.color.blue, b.color.blue);
    }


    template<typename Visitor>
    void visit_enemy_members(const EnemyConfig& a, const EnemyConfig& b, Visitor v)
    {
        v("shapeRadius",        a.shapeRadius, b.shapeRadius);
        v("collisionRadius",    a.collisionRadius, b.collisionRadius);
        v("min speed",          a.minSpeed, b.minSpeed);
        v("max speed",          a.maxSpeed, b.maxSpeed);
        v("outline color red",  a.outlineColor.red , b.outlineColor.red);
        v("outline color green",a.outlineColor.green, b.outlineColor.green);
        v("outline color blue", a.outlineColor.blue, b.outlineColor.blue);
        v("outline thickness",  a.outlineThickness, b.outlineThickness);
        v("min vertices",       a.minVertices, b.minVertices);
        v("max vertices",       a.maxVertices, b.maxVertices);
        v("small lifespan",     a.smallLifespan, b.smallLifespan);
        v("spawn interval",     a.spawnInterval, b.spawnInterval);
    }

    template<typename Visitor>
    void visit_player_members(const PlayerConfig& a, const PlayerConfig& b, Visitor v)
    {
        v("shapeRadius",         a.shapeRadius, b.shapeRadius);
        v("collisionRadius",     a.collisionRadius, b.collisionRadius);
        v("speed",               a.speed, b.speed);
        v("fill color red",      a.fillColor.red, b.fillColor.red);
        v("fill color green",    a.fillColor.green, b.fillColor.green);
        v("fill color blue",     a.fillColor.blue, b.fillColor.blue);
        v("outline color red",   a.outlineColor.red , b.outlineColor.red);
        v("outline color green", a.outlineColor.green, b.outlineColor.green);
        v("outline color blue",  a.outlineColor.blue, b.outlineColor.blue);
        v("outline thickness",   a.outlineThickness, b.outlineThickness);
        v("shape vertices",      a.shapeVertices, b.shapeVertices);
    }

    template<typename Visitor>
    void visit_window_members(const WindowConfig& a, const WindowConfig& b, Visitor v)
    {
        v("width",              a.width, b.width);
        v("height",             a.height, b.height);
        v("frame rate limit",   a.frameLimit, b.frameLimit);
        v("full screen mode",   a.fullScreenMode, b.fullScreenMode);
    }

    BulletConfig generateRandomBulletConfig();
};