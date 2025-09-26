#pragma once 
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <string_view>
#include <memory>

class Circle : public sf::Drawable, public sf::Transformable
{
    public:
    static constexpr float MIN_RADIUS = 5.0f;
    static constexpr float MAX_RADIUS = 50.0f;
    static constexpr float DEFAULT_RADIUS = 10.0f;

    static constexpr sf::Vector2f DEFAULT_POSITION = {0.0f, 0.0f};
    static constexpr sf::Vector2f DEFAULT_VELOCITY = {1.0f, 1.0f};

    static constexpr std::string_view DEFAULT_NAME = {"Default"};

    Circle(const CircleConfig* circleConfig, const TextConfig* textConfig);

    // Separate intialization function for text object due 
    //void initText(const sf::Font &font, sf::Color fontColor, int fontSize);

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
    sf::Font m_font;
    sf::Text m_text;
    sf::Vector2f      m_velocity;

    sf::CircleShape   m_circle;   
    std::string       m_name;

   

    void updateTextPosition(void);

};