#include "shape.h"

Shape::Shape(   const ShapeConfig& shapeConfig, 
                const sf::Font& font, 
                const TextConfig& textConfig) 
                : text(font, shapeConfig.name, textConfig.characterSize),
                  drawable(true), velocity(shapeConfig.velocity), 
                  name(shapeConfig.name)
{

    text.setFillColor(textConfig.fillColor);   
    text.setPosition(shapeConfig.position);
}

