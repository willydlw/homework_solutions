#pragma once 

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>

#include "gameConfig.h"

class Game 
{
    public:

    Game();

    void init(const std::string& configFile);

    private:
        sf::RenderWindow    m_window;
        sf::Font            m_font;
        GameConfig          m_gameConfig;

    void initConfig(const std::string& configFile);
    
    //std::vector<std::string> searchForFiles(const std::string& targetFile);
    
};