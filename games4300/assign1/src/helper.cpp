#include "helper.h"

namespace bounce{
   void initCircleShapes(std::vector<circle_t>& circleConfig, 
                        std::vector<Circle> &circles, 
                        const sf::Font &font,
                        const bounce::font_t *fontConfig)
   {
      for( auto& c : circleConfig)
      {
         sf::Color color(fontConfig->color.red, fontConfig->color.green, fontConfig->color.blue);
         Circle cs(c);

         cs.text.setString(c.name);
         cs.text.setFont(font);
         cs.text.setCharacterSize(fontConfig->size);
         cs.text.setFillColor(color);
         circles.push_back(cs);
      }
   }

   void initRectangleShapes(std::vector<rectangle_t>& rectangleConfig, 
                        std::vector<Rectangle> &rectangles,
                        const sf::Font &font,
                        const bounce::font_t *fontConfig)
   {
      for( auto& r : rectangleConfig)
      {
         sf::Color color(fontConfig->color.red, fontConfig->color.green, fontConfig->color.blue);
         Rectangle rs(r);
         rs.text.setString(r.name);
         rs.text.setFont(font);
         rs.text.setCharacterSize(fontConfig->size);
         rs.text.setFillColor(color);
         rectangles.push_back(rs);
      }
   }

   void printBounds(sf::FloatRect obj, std::string title)
   {
      std::cout << "\n*** " << title << "***\n";
      std::cout   << "left:   " << obj.left << '\n'
                  << "top:    " << obj.top << '\n'
                  << "width:  " << obj.width << '\n'
                  << "height: " << obj.height << '\n';
   }
}