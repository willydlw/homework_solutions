#pragma once 

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "gameConfig.h"
#include "rectangle.h"
#include "circle.h"


class Game
{
    public:

    static constexpr int FRAME_RATE = 60;

    Game();
    
    void init(const std::string& configFileName);

    void run(void);


    friend std::ostream& operator << (std::ostream& os, const Game& obj);

    

    private:

    sf::RenderWindow        m_window;
    sf::Font                m_font;
    sf::Clock               m_deltaClock;   // for ImGui's internal timing

    
    std::vector<Rectangle>  m_rectangles;
    std::vector<Circle>     m_circles;
    //std::vector<Shape*>     m_guiShapeList;
    GameConfig              m_gameConfig;
    
    

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


    void initCircles(void);
    void initGui(void);
    void initRectangles(void);
   
    //void initShapeNameList(void);
    void initWindow(void);

    void update(void);
    void draw(void);
};



