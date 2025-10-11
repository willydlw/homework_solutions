#pragma once 
#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameConfig.h"

// forward declaration
class Game;

class Circle : public sf::Drawable, public sf::Transformable
{
    public:

    friend class Game;

    static constexpr float MIN_RADIUS = 5.0f;
    static constexpr float MAX_RADIUS = 200.0f;
    static constexpr float DEFAULT_RADIUS = 10.0f;

    // Constructor
    Circle( const CircleConfig& circleConfig, 
            const sf::Font& font,
            const TextConfig& textConfig);

    // 
    void update(const sf::Vector2u& boundary);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    // Setter Member Functions
    void setColor(sf::Color color);
    void setDrawState(bool state);
    void setDisplayName(const std::string& name);
    void setId(const std::string& id);
    void setPosition(sf::Vector2f position);
    void setRadius(float radius);  
    void setScale(sf::Vector2f scale);
    void setVelocity(sf::Vector2f velocity);
    
    // Getter Member Functions
    sf::Color       getColor()const;
    bool            getDrawState()const;
    std::string     getId()const;
    std::string     getDisplayName()const;
    sf::Vector2f    getPosition()const;
    float           getRadius()const; 
    sf::Vector2f    getScale()const;
    sf::Vector2f    getVelocity()const;
    

    // Friend function
    friend std::ostream& operator <<(std::ostream& os, const Circle& obj);

    private:

    // Data members 
    sf::Text            m_text;
    bool                m_drawState = true;
    sf::Vector2f        m_velocity = {0.0f, 0.0f};
    std::string         m_id = "Default";
    std::string         m_displayName = "Default";
    sf::CircleShape     m_circle;   
   
    // private helper functions
    void updateTextPosition(void);

};