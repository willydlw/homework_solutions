#pragma once 
#include <iostream>

template <typeName T>
class Vec2
{
public:
    T x = 0.0f;
    T y = 0.0f;

    Vec2() = default;

    Vec2(T xin, T yin)
        : x(xin), y(yin) 
    { }

    // constructor to convert from sf::Vector2f 
    Vec2(const sf::Vector2<T>& vec)
        : x(vec.x), y(vec.y) 
    { }

    // 
    Vec2(const sf::Vector2i& vec)
        : x(T(vec.x)), y(T(vec.y))
    { }

    // allow automatic conversion to sf::Vector2 
    // this lets us pass Vec2 into sfml functions 
    operator sf::Vector2<T>()
    {
        return sf::Vector2<T>(x,y);
    }

    Vec2 operator + (const Vec2& rhs) const
    {
        // TODO 
        return Vec2();
    }
    Vec2 operator - (const Vec2& v) const 
    {
        // TODO
        return Vec2();
    }

    Vec2 operator / (const T val) const 
    {
        // TODO
    }
    Vec2 operator * (const T val) const
    {
        // TODO
    }



    Vec2& operator += (const Vec2& rhs)
    {
        // TODO
    }
    
   
    Vec2& operator -= (const Vec2& rhs)
    {
        // TODO
    }
   

    Vec2& operator *= (const T val)
    {
        // TODO
    }

     Vec2& operator /= (const T val)
    {
        // TODO
    }

    bool operator == (const Vec2& rhs) const 
    {
        // TODO
    }

    bool operator != (const Vec2& rhs) const 
    {
        // ToDO
    }

    float dist(const Vec2& rhs)const 
    {
        // TODO
    }

    float length() const 
    {
        // TODO
    }

    void normalize() 
    {
        // TODO
    }


    friend std::ostream& operator << (std::ostream& os, const Vec2& obj);


};