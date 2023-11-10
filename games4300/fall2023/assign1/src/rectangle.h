#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <SFML/Graphics.hpp>

#include "config.h"

namespace bounce
{
   class Rectangle{
      public:
         Rectangle();
         Rectangle(rectangle_t r);
      
         sf::RectangleShape   rectangle;
         sf::Vector2f         speed;
         sf::Text             text;
         std::string          name;

         friend std::ostream& operator << (std::ostream& os, const Rectangle& r);
         void updatePosition(sf::Vector2f boundary);
         void draw(sf::RenderTarget &renderTarget);

      private:
         void updateTextPosition(void);
   };
}

#endif 