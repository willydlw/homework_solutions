#include "shape.h"

Shape::Shape(   const ShapeConfig& shapeConfig, 
                const sf::Font& font, 
                const TextConfig& textConfig) 
                : m_text(font, shapeConfig.name, textConfig.characterSize),
                  drawable(true), m_velocity(shapeConfig.velocity), 
                  m_name(shapeConfig.name)
{

    m_text.setFillColor(textConfig.fillColor);   
    m_text.setPosition(shapeConfig.position);
}

void Shape::setName(const std::string& name)
{
    m_name = name;
}

void Shape::setVelocity(const sf::Vector2f& velocity)
{
    m_velocity = velocity;
}


std::string Shape::getName()const 
{ 
    return m_name;
}

sf::Vector2f Shape::getVelocity()const 
{
    return m_velocity;
}