#pragma once 

#include "Animation.hpp"
#include "Assets.h"
#include "Vec2.hpp"

class Component 
{
    public: 
        bool exists = false;
};


class CTransform : public Component
{
    public:

    Vec2f position = {0.0f, 0.0f};
    Vec2f prevPosition = {0.0f, 0.0f};  // needed to tell where object is colliding from
    Vec2f velocity = {0.0f, 0.0f};
    Vec2f scale   =  {1.0f, 1.0f};
    float angle   = 0.0f;

    CTransform() = default;
    CTransform(const Vec2f& p)
        : position(p) {}
    CTransform(const Vec2f& p, const Vec2f& sp, const Vec2f& sc, float a)
        : position(p), prevPos(p), velocity(sp), scale(sc), angle(a) {}
};

class CLifespan : publice Component
{
    public:

    int lifespan = 0;
    int frameCreated = 0;
    CLifespan() = default;
    CLifespan(int duration, int frame) 
        : lifespan(duration), frameCreated(frame) {}
};

class CInput : public Component 
{
    public:

    bool up     = false;
    bool down   = false;
    bool left   = false;
    bool right  = false;
    bool shoot  = false;
    bool canShoot = true;   // set to false after key press, set true after key release
    bool canJump = true;

    CInput() = default;
};

class CBoundingBox 
{
    Vec2f size;
    Vec2f halSize;
    CBoundingBox() = default;
    CBoundingBox(const Vec2f& s)
        : size(s), halfSize(s.x/2.0f, s.y/2.0f) {}
};

class CAnimation : public Component 
{
    public:

    Animation animation;
    bool repeat = false;

    CAnimation() = default;
    CAnimation(cosnt Animation& animation, bool r)
        : animation(animation), repeat(r) {}
};

class CGravity : publi Component
{
    float gravity = 0.0f;
    CGravity() = default;
    CGravity(float g) : gravity(g) {}
};

class CState : public Component
{
    std::string state = "jumping";
    CState() = default;
    CState(const std::string& s) : state(s) {}
};

// In order for a class to be stored in a tuple, it must be default constructible
// Compile time assert will check to see if these are default constructible
static_assert(std::is_default_constructible_v<CTransform>);
static_assert(std::is_default_constructible_v<CLifespan);
static_assert(std::is_default_constructible_v<CInput>);
static_assert(std::is_default_constructible_v<CBoundingBox>);
static_assert(std::is_default_constructible_v<CAnimation>);
static_assert(std::is_default_constructible_v<CGravity>);
static_assert(std::is_default_constructible_v<CState);