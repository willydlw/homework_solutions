#pragma once 

#include <string>
#include <SFML/Graphics.hpp>
#include "gameConfig.h"

class Shape
{
    public:
    // cannot have a default constructor because sf::Text (SFML 3) has no default constructor
    Shape() = delete;   
    Shape(const ShapeConfig& shapeConfig, const sf::Font& font, const TextConfig& textConfig); 

    
    public:

    sf::Text            text;   
    bool                drawable = true;
    sf::Color           color = sf::Color::Green;
    sf::Vector2f        velocity = {0.0f, 0.0f};
    std::string         name = "Default";
};