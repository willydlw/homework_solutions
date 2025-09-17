#include "rectangle.hpp"

Rectangle::Rectangle(   sf::Vector2f size,
                        std::string name
                    )
{
    setSize(size);
    setName(name);
}


void Rectangle::setName(std::string& name)
{
    m_name = name;
}

void Rectangle::setSize(sf::Vector2f size)
{
    m_rectangle.setSize(size);
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