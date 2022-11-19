#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>


class Vec2{
   
   public:

   float x = 0.0f;
   float y = 0.0f;

   Vec2() {}
   Vec2(float xin, float yin)
      : x(xin)
      , y(yin)
   {}

   // add consts after ) because the object
   // is not modified
   Vec2 operator + (const Vec2& rhs)const
   {
      return Vec2( x + rhs.x, y + rhs.y);
   }

   void operator += (const Vec2& rhs)
   {
      x += rhs.x;
      y += rhs.y;
   }

   Vec2& add(const Vec2& v)
   {
      x += v.x;
      y += v.y;
      return *this;
   }

   Vec2& scale(float s)
   {
      x *= s;
      y *= s;
      return *this;
   }

   // returning a reference to the object allows chaining function calls
   // example: v1.scale(5.0).rotate(30).normalize()


   float dist(const Vec2& v)const
   {
      return sqrtf((v.x-x) * (v.x-x) + (v.y-y) * (v.y-y));
   }



};

#endif 