#pragma once 

#include <filesystem>
#include <string>
#include <vector>
#include <SFML/Graphics/Color.hpp>

static constexpr int DEFAULT_SHAPE_RADIUS = 10;
static constexpr int DEFAULT_COLLISION_RADIUS = 10;
static constexpr int DEFAULT_LIFESPAN = 60;
static constexpr int DEFAULT_SHAPE_VERTICES = 8;

struct WindowConfig
{
    unsigned int width = 640U;
    unsigned int height = 480U;
    int frameLimit = 60;
    int fullScreenMode = 0;         // 1 yes, 0 no
    WindowConfig() = default;
    WindowConfig(int w, int h, int flimit, int screenMode) :
        width(w), height(h), frameLimit(flimit), fullScreenMode(screenMode){}
};


struct FontConfig
{
    std::string fileName = "arial.ttf";
    unsigned int size = 24U;
    sf::Color color = {sf::Color::Black};
    FontConfig() = default;
    FontConfig(const std::string& fName, int fsize, const sf::Color& fcolor) :
        fileName(fName), size(fsize), color(fcolor) {}
};

struct PlayerConfig
{
    int shapeRadius = DEFAULT_SHAPE_RADIUS;
    int collisionRadius = DEFAULT_COLLISION_RADIUS;
    float speed = 0.0f;                                 // pixels per frame, magnitude 
    sf::Color fillColor = {sf::Color::White};
    sf::Color outlineColor = {sf::Color::Black};
    int outlineThickness = 1;
    int shapeVertices = DEFAULT_SHAPE_VERTICES;          // number of circle shape points

    PlayerConfig() = default;
};


struct EnemyConfig
{
    int shapeRadius = DEFAULT_SHAPE_RADIUS;
    int collisionRadius = DEFAULT_COLLISION_RADIUS;
    float minSpeed = 0;
    float maxSpeed = 10;
    sf::Color outlineColor = sf::Color::Black;
    int outLineThickness = 1;
    int minVertices = 3;
    int maxVertices = 30;
    int smallLifespan = DEFAULT_LIFESPAN;
    int spawnInterval = 60;

    EnemyConfig() = default;
};

struct BulletConfig 
{
    int shapeRadius = DEFAULT_SHAPE_RADIUS;
    int collisionRadius = DEFAULT_COLLISION_RADIUS;
    float speed = 0.0f;
    sf::Color fillColor = sf::Color::Green;
    sf::Color outlineColor = sf::Color::Black;
    int outLineThickness = 1;
    int shapeVertices = DEFAULT_SHAPE_VERTICES;
    int lifespan = DEFAULT_LIFESPAN;
};



// Forward declare class Game because it's used before it's full 
// definition as a friend of GameConfig
class Game;

class GameConfig
{
    public:

    friend class Game;

    static constexpr const char* CONFIG_DIR_NAME = "assets/config";
    static constexpr const char* FONTS_DIR_NAME = "assets/fonts";

    GameConfig() = default;

    bool readConfigFile(const std::string& fileName);

    private:

    // Data members 
    WindowConfig            m_windowConfig;
    FontConfig              m_fontConfig;
    PlayerConfig            m_playerConfig;
    EnemyConfig             m_enemyConfig;

    // Helper functions 
    std::filesystem::path getWorkingDirectory();

    // Searches the target directory and its subdirectories for the target file 
    // Returns all directory paths found
    std::vector<std::filesystem::path> searchDirectory(
        const std::string& targetDirectory, const std::string& targetFile);

    std::vector<std::filesystem::path> findFileRecursive( 
        const std::filesystem::path& startPath, 
        const std::string& targetFile);

    void printPaths(const std::vector<std::filesystem::path>& paths);
};