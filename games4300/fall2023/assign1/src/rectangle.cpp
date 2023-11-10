#include "rectangle.h"

namespace bounce
{
   Rectangle::Rectangle() :
      speed(sf::Vector2f(0.0f, 0.0f)),
      name("default")
   {
      rectangle.setSize(sf::Vector2f(10.0f, 10.0f));
      rectangle.setFillColor(sf::Color(150, 150, 150));
      rectangle.setPosition(sf::Vector2f(0.0f, 0.0f));
   }

   Rectangle::Rectangle(rectangle_t r) :
      speed(sf::Vector2f(r.speed.x, r.speed.y)),
      name(r.name)
   {
      rectangle.setPosition(sf::Vector2f(r.position.x, r.position.y));
      rectangle.setSize(sf::Vector2f(r.width,r.height));
      rectangle.setFillColor(sf::Color(r.color.red, r.color.green, r.color.blue));
   }


   std::ostream& operator << (std::ostream& os, const Rectangle& r)
   {
      sf::Vector2f position = r.rectangle.getPosition();
      sf::Color color = r.rectangle.getFillColor();
      sf::Vector2f dimensions = r.rectangle.getSize();

      os << "position x: " << position.x << ", y: " << position.y << '\n';
      // cast uint8_t to int to print integer value
      // otherwise it intreprets uint8_t as a character 
      os << "color\n\tred:   " << static_cast<int>(color.r) 
         << "\n\tgreen: " << static_cast<int>(color.g) 
         << "\n\tblue:  " << static_cast<int>(color.b) << '\n'
         << "width: " << dimensions.x << ", height: " << dimensions.y << '\n';

      return os;
   }

   /* Centers text within the Circle Shape*/
   void Rectangle::updateTextPosition(void)
   {
      sf::Vector2f textPosition;
      sf::FloatRect gboundsRectangle = rectangle.getGlobalBounds();
      sf::FloatRect lboundsText = text.getLocalBounds();

      // Find offsets for text placement      
      float offsetX = (gboundsRectangle.width / 2.0f) - (lboundsText.width / 2.0f);
      float offsetY = (gboundsRectangle.height / 2.0f) - (lboundsText.height / 2.0f); 
      
      // center text within shape 
      textPosition.x = gboundsRectangle.left + offsetX;
      textPosition.y = gboundsRectangle.top + offsetY; 

      text.setPosition(textPosition);
   }

   void Rectangle::updatePosition(sf::Vector2f boundary)
   {
      sf::Vector2f pos = rectangle.getPosition();
      sf::Vector2f dimensions = rectangle.getSize();
      
      pos.x += speed.x;
      pos.y += speed.y;

      if(pos.x <= 0 || (pos.x + dimensions.x) >= boundary.x)
      {
         speed.x = -speed.x;
      }
      if(pos.y <= 0 || (pos.y + dimensions.y) >= boundary.y)
      {
         speed.y = -speed.y;
      }

      rectangle.setPosition(pos);
      updateTextPosition();

   }

   void Rectangle::draw(sf::RenderTarget &renderTarget)
   {
      renderTarget.draw(rectangle);
      renderTarget.draw(text);
   }
 
 
}