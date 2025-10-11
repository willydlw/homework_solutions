#pragma once 

#include "gameConfig.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Game;

class Rectangle : public sf::Drawable, public sf::Transformable
{
    public:  
    
    friend class Game;

    Rectangle(  const RectangleConfig& rectConfig, 
                const sf::Font& font, 
                const TextConfig& textConfig);


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(const sf::Vector2u& boundary);


    void setColor(sf::Color color);
    void setDrawState(bool state);
    void setId(const std::string& id);
    void setDisplayName(const std::string& name);
    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);
    void setScale(sf::Vector2f scale);
    void setVelocity(sf::Vector2f velocity);

    
    sf::Color    getColor() const;
    bool         getDrawState() const;
    std::string  getId() const;
    std::string  getDisplayName() const;
    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getScale()const;
    sf::Vector2f getVelocity()const;
    

    friend std::ostream& operator << (std::ostream& os, const Rectangle& obj);

    private:
    sf::Text            m_text;
    bool                m_drawState = true;
    sf::Vector2f        m_velocity = {0.0f, 0.0f};
    std::string         m_id = "Default";
    std::string         m_displayName = "Default";
    
    sf::RectangleShape  m_rectangle;  
    

    void updateTextPosition(void);
};