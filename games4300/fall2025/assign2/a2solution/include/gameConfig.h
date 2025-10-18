#pragma once 

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

// Forward declarations
struct BulletConfig; 
struct ColorConfig;
struct EnemyConfig;
struct FontConfig;
struct PlayerConfig;
struct WindowConfig;

// Constant expressions
static constexpr int DEFAULT_SHAPE_RADIUS       = 10;
static constexpr int DEFAULT_COLLISION_RADIUS   = 10;

static constexpr int DEFAULT_LIFESPAN           = 60;
static constexpr int DEFAULT_SPAWN_INTERVAL     = 60;

static constexpr int DEFAULT_MIN_SHAPE_VERTICES = 3;
static constexpr int DEFAULT_MAX_SHAPE_VERTICES = 32;
static constexpr int DEFAULT_SHAPE_VERTICES     = 8;

static constexpr int DEFAULT_OUTLINE_THICKNESS  = 1;

static constexpr float DEFAULT_SPEED_PIXELS_PER_FRAME   = 0;
static constexpr float DEFAULT_MIN_SPEED                = 0;
static constexpr float DEFAULT_MAX_SPEED                = 10;




/* For debugging purposes, not using sf::Color because the data fields 
   are uint8_t and will be output as characters when used with some 
   templated debugging print functions.
*/
struct ColorConfig
{
    int red = 0;
    int green = 0;
    int blue = 0;
    ColorConfig() = default;
    constexpr ColorConfig(int r, int g, int b) : red(r), green(g), blue(b) {}
    
    friend std::ostream& operator << (std::ostream& os, const ColorConfig& obj);
};

static constexpr ColorConfig DEFAULT_FILL_COLOR = {255,255,255}; 
static constexpr ColorConfig DEFAULT_OUTLINE_COLOR = {0, 0, 0};

struct WindowConfig
{
    unsigned int width = 640U;
    unsigned int height = 480U;
    int frameLimit = 60;
    int fullScreenMode = 0;         // 1 yes, 0 no
    WindowConfig() = default;
    WindowConfig(int w, int h, int flimit, int screenMode) :
        width(w), height(h), frameLimit(flimit), fullScreenMode(screenMode){}

    friend std::ostream& operator << (std::ostream& os, const WindowConfig& obj);
};


struct FontConfig
{
    std::string fileName = "arial.ttf";
    unsigned int size = 24U;
    ColorConfig color;
    FontConfig() = default;
    FontConfig(const std::string& fName, int fsize, const ColorConfig& fcolor) :
        fileName(fName), size(fsize), color(fcolor) {}

    friend std::ostream& operator << (std::ostream& os, const FontConfig& obj);
};


struct PlayerConfig
{
    int shapeRadius             = DEFAULT_SHAPE_RADIUS;
    int collisionRadius         = DEFAULT_COLLISION_RADIUS;
    float speed                 = DEFAULT_SPEED_PIXELS_PER_FRAME ;  // pixels per frame, magnitude 
    ColorConfig fillColor       = DEFAULT_FILL_COLOR;
    ColorConfig outlineColor    = DEFAULT_OUTLINE_COLOR;                                
    int outlineThickness        = DEFAULT_OUTLINE_THICKNESS;
    int shapeVertices           = DEFAULT_SHAPE_VERTICES;          // number of circle shape points

    PlayerConfig() = default;

    friend std::ostream& operator << (std::ostream& os, const PlayerConfig& obj);
};


struct EnemyConfig
{
    int shapeRadius             = DEFAULT_SHAPE_RADIUS;
    int collisionRadius         = DEFAULT_COLLISION_RADIUS;
    float minSpeed              = DEFAULT_MIN_SPEED;
    float maxSpeed              = DEFAULT_MAX_SPEED;
    ColorConfig outlineColor    = DEFAULT_OUTLINE_COLOR;
    int outLineThickness        = DEFAULT_OUTLINE_THICKNESS;
    int minVertices             = DEFAULT_MIN_SHAPE_VERTICES;
    int maxVertices             = DEFAULT_MAX_SHAPE_VERTICES;
    int smallLifespan           = DEFAULT_LIFESPAN;
    int spawnInterval           = DEFAULT_SPAWN_INTERVAL;

    EnemyConfig() = default;

    friend std::ostream& operator << (std::ostream& os, const EnemyConfig& obj);
};

struct BulletConfig 
{
    int shapeRadius             = DEFAULT_SHAPE_RADIUS;
    int collisionRadius         = DEFAULT_COLLISION_RADIUS;
    float speed                 = DEFAULT_SPEED_PIXELS_PER_FRAME;
    ColorConfig fillColor       = DEFAULT_FILL_COLOR;
    ColorConfig outlineColor    = DEFAULT_OUTLINE_COLOR;
    int outLineThickness        = DEFAULT_OUTLINE_THICKNESS;
    int shapeVertices           = DEFAULT_SHAPE_VERTICES;
    int lifespan                = DEFAULT_LIFESPAN;

    friend std::ostream& operator << (std::ostream& os, const BulletConfig& obj);
};




// Forward declare class Game because it's used before it's full 
// definition as a friend of GameConfig
class Game;

class GameConfig
{
    public:

    friend class Game;

    static constexpr const char* CONFIG_DIR_PATH = "assets/config";
    static constexpr const char* FONTS_DIR_PATH = "assets/fonts";

    GameConfig() = default;

    // Searches CONFIG_DIR_PATH for filename
    // If not found, will search current working directory.
    bool readConfigFile(const std::string& filename);
    
    // Note: these were added for testing this class to have access 
    // to provide the test class access to private data content.
    BulletConfig getBulletConfig() { return m_bulletConfig;}
    FontConfig   getFontConfig() { return m_fontConfig; }
    PlayerConfig getPlayerConfig() { return m_playerConfig;}
    EnemyConfig  getEnemyConfig()  { return m_enemyConfig;}
    WindowConfig getWindowConfig() { return m_windowConfig;}


    private:

    // Data members 
    WindowConfig            m_windowConfig;
    FontConfig              m_fontConfig;
    PlayerConfig            m_playerConfig;
    EnemyConfig             m_enemyConfig;
    BulletConfig            m_bulletConfig;

    // Helper functions 

    // Searches the target directory and its subdirectories for the target file 
    // Returns all directory paths found
    std::vector<std::filesystem::path> searchDirectory(
        const std::string& targetDirectory, const std::string& targetFile);

    // Returns program's current working directory (CWD). This is the directory 
    // in the file system where the program is currently operating. 
    // It is the default location for reading and writing files unless a program 
    // is given an absolute file path
    std::filesystem::path getWorkingDirectory();

    // Searches for the target file starting int the start path.
    // Recursively searches all sub-directories of the start path.
    // Returns array of paths where target file was found.
    // Return vector will be empty if target file was not found.
    std::vector<std::filesystem::path> findFileRecursive( 
        const std::filesystem::path& startPath, 
        const std::string& targetFile);

    // 
    void printPaths(const std::vector<std::filesystem::path>& paths);

    bool readWindowConfig(std::istringstream& iss);
    bool readFontConfig(std::istringstream& iss);
    bool readPlayerConfig(std::istringstream& iss);
    bool readEnemyConfig(std::istringstream& iss);
    bool readBulletConfig(std::istringstream& iss);

    bool readColor(std::istringstream& iss, ColorConfig& color);
};