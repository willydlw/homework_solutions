#pragma once 

#include <iostream>

#include <SFML/Graphics.hpp>

#include "gameConfig.hpp"
#include "rectangle.hpp"
#include "circle.hpp"


class Game
{
    public:

    Game();
    
    void init(const GameConfig *gc);


    void update();
    void draw(sf::RenderWindow& window);


    friend std::ostream& operator << (std::ostream& os, const Game& obj);

    private:

    sf::Font m_font;
    std::vector<Rectangle> m_rectangles;
    std::vector<Circle> m_circles;

    // private member functions
    private:

    bool initFont(const std::string& fontFileName);
    void initRectangles(const std::vector<RectangleConfig>& rConfig);
    void initCircles(const std::vector<CircleConfig>& cConfig);

};



