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
    std::cerr << "Creating static assets object\n";
    return assets;
}


void Assets::addTexture(const std::string& textureName, const std::string& path, bool smooth)
{
    std::cerr << "TODO: " << __PRETTY_FUNCTION__ << " test function\n";
    if(!m_textureMap[textureName].loadFromFile(path))
    {
        std::cerr << "Could not load texture file: " << path << std::endl;
        m_textureMap.erase(textureName);
    }
    else 
    {
        m_textureMap[textureName].setSmooth(smooth);
        std::cout << "Loaded texture: " << path << std::endl;
    }
}

void Assets::addAnimation(  const std::string& animationName, 
                            const std::string& textureName, 
                            size_t frameCount, size_t animationSpeed)
{
    std::cerr << "TODO: " << __PRETTY_FUNCTION__ << " test function\n";
    std::cerr << "is function: " << __PRETTY_FUNCTION__ << " missing a third parameter?"
        << " could not see it in lecture video\n";
    m_animationMap[animationName] 
        = Animation(animationName, textureName, frameCount, animationSpeed);
}

void Assets::addFont(const std::string& fontName, const std::string& path)
{
    std::cerr << "TODO: " << __PRETTY_FUNCTION__ << " test function\n";
    m_fontMap[fontName] = sf::Font();
    if(!m_fontMap[fontName].openFromFile(path))
    {
        std::cerr << "Could not load font: " << fontName << ", path: " << path << std::endl;
        m_fontMap.erase(fontName);
    }
    else 
    {
        std::cout << "Loaded font: " << path << std::endl;
    }
}

void Assets::loadFromFile(const std::string& path)
{
    std::cerr << "TODO: " << __PRETTY_FUNCTION__ << " test function\n";
    std::cerr << "Entering " << __PRETTY_FUNCTION__ << "\n";

    std::ifstream infile(path);
    if(!infile.is_open())
    {
        std::cerr << __PRETTY_FUNCTION__ << ", failed to open file, path: " << path << "\n";
        std::exit(EXIT_FAILURE);
    }

    std::string str;
    while(infile.good())
    {
        infile >> str;
        std::cerr << "iterating, read str: " << str << "\n";
        if(str == "Texture")
        {
            std::string name, path;
            infile >> name >> path;
            std::cerr << "read name: " << name << ", path: " << path << "\n";
            addTexture(name,path);
            std::cerr << "returned from addTexture\n";
        }
        else if( str == "Animation")
        {
            std::string animationName, textureName;
            size_t frameCount, animationSpeed;         // TODO: int or size_t??
            infile >> animationName >> textureName >> frameCount >> animationSpeed;
            addAnimation(animationName, textureName, frameCount, animationSpeed);
        }
        else if( str == "Font")
        {
            std::string name, path;
            infile >> name >> path;
            std::cerr << "read name: " << name << ", path: " << path << "\n";
            addFont(name, path);
        }
        else 
        {
            std::cerr << "Uknown: " << str << std::endl;
        }
    }

    std::cerr << "exiting " << __PRETTY_FUNCTION__ << "\n";
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