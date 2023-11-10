#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include "config.h"
#include "circle.h"
#include "rectangle.h"

namespace bounce
{
   void initCircleShapes(std::vector<circle_t>& circleConfig, 
                        std::vector<Circle> &circles, 
                        const sf::Font &font,
                        const bounce::font_t *fontConfig); 

   void initRectangleShapes(std::vector<rectangle_t> &rectangleConfig, 
                        std::vector<bounce::Rectangle> &rectangles,
                        const sf::Font &font,
                        const bounce::font_t *fontConfig); 

   // used for debugging object bounding box
   void printBounds(sf::FloatRect obj, std::string title);
}

#endif 