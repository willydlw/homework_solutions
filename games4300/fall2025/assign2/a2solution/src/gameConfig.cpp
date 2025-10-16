#include <fstream>
#include <iostream>
#include <sstream>

#include "gameConfig.h"
#include "logError.hpp"

 std::filesystem::path GameConfig::getWorkingDirectory()
 {
    try
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        return currentPath;
    } 
    catch (const std::filesystem::filesystem_error& e)
    {
        LOG_ERROR("\n\terror description: ", e.what());
        return {};
    }
 }


std::vector<std::filesystem::path> GameConfig::searchDirectory(
        const std::string& targetDirectory, const std::string& targetFile)
{
    std::vector<std::filesystem::path> foundFiles = findFileRecursive(targetDirectory, targetFile);

    if(foundFiles.empty())
    {
        std::filesystem::path workingDirectory = getWorkingDirectory();

        LOG_WARNING("\n\ttargetFile: ", targetFile, " not found in directory: ", targetDirectory);
        LOG_INFO("\n\tRecovery attempt, searching directory path: " , workingDirectory);

        foundFiles = findFileRecursive(workingDirectory, targetFile);
        if(foundFiles.empty())
        {
            LOG_WARNING("\n\ttargetFile: ", targetFile, " not found in directory: ", targetDirectory);
        }
        else 
        {
            std::ostringstream oss;
            for(const auto& file : foundFiles)
            {
                oss << "\t" << file << "\n";
            }

            LOG_INFO("\n\tRecovery results, found ", targetFile, " in directory: ", workingDirectory,"\n", oss.str());
        }
    }

    return foundFiles;
}


std::vector<std::filesystem::path> GameConfig::findFileRecursive( 
        const std::filesystem::path& targetPath, 
        const std::string& targetFile)
{
    std::vector<std::filesystem::path> foundFiles; 

    if(!std::filesystem::exists(targetPath) || !std::filesystem::is_directory(targetPath))
    {
        LOG_ERROR("targetPath: ", targetPath, "does not exist or is not a directory");
        return foundFiles;
    }

    // iterate through the directory recursively 
    for(const auto& entry : std::filesystem::recursive_directory_iterator(targetPath))
    {
        if(entry.is_regular_file() && entry.path().filename() == targetFile)
        {
            foundFiles.push_back(entry.path());
        }
    }

    return foundFiles;
}


void GameConfig::printPaths(const std::vector<std::filesystem::path>& paths)
{
    for(const auto& path : paths)
    {
        std::cout << path << "\n";
    }

    std::cout << std::endl;
}


bool GameConfig::readConfigFile(const std::string& fileName)
{
    std::ifstream inFile;
    std::vector<std::filesystem::path> foundFiles = searchDirectory(CONFIG_DIR_NAME, fileName);

    if(foundFiles.empty())
    {
        LOG_ERROR(fileName, " not found in directory: ", CONFIG_DIR_NAME);
        return false;
    }

    for(const auto& f : foundFiles)
    {
        inFile.open(f);
        if(inFile.is_open())
        {
            LOG_INFO("opened file: ", f);
            break;
        }
        else
        {
            LOG_WARNING("failed to open file: ", f);
        }

        if(!inFile.is_open())
        {
            LOG_ERROR("failed to open any of the found configuration files");
            return false;
        }

        std::string line;
        while(std::getline(inFile, line))
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
                    LOG_WARNING("failed to read Font configuration, input: ", line);
                }
                continue;
            }
            else if(firstWord == "Player")
            {
                if(!readPlayerConfig(iss))
                {
                    LOG_WARNING("failed to read Player configuration, input: ", line);
                }
                continue;
            }
            else if(firstWord == "Enemy")
            {
                if(!readEnemyConfig(iss))
                {
                    LOG_WARNING("failed to read Enemy configuration, input: ", line);
                }
                continue;
            }
            else if(firstWord == "Bullet")
            {
                if(!readBulletConfig(iss))
                {
                    LOG_WARNING("failed to read Bullett configuration, input: ", line);
                }
                continue;
            }
            else 
            {
                LOG_WARNING("Unknown first word: ", firstWord, "discarding input: ", line);
            }
        }
    }


    inFile.close();
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
    if( !(iss >> m_playerConfig.shapeRadius)        ||
        !(iss >> m_playerConfig.collisionRadius)    ||
        !(iss >> m_playerConfig.speed)              ||
        !(readColor(iss, m_playerConfig.fillColor)) ||
        !(readColor(iss, m_playerConfig.outlineColor)) ||
        !(iss >> m_playerConfig.outlineThickness)   ||
        !(iss >> m_playerConfig.shapeVertices))
    {
        return false;
    }
    return true;
}

bool GameConfig::readEnemyConfig(std::istringstream& iss)
{
     if( !(iss >> m_enemyConfig.shapeRadius)         ||
        !(iss >> m_enemyConfig.collisionRadius)     ||
        !(iss >> m_enemyConfig.minSpeed)            ||
        !(iss >> m_enemyConfig.maxSpeed)            ||
        !(readColor(iss, m_enemyConfig.outlineColor)) ||
        !(iss >> m_enemyConfig.outLineThickness)    ||
        !(iss >> m_enemyConfig.smallLifespan)       ||
        !(iss >> m_enemyConfig.spawnInterval))
    {
        return false;
    }
    return true;
}

bool GameConfig::readBulletConfig(std::istringstream& iss)
{
    if( !(iss >> m_bulletConfig.shapeRadius)        ||
        !(iss >> m_bulletConfig.collisionRadius)    ||
        !(iss >> m_bulletConfig.shapeRadius)        ||
        !(readColor(iss, m_bulletConfig.fillColor)) ||
        !(readColor(iss, m_bulletConfig.outlineColor)) ||
        !(iss >> m_bulletConfig.outLineThickness)   ||
        !(iss >> m_bulletConfig.shapeVertices)      ||
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
    unsigned red, green, blue;
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