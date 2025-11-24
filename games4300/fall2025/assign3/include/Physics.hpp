#ifndef A3_PHYSICS_H
#define A3_PHYSICS_H

#include "Entity.hpp"

namespace Physics
{
    Vec2f GetOverlap(std::shared_ptr<Entity> a, std::shared_pointer<Entity> b)
    {
        // TODO: return the overlap rectangle size of the bounding boxes of entity a and b 
        return Vec2f(0,0);
    }

    Vec2f GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        // TODO: return the previous overloap rectangle size of the bounding boxes of 
        // entity a and b 
        // previous overlap uses the entity's previous position 
        return Vec2f(0,0);
    }
}

// From lecture notes, but not shown as part of physics.hpp in assignment 3
class Physics 
{
    bool isCollision(Entity, Enity);
    bool isIntersect(Line, Line);
    bool isInside(Vec2, Line);
}

#endif