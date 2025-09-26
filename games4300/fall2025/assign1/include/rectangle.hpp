#pragma once 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Rectangle : public sf::Drawable, public sf::Transformable
{
    public:
    static constexpr sf::Vector2f DEFAULT_SIZE = {10.0f, 15.0f};
    static constexpr std::string_view DEFAULT_NAME = "Default";
    static constexpr sf::Vector2f DEFAULT_VELOCITY = {1.0f, 1.0f};
    static constexpr sf::Vector2f DEFAULT_POSITION = {0.0f, 0.0f};
    static constexpr sf::Color DEFAULT_COLOR = {255, 255, 255};
    

    Rectangle(const RectConfig* rectConfigt, const TextConfig* textConfig);

    void initText(const sf::Font &font, sf::Color fontColor, int fontSize);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(const sf::Vector2u& boundary);

    void setColor(sf::Color color);
    void setName(std::string& name);
    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);
    void setVelocity(sf::Vector2f velocity);
    


    sf::Color    getColor() const;
    std::string  getName() const;
    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;


    friend std::ostream& operator << (std::ostream& os, const Rectangle& obj);

    private:
    sf::RectangleShape m_rectangle;
    sf::Vector2f m_velocity;
    std::string m_name;

    // sf::Text does not have a default constructor (SFML 3)
    // To get around this, will create a pointer to text as a class attribute
    std::unique_ptr<sf::Text> m_text;
};