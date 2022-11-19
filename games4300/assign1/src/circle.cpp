#include "circle.h"

namespace bounce
{
   Circle::Circle() :
      speed(sf::Vector2f(0.0f, 0.0f)),
      name("default")
   {
      circle.setRadius(10.0f);
      circle.setFillColor(sf::Color(150, 150, 150));
      circle.setPosition(sf::Vector2f(0.0f, 0.0f));
   }

   Circle::Circle(circle_t c) :
      speed(sf::Vector2f(c.speed.x, c.speed.y)),
      name(c.name)
   {
      circle.setPosition(sf::Vector2f(c.position.x, c.position.y));
      circle.setRadius(c.radius);
      circle.setFillColor(sf::Color(c.color.red, c.color.green, c.color.blue));
   }

   std::ostream& operator << (std::ostream& os, const Circle& c)
   {
      sf::Vector2f position = c.circle.getPosition();
      sf::Color color = c.circle.getFillColor();

      os << "position x: " << position.x << ", y: " << position.y << '\n';
      // cast uint8_t to int to print integer value
      // otherwise it intreprets uint8_t as a character 
      os << "color\n\tred:   " << static_cast<int>(color.r) 
         << "\n\tgreen: " << static_cast<int>(color.g) 
         << "\n\tblue:  " << static_cast<int>(color.b) << '\n'
         << "radius: " << c.circle.getRadius() << '\n';

      return os;
   }

   /* Centers text within the Circle Shape*/
   void Circle::updateTextPosition(void)
   {
      sf::Vector2f textPosition;
      sf::FloatRect gboundsCircle = circle.getGlobalBounds();
      sf::FloatRect lboundsText = text.getLocalBounds();

      // Find offsets for text placement      
      float offsetX = (gboundsCircle.width / 2.0f) - (lboundsText.width / 2.0f);
      float offsetY = (gboundsCircle.height / 2.0f) - (lboundsText.height / 2.0f); 
      
      // center text within shape 
      textPosition.x = gboundsCircle.left + offsetX;
      textPosition.y = gboundsCircle.top + offsetY; 

      text.setPosition(textPosition);
   }

   void Circle::updatePosition(sf::Vector2f boundary)
   {
      sf::Vector2f pos = circle.getPosition();
      float diameter = 2.0f * circle.getRadius();

      pos.x += speed.x;
      pos.y += speed.y;

      if(pos.x <= 0 || (pos.x + diameter) >= boundary.x)
      {
         speed.x = -speed.x;
      }
      if(pos.y <= 0 || (pos.y + diameter) >= boundary.y)
      {
         speed.y = -speed.y;
      }

      circle.setPosition(pos);
      updateTextPosition();

   }

   void Circle::draw(sf::RenderTarget &renderTarget)
   {
      renderTarget.draw(circle);
      renderTarget.draw(text);
   }
 
}