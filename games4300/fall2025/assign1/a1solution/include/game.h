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

/* Why the union? So that one ImGui::Combo box can list both 
   Circle and Rectangle objects.
*/
union ShapeObject
{
    Circle*    circptr;
    Rectangle* rectptr;
};



class Game
{

public:

    // Class Constant Expressions
    static constexpr int FRAME_RATE = 60;
    static constexpr float MIN_VELOCITY = -8.0f;
    static constexpr float MAX_VELOCITY = 8.0f;
    static constexpr float MIN_SCALE = 0.0f;
    static constexpr float MAX_SCALE = 4.0f;

    // Constructor
    Game();
    
    // Controls initialization of all game elements
    void init(const std::string& configFileName);

    // Controls main game loop. Runs until window is closed.
    void run(void);

    // Overloaded operator << for debugging
    friend std::ostream& operator << (std::ostream& os, const Game& obj);

private:

    // Data members
    sf::RenderWindow                        m_window;
    sf::Font                                m_font;
    sf::Clock                               m_deltaClock;   // for ImGui's internal timing

    std::vector<Rectangle>                  m_rectangles;
    std::vector<Circle>                     m_circles;
    std::map<std::string, ShapeObject>      m_shapeMap;     
    std::vector<const char*>                m_shapeIds;      // Imgui requires const char*
    GameConfig                              m_gameConfig;
    
    
    // Initialization Helper Functions

    /*  Operation:
            Searches project directories for paths to fontFilename.
            Iterates though found paths until successfully opening font file.
        Return:
            Success - returns path to file opened 
            Failure - returns empty string
    */
    std::string initFont(const std::string& fontFileName);

    void initCircles();
    void initGui();
    void initRectangles();
   
    void initShapeMap();
    void initShapeIds();
    void initWindow();

    // ImGui helper functions
    void updateGui();
    sf::Color floatColorToUint(float fcolors[3]);
    void sfColorToFloat(sf::Color color, float fcolors[3]);

    // Main Game Loop helper functions
    void updateShapes();
    void drawShapes();

    // Debugging functions
    void printColor(const sf::Color& color);
    void printColor(const float* color, int n);
};



