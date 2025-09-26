#include "circle.hpp"
#include <iomanip>

#include <SFML/Graphics.hpp>

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


void Circle::update(const sf::Vector2u& boundary)
{
    sf::Vector2f position = m_circle.getPosition();
    position.x += m_velocity.x;
    position.y += m_velocity.y;
    setPosition(position);

    float radius = getRadius();
    if(position.y + radius > boundary.y || position.y - radius < 0)
    {
        m_velocity.y = -m_velocity.y;
    }

    if(position.x + radius > boundary.x || position.x - radius < 0)
    {
        m_velocity.x = -m_velocity.x;
    }
}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_circle, states);
}


std::ostream& operator <<(std::ostream& os, const Circle& obj)
{
    static constexpr int PRINT_WIDTH = 8;
    std::ios_base::fmtflags oldFlags = os.flags();

    sf::Color color = obj.getColor();
    sf::Vector2f position = obj.getPosition();

    os << std::fixed << std::setprecision(2);

    os << "name:         "  << obj.m_name << "\n";
    os << "radius:       "  << std::setw(PRINT_WIDTH) << obj.getRadius() << "\n"; 
    os << "position   x: "  << std::setw(PRINT_WIDTH) << position.x 
                            << ", y: " << std::setw(PRINT_WIDTH) << position.y << "\n";
    os << "velocity   x: "  << std::setw(PRINT_WIDTH) << obj.m_velocity.x 
                            << ", y: " << std::setw(PRINT_WIDTH) << obj.m_velocity.y << "\n";
    
     os << "fill color r: "  << std::setw(PRINT_WIDTH) << static_cast<unsigned> (color.r) 
                            << "  g: " << std::setw(PRINT_WIDTH) << static_cast<unsigned> (color.g) 
                            << "  b: " << std::setw(PRINT_WIDTH) << static_cast<unsigned> (color.b)
                            << "\n";

    os.flags(oldFlags);
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