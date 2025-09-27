#include "rectangle.h"

#include <iomanip>

Rectangle::Rectangle(   const RectangleConfig* rectConfig, 
                        const TextConfig* textConfig
                    ) 
                    :   m_font(textConfig->font), 
                        m_text(m_font)
{
    m_text.setCharacterSize(textConfig->fontSize);
    m_text.setFillColor(textConfig->color);

    // rectangle shape attributes
    setSize({rectConfig->width, rectConfig->height});
    setPosition(rectConfig->position);
    setColor(rectConfig->color);

    setVelocity(rectConfig->velocity);
    m_name = rectConfig->shapeName;
}

void Rectangle::update(const sf::Vector2u& boundary)
{
    sf::Vector2f position = m_rectangle.getPosition();
    position.x += m_velocity.x;
    position.y += m_velocity.y;
    setPosition(position);

    
    sf::Vector2f size = getSize();
    // position.y is rectangle top
    if(position.y + size.y > boundary.y || position.y < 0)
    {
        m_velocity.y = -m_velocity.y;
    }

    // position.x is rectangle top left 
    if(position.x + size.x > boundary.x || position.x < 0)
    {
        m_velocity.x = -m_velocity.x;
    }
}

void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_rectangle, states);
}

void Rectangle::setColor(sf::Color color){
    m_rectangle.setFillColor(color);
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
    static constexpr int PRINT_WIDTH = 8;
    std::ios_base::fmtflags oldFlags = os.flags();

    sf::Color color = obj.getColor();
    sf::Vector2f size = obj.getSize();
    sf::Vector2f position = obj.getPosition();

    os << std::fixed << std::setprecision(2);

    os << "name:         "  << obj.m_name << "\n";
    
    os << "width:        "  << std::setw(PRINT_WIDTH) << size.x 
                            << ", height: " << std::setw(PRINT_WIDTH) << size.y << "\n";

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


sf::Color Rectangle::getColor()const 
{
    return m_rectangle.getFillColor();
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