#include "rectangle.hpp"

Rectangle::Rectangle(   sf::Vector2f size,
                        std::string name,
                        sf::Vector2f position,
                        sf::Vector2f velocity, 
                        sf::Color color
                    )
{
    setSize(size);
    setName(name);
    setPosition(position);
    setVelocity(velocity);
    setColor(color);
}

void Rectangle::setColor(sf::Color color){
    m_color = color;
}

void Rectangle::setName(std::string& name)
{
    m_name = name;
}

void Rectangle::setSize(sf::Vector2f size)
{
    m_rectangle.setSize(size);
}

void Rectangle::setPosition(sf::Vector2f position)
{
    m_rectangle.setPosition(position);
}

void Rectangle::setVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}


std::ostream& operator << (std::ostream& os, const Rectangle& obj)
{
    os << "name: " << obj.m_name << "\n";
    return os;
}

std::string Rectangle::getName()const 
{ 
    return m_name;
}

sf::Vector2f Rectangle::getSize()const
{
    return m_rectangle.getSize();
}

sf::Vector2f Rectangle::getPosition()const
{
    return m_rectangle.getPosition();
}

sf::Vector2f Rectangle::getVelocity()const 
{
    return m_velocity;
}