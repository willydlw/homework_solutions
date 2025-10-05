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
    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);
    void setScale(sf::Vector2f scale);

    
    sf::Color    getColor() const;
    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getScale()const;
    

    friend std::ostream& operator << (std::ostream& os, const Rectangle& obj);

    private:
    sf::Text            m_text;
    bool                m_drawable = true;
    sf::Vector2f        m_velocity = {0.0f, 0.0f};
    std::string         m_name = "Default";
    
    sf::RectangleShape  m_rectangle;  
    

    void updateTextPosition(void);
};