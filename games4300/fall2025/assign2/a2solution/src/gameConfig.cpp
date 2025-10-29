#include <fstream>
#include <iostream>
#include <sstream>

#include "../include/fileUtility.h"
#include "../include/gameConfig.h"
#include "../include/logError.hpp"

// Default Color Constants

const sf::Color PlayerConfig::DEFAULT_FILL_COLOR = {0, 255, 0};
const sf::Color PlayerConfig::DEFAULT_OUTLINE_COLOR = {255, 0, 255};

const sf::Color EnemyConfig::DEFAULT_OUTLINE_COLOR = {0, 0, 0};

const sf::Color BulletConfig::DEFAULT_FILL_COLOR = {255, 255, 255};
const sf::Color BulletConfig::DEFAULT_OUTLINE_COLOR = {255, 255, 255};




/*  Config Struct Friend Functions  */

std::ostream& operator << (std::ostream& os, const sf::Color& obj)
{
    os << "   red   \t" << (int)obj.r    << "\n";
    os << "   green \t" << (int)obj.g    << "\n";
    os << "   blue  \t" << (int)obj.b    << "\n";
    return os;
}

std::ostream& operator << (std::ostream& os, const WindowConfig& obj)
{
    os  << "width            " << obj.width             << "\n"
        << "height           " << obj.height            << "\n"
        << "frame limit      " << obj.frameLimit        << "\n"
        << "fullscreen mode  " << obj.fullScreenMode    << "\n";
    return os;
}

std::ostream& operator << (std::ostream& os, const FontConfig& obj)
{
    os  << "file name   \t" << obj.fileName << "\n"
        << "size        \t" << obj.size     << "\n"
        << "color\n"        << obj.color    << "\n";
    return os;
}

std::ostream& operator << (std::ostream& os, const PlayerConfig& obj)
{
    os  << "shape radius     \t" << obj.shapeRadius     << "\n"
        << "collision radius \t" << obj.collisionRadius << "\n"
        << "speed            \t" << obj.speed           << "\n\n"
        << "fill color\n"        << obj.fillColor       << "\n"
        << "outline color\n"     << obj.outlineColor    << "\n"
        << "outline thickness\t" << obj.outlineThickness << "\n"
        << "shape vertices   \t" << obj.shapeVertices   << "\n";

    return os;
}

std::ostream& operator << (std::ostream& os, const EnemyConfig& obj)
{
    os  << "shape radius      \t" << obj.shapeRadius        << "\n"
        << "collision radius  \t" << obj.collisionRadius    << "\n"
        << "min speed         \t" << obj.minSpeed           << "\n"
        << "max speed         \t" << obj.maxSpeed           << "\n\n"
        << "outline color\n"      << obj.outlineColor       << "\n"
        << "outline thickness \t" << obj.outlineThickness   << "\n"
        << "min vertices      \t" << obj.minVertices        << "\n"
        << "max vertices      \t" << obj.maxVertices        << "\n"
        << "small lifespan    \t" << obj.smallLifespan      << "\n"
        << "spawn interval    \t" << obj.spawnInterval      << "\n";

    return os;
}

std::ostream& operator << (std::ostream& os, const BulletConfig& obj)
{
    os  << "shape radius       \t" << obj.shapeRadius       << "\n"
        << "collision radius   \t" << obj.collisionRadius   << "\n"
        << "speed              \t" << obj.speed             << "\n\n"
        << "fill color\n"          << obj.fillColor
        << "outline color\n"       << obj.outlineColor      << "\n"
        << "outline thickness  \t" << obj.outlineThickness  << "\n"
        << "shape vertices     \t" << obj.shapeVertices     << "\n"
        << "lifespan           \t" << obj.lifespan          << "\n";

    return os;
}


void GameConfig::findAndOpenConfigFile(std::ifstream& infile, 
                    const std::string& assetPath, 
                    const std::string& filename)
{
    std::vector<std::filesystem::path> foundFiles = searchDirectory(assetPath, filename);
    if(foundFiles.empty())
    {
        LOG_ERROR(filename, " not found in directory: ", assetPath);
        return;
    }

    for(const auto& f : foundFiles)
    {
        infile.open(f);
        if(infile.is_open())
        {
            LOG_INFO("opened file: ", f);
            return;
        }
    }
}


bool GameConfig::readConfigFile(const std::string& filename)
{
    std::ifstream infile;
    findAndOpenConfigFile(infile, CONFIG_DIR_PATH, filename);
    if(!infile.is_open())
    {
        LOG_ERROR("failed to open any of the found configuration files");
        return false;
    }

    std::string line;
    while(std::getline(infile, line))
    {
        // since we declare iss object each time through the loop
        // if the stream enters a fail state in one of the reads 
        // below, the old object will destruct and we don't have to clear 
        // the flags
        std::istringstream iss(line);
        std::string firstWord;
        iss >> firstWord;

        if(firstWord == "Window")
        {
            if(!readWindowConfig(iss))
            {
                LOG_WARNING("failed to read Window configuration input: ", line);
            }
            continue;
        }
        else if(firstWord == "Font")
        {
            if(!readFontConfig(iss))
            {
                LOG_WARNING("failed to read Font configuration input: ", line);
            }
            continue;
        }
        else if(firstWord == "Player")
        {
            if(!readPlayerConfig(iss))
            {
                LOG_WARNING("failed to read Player configuration input: ", line);
            }
            continue;
        }
        else if(firstWord == "Enemy")
        {
            if(!readEnemyConfig(iss))
            {
                LOG_WARNING("failed to read Enemy configuration input: ", line);
            }
            continue;
        }
        else if(firstWord == "Bullet")
        {
            if(!readBulletConfig(iss))
            {
                LOG_WARNING("failed to read Bullett configuration input: ", line);
            }
            continue;
        }
        else 
        {
            LOG_WARNING("Unknown first word: ", firstWord, "discarding input: ", line);
        }
    }

    infile.close();
    return true;
}

bool GameConfig::readWindowConfig(std::istringstream& iss)
{
    if( !(iss >> m_windowConfig.width) ||
        !(iss >> m_windowConfig.height) || 
        !(iss >> m_windowConfig.frameLimit) || 
        !(iss >> m_windowConfig.fullScreenMode))
    {
        return false;
    }
    
    return true;
}

bool GameConfig::readFontConfig(std::istringstream& iss)
{
    if( !(iss >> m_fontConfig.fileName) ||
        !(iss >> m_fontConfig.size)     ||
        !(readColor(iss, m_fontConfig.color)))
    {
        return false;
    }
    return true;
}

bool GameConfig::readPlayerConfig(std::istringstream& iss)
{
    if( !(iss >> m_playerConfig.shapeRadius)            ||
        !(iss >> m_playerConfig.collisionRadius)        ||
        !(iss >> m_playerConfig.speed)                  ||
        !(readColor(iss, m_playerConfig.fillColor))     ||
        !(readColor(iss, m_playerConfig.outlineColor))  ||
        !(iss >> m_playerConfig.outlineThickness)       ||
        !(iss >> m_playerConfig.shapeVertices))
    {
        return false;
    }
    return true;
}

bool GameConfig::readEnemyConfig(std::istringstream& iss)
{
     if( !(iss >> m_enemyConfig.shapeRadius)            ||
        !(iss >> m_enemyConfig.collisionRadius)         ||
        !(iss >> m_enemyConfig.minSpeed)                ||
        !(iss >> m_enemyConfig.maxSpeed)                ||
        !(readColor(iss, m_enemyConfig.outlineColor))   ||
        !(iss >> m_enemyConfig.outlineThickness)        ||
        !(iss >> m_enemyConfig.minVertices)             ||
        !(iss >> m_enemyConfig.maxVertices)             ||
        !(iss >> m_enemyConfig.smallLifespan)           ||
        !(iss >> m_enemyConfig.spawnInterval))
    {
        return false;
    }
    return true;
}

bool GameConfig::readBulletConfig(std::istringstream& iss)
{
    if( !(iss >> m_bulletConfig.shapeRadius)            ||
        !(iss >> m_bulletConfig.collisionRadius)        ||
        !(iss >> m_bulletConfig.speed)                  ||
        !(readColor(iss, m_bulletConfig.fillColor))     ||
        !(readColor(iss, m_bulletConfig.outlineColor))  ||
        !(iss >> m_bulletConfig.outlineThickness)       ||
        !(iss >> m_bulletConfig.shapeVertices)          ||
        !(iss >> m_bulletConfig.lifespan))
    {
        return false;
    }

    return true;
}


/* sf::color type uint8_t 
   istringstream operator >> interprets uint8_t as unsigned char
   
   If we try iss >> color.r, only the character 2 will be extracted
   from the input 255. 
   
   To read the entire value of 255, we declare local unsigned int 
   variables to extract the entire value and then cast unsigned int 
   to uint8_t when assigning to color fields

*/ 
            
bool GameConfig::readColor(std::istringstream& iss, sf::Color& color)
{
    // sf::Color variables are type uint8_t. Input string stream will 
    // only read one character of uint8_t. For example, when the input 
    // value is 150, only the 1 will be read.
    // To avoid this, we use intermediate unsigned int variables 
    // to extract the whole value and then case to uint8_t
    unsigned int red, green, blue;      // 
    if( !(iss >> red)   ||
        !(iss >> green) ||
        !(iss >> blue))
    {
        std::cerr << "[ERROR] function " << __PRETTY_FUNCTION__ 
            << ", failed to read r,g, or b values\n";
        return false;
    }   

    color.r = static_cast<uint8_t>(red);
    color.g = static_cast<uint8_t>(green);
    color.b = static_cast<uint8_t>(blue);
    return true;
}


std::ostream& operator << (std::ostream& os, const GameConfig& gc)
{
    #define ANSI_BOLD       "\033[1m"
    #define ANSI_UNDERLINE  "\033[4m"
    #define ANSI_RESET      "\033[0m"
    os << ANSI_BOLD << "\n=== Game Configuration ===\n" << ANSI_RESET
       << ANSI_UNDERLINE << "\nWindow Config\n" << ANSI_RESET << gc.m_windowConfig
       << ANSI_UNDERLINE << "\nFont Config\n"   << ANSI_RESET << gc.m_fontConfig 
       << ANSI_UNDERLINE << "\nPlayer Config\n" << ANSI_RESET << gc.m_playerConfig
       << ANSI_UNDERLINE<< "\nEnemy Config\n"   << ANSI_RESET << gc.m_enemyConfig
       << ANSI_UNDERLINE<< "\nBullet Config\n"  << ANSI_RESET << gc.m_bulletConfig
       << "\n";
    return os;
}