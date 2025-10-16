#pragma once 

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "gameConfig.h"

class Game 
{
    public:

    Game();

    void init(const std::string& configFile);

    private:
        sf::RenderWindow    m_window;

        PlayerConfig        m_playerConfig;
        EnemyConfig         m_enemyConfig;
        BulletConfig        m_bulletConfig;

    void initConfig(const std::string& configFile);
    std::vector<std::string> searchForFiles(const std::string& targetFile);
    
};