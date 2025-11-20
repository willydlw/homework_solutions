/*  Asset Management 
    - Assets are external files that are loaded into memory to be used in the game 
    - For our games, assets will be 
        - Textures (image files: .png, .jpg)
            png files are compressed, lossless and can support transparency
        - Animations (textures + bookeeping)
        - Sounds (sound files: .wav, .ogg)
        - Fonts (filetype: ttf)
    - Load once, use often
*/

/*  Assets Class

    - Want to load assets that are defined in an external configuration file 
        - Texture MegaMan textures/MMS.png 
        - Sound MegaDeath sounds/death.wav 
    - We can reference that asset via name:
        - m_assets->getTexture("Megaman");
        - m_assets->getSound("MegaDeath");
    - To implement this, the Asset class will use a std::map<std::string, AssetType>
*/

/*  Lives inside the GameEngine class 
    Initialized inside GameEngine init()
    Accessed via Scene's pointer to GameEngine
        - m_game->getAssets()

    Assets loaded once at beginning of program
*/


#pragma once 

#include <SFML/Graphics.hpp>
#include <map>
#include <cassert>
#include <iostream>
#include <fstream>

class Animation;

class Assets
{
    private:

    // data
    std::map<std::string, sf::Texture> m_textureMap;
    std::map<std::string, Animation>   m_animationMap;
    std::map<std::string, sf::Font>    m_fontMap;  

    // functions 
    void addTexture(const std::string& textureName, const std::string& path,
            bool smooth = ?);

    void addAnimation(const std::string& animationName, const std::string& textureName,
            size_t ??);

    void addFont(const std::string& fontName, const std::string& path);

    Assets() = default;
   
public:

    static Assets& Instance();

    void loadFromFile(const std::string& path);

    const sf::Texture& getTexture(const std::string& textureName) const;
    const Animation& getAnimation(const std::string& animationName) const;
    const sf::Font& getFont(const std::string& fontName) const;
    const std::map<std::string, sf::Texture>& getTextures() const;
    const std::map<std::string, Animation>& getAnimations() const;
    
}