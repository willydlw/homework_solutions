#pragma once 

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "gameConfig.h"

class Game 
{
    public:

    Game();

    void init(const std::string& configFile);

    void run();
    

    private:
        sf::RenderWindow    m_window;
        sf::Font            m_font;
        sf::Text         m_text;             // SFML 3 Text has no default constructor
        FontConfig          m_fontConfig;       // for size and color
        PlayerConfig        m_playerConfig;
        EnemyConfig         m_enemyConfig;
        BulletConfig        m_bulletConfig;

       

    void initConfig(const std::string& configFile);
    
    void initWindow(const WindowConfig& wc);
    void initFont(const FontConfig& fc);
    
    
};