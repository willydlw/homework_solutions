#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "config.h"

namespace bounce
{
   class Circle{
      public:
         Circle();
         Circle(circle_t c);
      
         sf::CircleShape      circle;
         sf::Vector2f         speed;
         sf::Text             text;
         std::string          name;

         friend std::ostream& operator << (std::ostream& os, const Circle& c);
         void updatePosition(sf::Vector2f boundary);
         void draw(sf::RenderTarget &renderTarget);

      private:
         void updateTextPosition(void);
   };
}

#endif 