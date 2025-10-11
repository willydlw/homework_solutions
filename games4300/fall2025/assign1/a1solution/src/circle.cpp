#include "circle.h"
#include <iomanip>

#include <SFML/Graphics.hpp>

Circle::Circle( const CircleConfig& circleConfig, 
                const sf::Font& font,
                const TextConfig& textConfig) 
                : m_text(font, circleConfig.shapeConfig.name, textConfig.characterSize),
                  m_drawState(true), 
                  m_velocity(circleConfig.shapeConfig.velocity),
                  m_id(circleConfig.shapeConfig.name),
                  m_displayName(circleConfig.shapeConfig.name)
{
    m_text.setFillColor(textConfig.fillColor);
    setRadius(circleConfig.radius);
    setPosition(circleConfig.shapeConfig.position);
    setColor(circleConfig.shapeConfig.color);
}


void Circle::update(const sf::Vector2u& boundary)
{
    // position is top left corner of circle bounding box
    sf::Vector2f position = m_circle.getPosition();

    position.x += m_velocity.x;
    position.y += m_velocity.y;
  
    // when gui sets circle scale, both x,y are same
    float diameter = 2.0f * m_circle.getRadius() * m_circle.getScale().x;
    
    // gui scaling can cause the object to go beyond 
    // the window boundaries and remain beyond the boundary
    // resulting in oscillating velocity if position is
    // not also corrected.
    if( (position.y + diameter) >= boundary.y)
    {
        m_velocity.y = -m_velocity.y;
        position.y = boundary.y - diameter;
    }
    else if(position.y < 0)
    {
        m_velocity.y = -m_velocity.y;
        position.y = 0;
    }

    if((position.x + diameter) > boundary.x)
    {
        m_velocity.x = -m_velocity.x;
        position.x = boundary.x - diameter;
    }
    else if(position.x < 0)
    {
        m_velocity.x = -m_velocity.x;
        position.x = 0;
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
    if(m_drawState)
    {
        states.transform *= getTransform();
        target.draw(m_circle, states);
        target.draw(m_text, states);
    }
}


// *** Friend Functions ****

std::ostream& operator <<(std::ostream& os, const Circle& obj)
{
    static constexpr int PRINT_WIDTH = 8;
    std::ios_base::fmtflags oldFlags = os.flags();

    sf::Color color = obj.getColor();
    sf::Vector2f position = obj.getPosition();
    sf::Vector2f scale = obj.getScale();

    os << std::fixed << std::setprecision(2);

    os << "id:           "  << obj.m_id << "\n";
    os << "name:         "  << obj.m_displayName << "\n";
    os << "draw state:   "  << obj.m_drawState << "\n";
    os << "radius:       "  << std::setw(PRINT_WIDTH) << obj.getRadius() << "\n"; 
    os << "scale      x: "  << std::setw(PRINT_WIDTH) << scale.x  
                            << ", y: " << std::setw(PRINT_WIDTH) << scale.y << "\n"; 
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



/**** Getter Functions  *****/

sf::Color Circle::getColor()const 
{
    return m_circle.getFillColor();
}

std::string Circle::getDisplayName() const 
{
    return m_displayName;
}

bool Circle::getDrawState() const 
{ 
    return m_drawState;
}

std::string Circle::getId() const 
{
    return m_id;
}

sf::Vector2f Circle::getPosition()const 
{
    return m_circle.getPosition();
}

float Circle::getRadius()const
{
    return m_circle.getRadius();
}

sf::Vector2f Circle::getScale()const 
{
    return m_circle.getScale();
}

sf::Vector2f Circle::getVelocity() const 
{
    return m_velocity;
}


// *** Setter Functions ***

void Circle::setColor(sf::Color color)
{
    m_circle.setFillColor(color);
}

void Circle::setDisplayName(const std::string& name)
{
    m_displayName = name;
    m_text.setString(m_displayName);
}

void Circle::setDrawState(bool state)
{
    m_drawState = state;
}

void Circle::setId(const std::string& id)
{
    m_id = id;
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
        std::cerr << "[WARNING] function: " << __PRETTY_FUNCTION__ 
            << ", radius: " << radius << " not within bounds {" 
            << MIN_RADIUS << ", "
            << MAX_RADIUS << "}, setting to default: " 
            << DEFAULT_RADIUS << "\n";  
        m_circle.setRadius(DEFAULT_RADIUS);
    }
}

void Circle::setScale(sf::Vector2f scale)
{
    m_circle.setScale(scale);
}

void Circle::setVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}