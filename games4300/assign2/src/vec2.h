#pragma once 

/* Class functions using division will throw a runtime error for 
   division by zero. Call them in a try catch block.

   For example:

   Vec2 v(3.0f, 4.0f);
   float divisor = 0.0f;

   try
   {
      v2 / divisor;
   }
   catch(std::runtime_error &e)
   {
      cout << "exception occurred: "
         << e.what();
   }
*/

class Vec2
{
   public:

      float x = 0.0f;
      float y = 0.0f;

      Vec2();
      Vec2(float xin, float yin);

      bool operator == (const Vec2 & rhs) const;
      bool operator != (const Vec2 & rhs) const;

      Vec2 operator + (const Vec2 & rhs) const;
      Vec2 operator - (const Vec2 & rhs) const;
      Vec2 operator / (const float val) const;        // throws runtime exception for division by zero
      Vec2 operator * (const float val ) const;

      void operator += (const Vec2 & rhs);
      void operator -= (const Vec2 & rhs);
      void operator *= (const float val);
      void operator /= (const float val);             // throws runtime exception for division by zero

      float distance(const Vec2 & rhs) const;
      float magnitude() const;
      void normalize();                               // throws runtime exception for division by zero

};