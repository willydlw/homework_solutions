/* File shown on assignment 2 video */
#pragma once 


#include "Vec2.h"
#include <SFML/Graphics.hpp>


/* Components are essentially structs

   They are classes that represent pure data.
   The only functioinality in each class is the constructor.

*/

class CTransform
{
   public:
      Vec2 pos      = {0.0, 0.0};
      Vec2 velocity  = {0.0, 0.0};
      float angle    = 0.0f;

      CTransform(const Vec2 &p, const Vec2 &v, float a)
         : pos(p), velocity(v), angle(a) {}
};


class CShape
{
   public:
      sf::CircleShape circle;

      CShape(float radius, int points, const sf::Color &fill, const sf::Color & outline, float thickness)
         : circle(radius, points)
      {
         circle.setFillColor(fill);
         circle.setOutlineColor(outline);
         circle.setOutlineThickness(thickness);
         circle.setOrigin(radius,radius);
      }
};

class CCollision
{
   public:
      float radius = 0.0f;
      CCollision(float r)
         : radius(r) {}

};

class CScore
{
   public:
      int score = 0;
      CScore(int s)
         : score(s) {}

};

class CLifespan
{
   public:
      int remaining     = 0;  // amount of lifespan remaining on the entity
      int total         = 0;  // total initial amount of lifespan 
      CLifespan(int total)
         : remaining(total), total(total) {}
};


/* stores whether we are pressing specific keys */
class CInput
{
   public:
      bool up     = false;
      bool down   = false;
      bool left   = false;
      bool right  = false;
      bool shoot  = false;

      CInput() {}
};
