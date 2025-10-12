#pragma once 

#include <SFML/Graphics.hpp>
#include <cmath>

template <typename T>
class Vec2
{
public:
    T x = 0.0f;
    T y = 0.0f;

    Vec2() = default;

    Vec2(T xin, T yin)
        : x(xin), y(yin) 
    { }

    // constructor to convert from sf::Vector2 
    Vec2(const sf::Vector2<T>& vec)
        : x(vec.x), y(vec.y) 
    { }

    // constructor to convert from sf::Vector2i 
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
        return Vec2<T>();
    }
    Vec2 operator - (const Vec2& rhs) const 
    {
        // TODO
        return Vec2<T>();
    }

    Vec2 operator / (const T val) const 
    {
        return Vec2<T>();
    }
    Vec2 operator * (const T val) const
    {
        return Vec2<T> ();
    }


    Vec2& operator += (const Vec2& rhs)
    {
        // TODO
        return *this;
    }
    
   
    Vec2& operator -= (const Vec2& rhs)
    {
        // TODO
        return *this;
    }
   

    Vec2& operator *= (const T val)
    {
       // TODO
        return *this;
    }

     Vec2& operator /= (const T val)
    {
       // TODO
        return *this;
    }

    bool operator == (const Vec2& rhs) const 
    {
        // TODO
        return false;
    }

    bool operator != (const Vec2& rhs) const 
    {
        // TODO
        return false;
    }

    float distance(const Vec2& rhs)const 
    {
        // TODO
        return 0.0f;
    }

    float length() const 
    {
        // TODO
        return 0.0f;
    }

    void normalize() 
    {
        // TODO
    }

};


using Vec2f = Vec2<float>;