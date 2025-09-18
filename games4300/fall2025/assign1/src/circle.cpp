#include "circle.hpp"

Circle::Circle( float radius,
                sf::Color color,
                sf::Vector2f position,
                sf::Vector2f velocity,
                std::string name
                )
{
    setRadius(radius);
    setPosition(position);
    setVelocity(velocity);
    setColor(color);
    setName(name);
}

void Circle::setPosition(sf::Vector2f position)
{
    m_circle.setPosition(position);
}
    
void Circle::setRadius(float radius)
{
    if(radius >= MIN_RADIUS && radius <= MAX_RADIUS){
        m_circle.setRadius(radius);
    }
    else{
        m_circle.setRadius(DEFAULT_RADIUS);
    }
}

void Circle::setColor(sf::Color color)
{
    m_circle.setFillColor(color);
}

void Circle::setVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

void Circle::setName(std::string& name){
    m_name = name;
}


std::ostream& operator <<(std::ostream& os, const Circle& obj)
{
    std::cerr << __func__ << " incomplete\n";
    os << "name: " << obj.m_name << "\n";
    return os;
}



/**** Getter Functions  *****/

sf::Vector2f Circle::getPosition()const 
{
    return m_circle.getPosition();
}

float Circle::getRadius()const
{
    return m_circle.getRadius();
}

sf::Color Circle::getColor()const 
{
    return m_circle.getFillColor();
}

std::string Circle::getName()const 
{
    return m_name;
}