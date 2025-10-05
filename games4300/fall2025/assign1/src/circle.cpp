#include "circle.h"
#include <iomanip>

#include <SFML/Graphics.hpp>

Circle::Circle( const CircleConfig& circleConfig, 
                const sf::Font& font,
                const TextConfig& textConfig) 
                : m_text(font, circleConfig.shapeConfig.name, textConfig.characterSize),
                  m_drawable(true), 
                  m_velocity(circleConfig.shapeConfig.velocity),
                  m_name(circleConfig.shapeConfig.name)
{
    m_text.setFillColor(textConfig.fillColor);
    setRadius(circleConfig.radius);
    setPosition(circleConfig.shapeConfig.position);
    setColor(circleConfig.shapeConfig.color);
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
        std::cerr << "WARNING radius: " << radius 
            << " not within bounds {" << MIN_RADIUS << ", "
            << MAX_RADIUS << "}, setting to default: " 
            << DEFAULT_RADIUS << "\n";  
        m_circle.setRadius(DEFAULT_RADIUS);
    }
}

void Circle::setColor(sf::Color color)
{
    std::cerr << "[INFO] function: " << __PRETTY_FUNCTION__ 
        << "color values r: " << (int)color.r 
        << ", g: " << (int)color.g 
        << ", b: " << (int)color.b 
        << ", a: " << (int)color.a
        << "\n";
    m_circle.setFillColor(color);

    sf::Color updatedColor = m_circle.getFillColor();

    std::cerr << "After calling setFillColor, getFillColor returns r: "
        << (int)updatedColor.r 
        << ", g: " << (int)updatedColor.g 
        << ", b: " << (int)updatedColor.b 
        << ", a: " << (int)updatedColor.a 
        << "\n";
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

