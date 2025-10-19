#pragma once 

#include "../../a2solution/include/gameConfig.h"

class GameConfigTest 
{
    public:

    GameConfigTest() = default;

    void testReadBulletConfig(const char* filename, const BulletConfig& expectedConfig);

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
        v("outline thickness",   a.outLineThickness, b.outLineThickness);
        v("shape vertices",      a.shapeVertices, b.shapeVertices);
        v("lifespan",            a.lifespan, b.lifespan);
    }

};