#pragma once 

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>

// use namespace alias to reduce typing and enhance readability
namespace fs = std::filesystem;

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


struct TextConfig{
    unsigned int characterSize = 24;
    sf::Color fillColor = sf::Color::Black;
};



// Forward declare class Game as it's used before its full 
// defintion, so it can be made friend of GameConfig
class Game;

class GameConfig {
public:

    friend class Game;

    static constexpr const char* CONFIG_DIR_NAME = "assets/config";
    static constexpr const char* FONTS_DIR_NAME = "assets/fonts";

    GameConfig() = default;

    bool readConfigFile(const std::string& fileName);


private:

    // Data members 
    WindowConfig                    m_windowConfig;
    FontConfig                      m_fontConfig;
    std::vector<RectangleConfig>    m_rectConfig;
    std::vector<CircleConfig>       m_circleConfig;
    

    // Helper functions
    fs::path getWorkingDirectory(void);
    void fileOnlySearch(const std::string& targetFile);
    std::vector<fs::path> directoryAndFileSearch(const std::string& searchDirectory, const std::string& targetFile);
    void printPaths(const std::vector<fs::path>& paths);
    

    std::vector<std::filesystem::path> findFileRecursive(
        const std::filesystem::path& startPath, 
        const std::string& filenameToFind);

    

    bool readVector2f(std::istringstream& iss, sf::Vector2f& v2);
    bool readColor(std::istringstream& iss, sf::Color& color);

};
