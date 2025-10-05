#pragma once 

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "gameConfig.h"
#include "rectangle.h"
#include "circle.h"

union ShapeObject
{
    Circle*    circptr;
    Rectangle* rectptr;
};



class Game
{
    public:

    static constexpr int FRAME_RATE = 60;
    static constexpr float MIN_VELOCITY = -5.0f;
    static constexpr float MAX_VELOCITY = 5.0f;
    static constexpr float MIN_SCALE = 0.25f;
    static constexpr float MAX_SCALE = 5.0f;

    Game();
    
    void init(const std::string& configFileName);

    void run(void);


    friend std::ostream& operator << (std::ostream& os, const Game& obj);

    

    private:

    sf::RenderWindow        m_window;
    sf::Font                m_font;
    sf::Clock               m_deltaClock;   // for ImGui's internal timing

    
    std::vector<Rectangle>   m_rectangles;
    std::vector<Circle>      m_circles;
    std::map<std::string, ShapeObject>      m_shapeMap;
    std::vector<const char*> m_shapeNames;      // gui requires const char*
    GameConfig               m_gameConfig;
    
    

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
   
    void initShapeMap(void);
    void initShapeNames(void);
    void initWindow(void);


    sf::Color floatColorToUint(float fcolors[3]);
    void sfColorToFloat(sf::Color color, float fcolors[3]);

    void update(void);
    void draw(void);

    void printColor(const sf::Color& color);
    void printColor(const float* color, int n);
};



