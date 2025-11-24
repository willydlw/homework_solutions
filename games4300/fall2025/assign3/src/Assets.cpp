#include "Assets.h"
#include "Animation.hpp"

#include <SFML/Graphics.hpp>

#include <map>
#include <cassert>
#include <iostream>
#include <fstream>

Assets& Assets::Instance() 
{
    static Assets assets;
    return assets;
}


void Assets::addTexture(const std::string& textureName, const std::string& path, bool smooth)
{
    if(!m_textureMap[textureName].loadFromFile(path))
    {
        std::cerr << "[ERROR], function: " << __PRETTY_FUNCTION__
            << ", could not load texture file: " << path << std::endl;
        m_textureMap.erase(textureName);
    }
    else 
    {
        m_textureMap[textureName].setSmooth(smooth);
        std::cerr << "[SUCCESS] function: " << __PRETTY_FUNCTION__ 
            << ", loaded texture: " << path << std::endl;
    }
}

void Assets::addAnimation(  const std::string& animationName, 
                            const std::string& textureName, 
                            size_t frameCount, size_t animationSpeed)
{
    m_animationMap[animationName] 
        = Animation(animationName, textureName, frameCount, animationSpeed);
}

void Assets::addFont(const std::string& fontName, const std::string& path)
{
    m_fontMap[fontName] = sf::Font();
    if(!m_fontMap[fontName].openFromFile(path))
    {
        std::cerr << "[ERROR] function: " 
            << __PRETTY_FUNCTION__ << ", could not load font: " 
            << fontName << ", path: " << path << std::endl;
        m_fontMap.erase(fontName);
    }
    else 
    {
        std::cout << "[SUCCESS] function: " << __PRETTY_FUNCTION__ 
            << ", Loaded font: " << path << std::endl;
    }
}

void Assets::loadFromFile(const std::string& path)
{
    std::ifstream infile(path);
    if(!infile.is_open())
    {
        std::cerr << "[ERROR] function: " << __PRETTY_FUNCTION__ 
            << ", failed to open file, path: " << path << "\n";
        std::exit(EXIT_FAILURE);
    }

    while(infile.good())
    {
        std::string assetCategory;
        infile >> assetCategory;
        std::cerr << "iterating, read assetCategory: " << assetCategory << "\n";

        if(assetCategory == "Texture")
        {
            std::string name, path;
            if(infile >> name >> path){
                addTexture(name, path);
            }
            else {
                std::cerr << "[ERROR] function: " << __PRETTY_FUNCTION__ 
                    << ", asset category: " << assetCategory 
                    << ", FAILED to read name, path fields\n";
                break;
            }
        }
        else if(assetCategory == "Animation")
        {
            std::string animationName, textureName;
            size_t frameCount, animationSpeed;
            if(infile >> animationName >> textureName >> frameCount >> animationSpeed)
            {
                addAnimation(animationName, textureName, frameCount, animationSpeed);
            }
            else 
            {
                std::cerr << "[ERROR] function: " << __PRETTY_FUNCTION__ 
                    << ", asset category: " << assetCategory 
                    << ", FAILED to read animationName, textureName, frameCount, animationSpeed fields\n";
                break;
            }
        }
        else if( assetCategory == "Font")
        {
            std::string name, path;
            if(infile >> name >> path)
            {
                addFont(name, path);
            }
            else {
                std::cerr << "[ERROR] function: " << __PRETTY_FUNCTION__ 
                    << ", asset category: " << assetCategory 
                    << ", FAILED to read name, path fields\n";
                break;
            }
        }
        else 
        {
            std::cerr << "[WARNING] function: " << __PRETTY_FUNCTION__ 
                << " Asset Category Uknown: " << assetCategory << "\n";
            break;
        }
    }
    infile.close();
}


const sf::Texture& Assets::getTexture(const std::string& textureName) const
{
    return m_textureMap.at(textureName);
}

const Animation& Assets::getAnimation(const std::string& animationName) const
{
    return m_animationMap.at(animationName);
}

const sf::Font& Assets::getFont(const std::string& fontName) const
{
    return m_fontMap.at(fontName);
}
    
const std::map<std::string, sf::Texture>& Assets::getTextures() const
{
    return m_textureMap;
}

const std::map<std::string, Animation>& Assets::getAnimations() const
{
    return m_animationMap;
}