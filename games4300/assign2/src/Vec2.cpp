#include "Vec2.h"
#include <cmath>

Vec2::Vec2()
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
   // TODO
}

Vec2 Vec2::operator - (const Vec2 & rhs) const
{
   // TODO
}

Vec2 Vec2::operator * (const float val) const
{
   return Vec2(x * val, y * val);
}

Vec2 Vec2::operator / (const float val) const
{
   // TODO
}


void Vec2::operator += (const Vec2 & rhs)
{
   // TODO
}

void Vec2::operator -= (const Vec2 & rhs)
{
   // TODO
}

void Vec2::operator *= (const float val)
{
   // TODO
}

void Vec2::operator /= (const float val)
{
   // TODO
}

float Vec2::length ()const
{
   // TODO
}

void Vec2::normalize()
{
   // TODO
}