#pragma once 

#include <cstdint>
#include <string>
#include <vector>
#include <filesystem>


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>


struct WindowConfig{
    unsigned int width;
    unsigned int height;
    WindowConfig() : width(640U), height(480U) {}
    WindowConfig(int w, int h) : width(w), height(h) {}
};

struct FontConfig{
    std::string fileName;
    unsigned int fontSize;
    sf::Color color;
    FontConfig() : fileName("fonts/arial.ttf"), fontSize(32) {}
};

struct RectangleConfig{
    std::string shapeName;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float width;
    float height;
};


struct CircleConfig{
    std::string shapeName;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float radius;
};


struct GameConfig{
    WindowConfig window;
    FontConfig font;
    std::vector<RectangleConfig> rects;
    std::vector<CircleConfig>circles;
};


struct TextConfig{
    unsigned int characterSize;
    sf::Color fillColor;
};



// Returns working directory path
std::filesystem::path getWorkingDirectory(void);

// 
std::vector<std::filesystem::path> findFileRecursive(
    const std::filesystem::path& startPath, const std::string& filenameToFind);


bool readConfigFile(const std::string& fileName, GameConfig *gameConfig);

bool readVector2f(std::istringstream& iss, sf::Vector2f& v2);
bool readColor(std::istringstream& iss, sf::Color& color);


