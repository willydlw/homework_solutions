#pragma once 

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>

/*  Class functions using division will throw a runtime error for 
    division by zero. Call them in a try catch block.

    Example:
    Vec2<float> v(3.0f, 4.0f);
    float divisor = 0.0f;
    try{
        v2 /= divisor;
    }
    catch(std::runtime_error &e)
    {
        std::cerr << "exception occurred: " << e.what();
    }
*/

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

    #if 0
    // Note: this causes an issue when creating Vec2<int> 
    // as it duplicates integer copy constructors 
     
    // constructor to convert from sf::Vector2i 
    Vec2(const sf::Vector2i& vec)
        : x(T(vec.x)), y(T(vec.y))
    { }
    #endif 

    Vec2(const sf::Vector2u& vec)
        : x(T(vec.x)),
          y(T(vec.y))
    { }

    // allow automatic conversion to sf::Vector2 
    // this lets us pass Vec2 into sfml functions 
    operator sf::Vector2<T>()
    {
        return sf::Vector2<T>(x,y);
    }

    /****  Overloaded Operators ****/ 

    // v3 = v1 + v2
    Vec2 operator + (const Vec2& rhs) const
    {
        return Vec2<T>(x + rhs.x, y + rhs.y);
    }

    // v3 = v1 - v2
    Vec2 operator - (const Vec2& rhs) const 
    {
        return Vec2<T>(x - rhs.x, y - rhs.y);
    }

    // unary minus
    Vec2 operator - () const 
    {
        return Vec2<T>(-x, -y);
    }

    
    // scalar division
    Vec2 operator / (const T val) const 
    {
        // throw runtime error for division by zero 
        if(val != 0.0f){
            return Vec2<T>( x / val, y / val);
        }
        else
        {
            std::ostringstream oss; 
            oss << "[RUNTIME ERROR] function: " << __PRETTY_FUNCTION__ 
                << "\n\t--Attempted division by zero--"
                << "\n\tx: " << x << ", y: " << y 
                << "\n\tscalar: " << val << "\n";
            throw std::runtime_error(oss.str());
            return Vec2();
        }        
    }


    // scalar multiplication
    Vec2 operator * (const T val) const
    {
        return Vec2<T> ( x * val, y * val);
    }


    // v1 = v1 + v2
    Vec2& operator += (const Vec2& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    
   
    // v1 = v1 - v2
    Vec2& operator -= (const Vec2& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
   
    // v1 = v1 * val
    Vec2& operator *= (const T val)
    {
        x *= val;
        y *= val;
        return *this;
    }

    // v1 = v1 / val
    Vec2& operator /= (const T val)
    {
        x /= val;
        y /= val;
        return *this;
    }

    bool operator == (const Vec2& rhs) const 
    {
        return(x == rhs.x && y == rhs.y);
    }

    bool operator != (const Vec2& rhs) const 
    {
        return (x != rhs.x || y != rhs.y);
    }

    friend std::ostream& operator << (std::ostream& os, const Vec2<T>& obj)
    {
        os << "x: " << obj.x << ", y: " << obj.y;
        return os;
    }

    T dotProduct(const Vec2<T>& rhs) const
    {
        return (x*rhs.x + y * rhs.y);
    }

    // calculates angle between the two vectors
    float angle(const Vec2& rhs) const
    {
        return std::acos(dotProduct(rhs) / (magnitude() * rhs.magnitude()));
    }

    float distance(const Vec2& rhs)const 
    {
        return sqrt((x-rhs.x)*(x-rhs.x) + (y-rhs.y)*(y-rhs.y));
    }

    float magnitude() const 
    {
        return sqrt(x*x + y*y);
    }

    Vec2<T> normalize()const 
    {
        float mag = magnitude();

        if(mag > 0)
        {
            return Vec2<T> ((float)x/mag, (float)y/mag);
        }
        else
        {
            // throw runtime error for division by zero 
            std::ostringstream oss; 
            oss << "[RUNTIME ERROR] function: " << __PRETTY_FUNCTION__ 
                << "\n\t--Attempted division by zero--"
                << "\n\tx: " << x << ", y: " << y  
                << "\n\tmagnitude: " << mag << "\n";
            throw std::runtime_error(oss.str());
            return Vec2();
        }
    }

};


using Vec2f = Vec2<float>;