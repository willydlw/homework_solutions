#pragma once 

#include <SFML/Graphics.hpp>

#include "../include/vec2.hpp"


// Base class - all components need exists attribute
// so we create the base class with this public attribute
// and have all component classes inherit from the base
// class so we don't have to manually add the same variable 
// to all the component classes
class Component
{
public:
    bool exists = false;
};

// exists is whether entity actually contains the
// derived component

// default to fals so default constructed components 
// are not considered part of the entity


// All components have default constructor because tuple requires one

class CTransform : public Component
{
    public:
    Vec2f pos      = {0.0f, 0.0f};
    Vec2f velocity = {0.0f ,0.0f};
    float angle = 0.0f;

    CTransform() = default;
    CTransform(const Vec2f& p, const Vec2f& v, float a )
        : pos(p), velocity(v), angle(a) {}
};


class CShape : public Component
{

public:
    sf::CircleShape circle;

    CShape() = default;
    CShape(float radius, size_t points, const sf::Color& fill, 
            const sf::Color& outline, float thickness)
        : circle(radius, points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin({radius, radius});
    }
};


class CCollision : public Component 
{
    public:
    float radius = 0;

    CCollision() = default;
    CCollision(float r)
        : radius(r) {}
};

class CScore : public Component
{
public:
    int score = 0;

    CScore() = default;
    CScore(int s) : score(s) {}
};

class CLifeSpan : public Component
{
    public:
    int lifespan = 0;
    int remaining = 0;
    CLifeSpan() = default;
    CLifeSpan(int totalLifespan)
        : lifespan(totalLifespan)
        , remaining(totalLifespan) {}
};


class CInput : public Component
{
public:
    bool up = false;
    bool left = false;
    bool right = false;
    bool down = false;
    bool shoot = false;
    
    CInput() = default;
};