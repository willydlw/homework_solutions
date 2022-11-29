#include "vec2.h"
#include <cmath>
#include <stdexcept>

Vec2::Vec2() : x(0.0f), y(0.0f)
{

}

Vec2::Vec2(float xin, float yin)
   : x(xin), y(yin)
{

}

bool Vec2::operator == (const Vec2 & rhs) const
{
   return(x == rhs.x && y == rhs.y);
}

bool Vec2::operator != (const Vec2 & rhs) const 
{
   return(x != rhs.x || y != rhs.y);
}

Vec2 Vec2::operator + (const Vec2 & rhs) const
{
   return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2 & rhs) const
{
   return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator * (const float val) const
{
   return Vec2(x * val, y * val);
}

Vec2 Vec2::operator / (const float val) const
{
   // throw runtime error for division by zero
   if(val == 0)
   {
      throw std::runtime_error("Math error: Attempted division by zero\n");
   }

   // else complete the division operation
   return Vec2(x / val, y / val);
}


void Vec2::operator += (const Vec2 & rhs)
{
   x += rhs.x;
   y += rhs.y;
}

void Vec2::operator -= (const Vec2 & rhs)
{
   x -= rhs.x;
   y -= rhs.y;
}

void Vec2::operator *= (const float val)
{
   x *= val;
   y *= val;
}

void Vec2::operator /= (const float val)
{
   // throw runtime error for division by zero
   if(val == 0)
   {
      throw std::runtime_error("Math error: Attempted division by zero\n");
   }

   // else complete the division operation
   x /= val;
   y /= val;
}

float Vec2::distance(const Vec2 & rhs) const
{
   return sqrtf((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y-rhs.y));
}

float Vec2::magnitude()const
{
   return sqrtf( x*x + y*y );
}

void Vec2::normalize()
{
   float length = this->magnitude();
   // throw runtime error for division by zero
   if(length == 0)
   {
      throw std::runtime_error("Math error: Attempted division by zero\n");
   }

   // else complete the division operation
   x = x / length;
   y = y / length;
}
