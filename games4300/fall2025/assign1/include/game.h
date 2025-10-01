#pragma once 

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "gameConfig.h"
#include "rectangle.h"
#include "circle.h"


class Game
{
    public:

    Game();
    
    void init(const GameConfig *gc);


    void update(const sf::Vector2u& boundary);
    void draw(sf::RenderWindow& window);

    friend std::ostream& operator << (std::ostream& os, const Game& obj);

    // make this public to give ui access 
    std::vector<std::string> shapeNames;

    private:

    sf::Font m_font;
    std::vector<Rectangle> m_rectangles;
    std::vector<Circle> m_circles;
    

    // private member functions
    private:

    /*  Operation:
            Searches project directories for paths to fontFilename.
            Iterates though found paths until successfully opening font file.
        Return:
            Success - returns path to file opened 
            Failure - returns empty string
    */
    std::string initFont(const std::string& fontFileName);

    void initRectangles(const std::vector<RectangleConfig>& rConfig, const TextConfig& textConfig);

    void initCircles(const std::vector<CircleConfig>& cConfig, const TextConfig& textConfig);
    
    void initShapeNameList();

};



