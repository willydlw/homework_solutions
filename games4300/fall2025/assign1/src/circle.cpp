#include "circle.h"
#include <iomanip>

#include <SFML/Graphics.hpp>

Circle::Circle( const CircleConfig* circleConfig, 
                const sf::Font& font,
                const TextConfig* textConfig) 
                : m_text(font, circleConfig->shapeName, textConfig->characterSize)
{

    
    m_text.setFillColor(textConfig->fillColor);
    m_text.setPosition(circleConfig->position);

    // circleShape attributes
    setRadius(circleConfig->radius);
    setPosition(circleConfig->position);
    setPosition(circleConfig->position);
    setColor(circleConfig->color);

    setVelocity(circleConfig->velocity);
    m_name = circleConfig->shapeName;
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
    // position is top left corner of circle bounding box
    sf::Vector2f position = m_circle.getPosition();
    float diameter = 2.0f * m_circle.getRadius();

    position.x += m_velocity.x;
    position.y += m_velocity.y;
    
    if( (position.y + diameter) >= boundary.y || position.y <= 0)
    {
        m_velocity.y = -m_velocity.y;
    }

    if((position.x + diameter) >= boundary.x || position.x <= 0)
    {
        m_velocity.x = -m_velocity.x;
    }

    m_circle.setPosition(position);
    updateTextPosition();
}

// Centers text within the circle shape
void Circle::updateTextPosition(void)
{
    sf::Vector2f textPosition;

    // Global Bounds is minimal rectangle that fully encloses shape 
    // taking into account all transformations 
    // Provides an axis-aligned bounding box 
    // in terms of global coordinate system
    sf::FloatRect gboundsCircle = m_circle.getGlobalBounds();
    float circleBoxWidth = gboundsCircle.size.x;
    float circleBoxHeight = gboundsCircle.size.y;
    float circleBoxLeft = gboundsCircle.position.x;
    float circleBoxTop = gboundsCircle.position.y;

    // Local bounds 
    sf::FloatRect lboundsText = m_text.getLocalBounds();
    float localTextWidth = lboundsText.size.x;
    float localTextHeight = lboundsText.size.y;

   
    // Find offsets for text placement 
    float offsetX = (circleBoxWidth  / 2.0f) - (localTextWidth / 2.0f);
    float offsetY = (circleBoxHeight / 2.0f) - (localTextHeight / 2.0f);

    // center text within shape 
    textPosition.x = circleBoxLeft + offsetX;
    textPosition.y = circleBoxTop + offsetY;
    m_text.setPosition(textPosition);
}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_circle, states);
    target.draw(m_text, states);
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