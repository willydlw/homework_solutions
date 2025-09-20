#pragma once 

#include <cstdint>
#include <string>
#include <vector>
#include <filesystem>

#include <SFML/Graphics/Font.hpp>

struct VectorConfig{
    float x;
    float y;
    VectorConfig(): x(0.0f), y(0.0f){}
    VectorConfig(float x, float y): x(x), y(y){}
};

struct ColorRGB{
    std::uint8_t red;
    std::uint8_t green;
    std::uint8_t blue;
    ColorRGB() : red(255), green(255), blue(255) {} 
    ColorRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b) : 
        red(r), green(g), blue(b) {}
};

struct WindowConfig{
    unsigned int width;
    unsigned int height;
    WindowConfig() : width(640U), height(480U) {}
    WindowConfig(int w, int h) : width(w), height(h) {}
};

struct FontConfig{
    std::string fileName;
    int fontSize;
    ColorRGB color;
    FontConfig() : fileName("fonts/arial.ttf"), fontSize(32) {}
};

struct RectangleConfig{
    std::string shapeName;
    VectorConfig position;
    VectorConfig speed;
    ColorRGB color;
    float width;
    float height;
};


struct CircleConfig{
    std::string shapeName;
    VectorConfig position;
    VectorConfig speed;
    ColorRGB color;
    float radius;
};


struct GameConfig{
    WindowConfig window;
    FontConfig font;
    std::vector<RectangleConfig> rects;
    std::vector<CircleConfig>circles;
};


std::filesystem::path getWorkingDirectory(void);

std::vector<std::filesystem::path> findFileRecursive(
    const std::filesystem::path& startPath, const std::string& filenameToFind);

bool readConfigFile(const std::string& fileName, GameConfig *gameConfig);

bool initFont(sf::Font& font, const std::string& fontFileName);