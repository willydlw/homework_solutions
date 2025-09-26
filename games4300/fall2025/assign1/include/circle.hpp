#pragma once 
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <string_view>

class Circle : public sf::Drawable, public sf::Transformable
{
    public:
    static constexpr float MIN_RADIUS = 5.0f;
    static constexpr float MAX_RADIUS = 50.0f;
    static constexpr float DEFAULT_RADIUS = 10.0f;

    static constexpr sf::Vector2f DEFAULT_POSITION = {0.0f, 0.0f};
    static constexpr sf::Vector2f DEFAULT_VELOCITY = {1.0f, 1.0f};

    static constexpr std::string_view DEFAULT_NAME = {"Default"};

    Circle( float radius = DEFAULT_RADIUS, 
            sf::Color color = sf::Color::Green,
            sf::Vector2f position = DEFAULT_POSITION,
            sf::Vector2f velocity = DEFAULT_VELOCITY,
            std::string name = std::string(DEFAULT_NAME)
          );


    void update(const sf::Vector2u& boundary);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    // Setter Member Functions
    void setPosition(sf::Vector2f position);
    void setRadius(float radius);
    void setColor(sf::Color color);
    void setName(std::string& name);
    void setVelocity(sf::Vector2f velocity);

    // Getter Member Functions
    sf::Vector2f getPosition()const;
    float getRadius()const;
    sf::Color getColor()const;
    std::string getName()const;

    // Friend functions
    friend std::ostream& operator <<(std::ostream& os, const Circle& obj);


    private:
    // Data members
    sf::CircleShape m_circle;   
    sf::Vector2f m_velocity;
    std::string  m_name;
};