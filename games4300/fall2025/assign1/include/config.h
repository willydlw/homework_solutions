#pragma once 

#include <string>
#include <vector>

struct VectorConfig{
    float x;
    float y;
};

struct ColorRGB{
    int red;
    int green;
    int blue;
};

struct WindowConfig{
    int width;
    int height;
};

struct FontConfig{
    std::string fileName;
    int fontSize;
    ColorRGB color;
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

bool readConfigFile(const std::string& fileName, GameConfig *gameConfig);