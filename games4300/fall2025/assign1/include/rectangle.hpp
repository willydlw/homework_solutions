#pragma once 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Rectangle{
    public:
    static constexpr sf::Vector2f DEFAULT_SIZE = {10.0f, 15.0f};
    static constexpr std::string_view DEFAULT_NAME = "Default";
    

    Rectangle(sf::Vector2f size = DEFAULT_SIZE,
                std::string name = std::string(DEFAULT_NAME)
            );

    void setName(std::string& name);
    void setSize(sf::Vector2f size);


    std::string getName() const;
    sf::Vector2f getSize() const;


    friend std::ostream& operator << (std::ostream& os, const Rectangle& obj);

    private:
    sf::RectangleShape m_rectangle;
    sf::Vector2f m_velocity;
    std::string m_name;

};