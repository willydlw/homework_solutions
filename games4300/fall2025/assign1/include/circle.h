#pragma once 
#include <SFML/Graphics.hpp>

#include <iostream>

#include "gameConfig.h"
#include "shape.h"

class Circle : public Shape, public sf::Drawable, public sf::Transformable
{
    public:
    static constexpr float MIN_RADIUS = 5.0f;
    static constexpr float MAX_RADIUS = 200.0f;
    static constexpr float DEFAULT_RADIUS = 10.0f;

   
    // Constructor
    Circle( const CircleConfig& circleConfig, 
            const ShapeConfig&  shapeConfig,
            const sf::Font& font,
            const TextConfig& textConfig);

    // 
    void update(const sf::Vector2u& boundary);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    // Setter Member Functions
    void setPosition(sf::Vector2f position);
    void setRadius(float radius);
    void setColor(sf::Color color);
    

    // Getter Member Functions
    sf::Vector2f getPosition()const;
    float getRadius()const;
    sf::Color getColor()const;
    

    // Friend functions
    friend std::ostream& operator <<(std::ostream& os, const Circle& obj);

    private:

    // Data members 
    sf::CircleShape   m_circle;  
   
    // private helper functions
    void updateTextPosition(void);

};