#pragma once 

#include <cstdint>
#include <string>
#include <vector>
#include <filesystem>


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>


// Configuration Structures
struct WindowConfig{
    unsigned int width =  640U;
    unsigned int height = 480U;
};

struct FontConfig{
    std::string fileName = "arial.ttf";
    unsigned int fontSize = 24U;
    sf::Color color = {sf::Color::Blue};
};

struct ShapeConfig{
    std::string  name = "Default";
    sf::Vector2f velocity = {0.0f, 0.0f};
    sf::Vector2f position = {0.0f, 0.0f};
    sf::Color color       = {sf::Color::White};
};

struct RectangleConfig{
    ShapeConfig  shapeConfig;
    float width           = 0.0f;
    float height          = 0.0f;
};


struct CircleConfig{
    ShapeConfig shapeConfig;
    float radius = 0.0f;
};


/*
struct GameConfig{
    WindowConfig window;
    FontConfig font;
    std::vector<RectangleConfig> rects;
    std::vector<CircleConfig>circles;
};
*/


struct TextConfig{
    unsigned int characterSize;
    sf::Color fillColor;
};



// Forward declare class Game as it's used before its full 
// defintion, so it can be made friend of GameConfig
class Game;

class GameConfig {

public:
    // Declare Game class as friend of class GameConfig
    friend class Game;

    GameConfig() = default;

    bool readConfigFile(const std::string& fileName);


private:

    // Data members 
    WindowConfig                    m_windowConfig;
    FontConfig                      m_fontConfig;
    std::vector<RectangleConfig>    m_rectConfig;
    std::vector<CircleConfig>       m_circleConfig;
    

    // Helper functions

    std::filesystem::path getWorkingDirectory(void);

    std::vector<std::filesystem::path> findFileRecursive(
        const std::filesystem::path& startPath, 
        const std::string& filenameToFind);


    bool readVector2f(std::istringstream& iss, sf::Vector2f& v2);
    bool readColor(std::istringstream& iss, sf::Color& color);

};
