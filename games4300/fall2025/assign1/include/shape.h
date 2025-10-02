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

    
    void setName(const std::string& name);
    void setVelocity(const sf::Vector2f& velocity);

    std::string  getName() const;
    sf::Vector2f getVelocity() const;

    protected:

    // data members 
    sf::Text m_text;
    bool                drawable = true;
    sf::Vector2f        m_velocity = {0.0f, 0.0f};
    std::string         m_name = "Default";
};