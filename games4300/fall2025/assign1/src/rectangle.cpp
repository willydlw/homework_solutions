#include "rectangle.h"
#include <iomanip>

Rectangle::Rectangle(   const RectangleConfig& rectConfig,
                        const sf::Font& font, 
                        const TextConfig& textConfig) 
                        : m_text(font, rectConfig.shapeConfig.name, textConfig.characterSize),
                          m_drawable(true),
                          m_velocity(rectConfig.shapeConfig.velocity),
                          m_name(rectConfig.shapeConfig.name)
{
    m_text.setFillColor(textConfig.fillColor);

    // rectangle shape attributes
    setSize({rectConfig.width, rectConfig.height});
    setPosition(rectConfig.shapeConfig.position);
    setColor(rectConfig.shapeConfig.color);
}
    

void Rectangle::update(const sf::Vector2u& boundary)
{
    // position is top left corner
    sf::Vector2f position = m_rectangle.getPosition();

    position.x += m_velocity.x;
    position.y += m_velocity.y;
    

    // width is size.x, height is size.y
    sf::Vector2f size = getSize();
    sf::Vector2f scale = getScale();
    size.x *= scale.x;
    size.y *= scale.y;

    // gui scaling can cause the object to go beyond 
    // the window boundaries and remain beyond the boundary
    // resulting in oscillating velocity if position is
    // not also corrected.
    if(position.y + size.y > boundary.y) 
    {
        m_velocity.y = -m_velocity.y;
        position.y = boundary.y - size.y;
    }
    else if(position.y < 0)
    {
        m_velocity.y = -m_velocity.y;
        position.y = 0;
    }

    if(position.x + size.x > boundary.x)
    {
        m_velocity.x = -m_velocity.x;
        position.x = boundary.x - size.x;
    }
    else if(position.x < 0)
    {
        m_velocity.x = -m_velocity.x;
        position.x = 0;
    }
    
    m_rectangle.setPosition(position);
    updateTextPosition();
}


// Centers text within the circle shape
void Rectangle::updateTextPosition(void)
{
    sf::Vector2f textPosition;

    // Global Bounds is minimal rectangle that fully encloses shape 
    // taking into account all transformations 
    // Provides an axis-aligned bounding box 
    // in terms of global coordinate system
    sf::FloatRect gboundsRect = m_rectangle.getGlobalBounds();
    float rectBoxWidth = gboundsRect.size.x;
    float rectBoxHeight = gboundsRect.size.y;
    float rectBoxLeft = gboundsRect.position.x;
    float rectBoxTop = gboundsRect.position.y;

  
    // Local bounds 
    sf::FloatRect lboundsText = m_text.getLocalBounds();
    float localTextWidth = lboundsText.size.x;
    float localTextHeight = lboundsText.size.y;
   
    // Find offsets for text placement 
    float offsetX = (rectBoxWidth  / 2.0f) - (localTextWidth / 2.0f);
    float offsetY = (rectBoxHeight / 2.0f) - (localTextHeight / 2.0f);

    // center text within shape 
    textPosition.x = rectBoxLeft + offsetX;
    textPosition.y = rectBoxTop + offsetY;
    m_text.setPosition(textPosition);
}

void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(m_drawable)
    {
        states.transform *= getTransform();
        target.draw(m_rectangle, states);
        target.draw(m_text, states);
    }
}


std::ostream& operator << (std::ostream& os, const Rectangle& obj)
{
    static constexpr int PRINT_WIDTH = 8;
    std::ios_base::fmtflags oldFlags = os.flags();

    sf::Color color = obj.getColor();
    sf::Vector2f size = obj.getSize();
    sf::Vector2f position = obj.getPosition();
    sf::Vector2f scale = obj.getScale();

    os << std::fixed << std::setprecision(2);

    os << "name:         "  << obj.m_name << "\n";
    os << "scale      x: "  << std::setw(PRINT_WIDTH) << scale.x  
                            << ", y: " << std::setw(PRINT_WIDTH) << scale.y << "\n"; 
    
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

    std::string textString = obj.m_text.getString();

    os << "Text Data\n";
    os << "\tsize: " << obj.m_text.getCharacterSize() << "\n"
        << "\tstring: " << textString << "\n";

    os.flags(oldFlags);
    return os;
}



/* Getter Functions */

sf::Color Rectangle::getColor()const 
{
    return m_rectangle.getFillColor();
}

sf::Vector2f Rectangle::getSize()const
{
    return m_rectangle.getSize();
}

sf::Vector2f Rectangle::getPosition()const
{
    return m_rectangle.getPosition();
}

sf::Vector2f Rectangle::getScale()const 
{
    return m_rectangle.getScale();
}



/*  Setter Functions */

void Rectangle::setColor(sf::Color color){
    m_rectangle.setFillColor(color);
}


void Rectangle::setSize(sf::Vector2f size)
{
    m_rectangle.setSize(size);
}

void Rectangle::setPosition(sf::Vector2f position)
{
    m_rectangle.setPosition(position);
}

void Rectangle::setScale(sf::Vector2f scale)
{
    m_rectangle.setScale(scale);
}
