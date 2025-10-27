#include "game.h"
#include "logError.hpp"

#include <optional>

Game::Game() : m_text(m_font){}

void Game::init(const std::string& configFile)
{
    // TODO
    initConfig(configFile);
    
}


void Game::initConfig(const std::string& configFile)
{
    // TODO
    GameConfig gameConfig;
    if(!gameConfig.readConfigFile(configFile))
    {
        LOG_FATAL("Configuration Failed\n");
        std::exit(EXIT_FAILURE);
    }

    LOG_INFO("***Initial Configuration***");
    std::cerr << gameConfig;

    initWindow(gameConfig.m_windowConfig);
    initFont(gameConfig.m_fontConfig);
    m_playerConfig = gameConfig.m_playerConfig;
    m_enemyConfig = gameConfig.m_enemyConfig;
    m_bulletConfig = gameConfig.m_bulletConfig;
}

void Game::initWindow(const WindowConfig& wc)
{
    m_window.setSize({wc.width, wc.height});
    m_window.setTitle("Geometry Wars");
    m_window.setFramerateLimit(wc.frameLimit);
    LOG_INFO("Full screen mode disabled by default\n");
}

void Game::initFont(const FontConfig& fc)
{
    
    if(!m_font.openFromFile(fc.fileName))
    {
        LOG_ERROR("Failed to open file: ", fc.fileName);
        return;
    }

    m_text.setFont(m_font);
    m_text.setCharacterSize(fc.size);
    m_text.setFillColor(sf::Color(fc.color.red, fc.color.green, fc.color.blue));
    m_text.setString("TODO");
}

void Game::run()
{
    while(m_window.isOpen())
    {
        while (const std::optional event = m_window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                m_window.close();
            }

            m_window.clear(sf::Color::Black);
            m_window.draw(m_text);
            m_window.display();
        }
    }
}
