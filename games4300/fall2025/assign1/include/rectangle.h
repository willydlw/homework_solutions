#pragma once 

#include "gameConfig.h"
#include "shape.h"

#include <SFML/Graphics.hpp>
#include <iostream>



class Rectangle : public Shape 
{
    public:    

    Rectangle(  const RectangleConfig& rectConfig, 
                const ShapeConfig& shapeConfig,
                const sf::Font& font, 
                const TextConfig& textConfig);


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(const sf::Vector2u& boundary);


    void setColor(sf::Color color);
    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);

    


    sf::Color    getColor() const;
    
    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;
    

    friend std::ostream& operator << (std::ostream& os, const Rectangle& obj);

    private:
   
    sf::RectangleShape m_rectangle;
    

    void updateTextPosition(void);
};