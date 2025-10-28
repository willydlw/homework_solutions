#include <optional>

#include "../include/fileUtility.h"
#include "game.h"
#include "logError.hpp"

// Note: SFML 3, sf::text has no default constructor
// Constructing it with default font to avoid compilation 
// error. The m_font and m_text objects will be initialized 
// by calling the init function.
Game::Game() : m_text(m_font)
{

}

void Game::init(const std::string& configFile)
{
    GameConfig gameConfig;
    if(!gameConfig.readConfigFile(configFile))
    {
        LOG_FATAL("Configuration Failed\n");
        std::exit(EXIT_FAILURE);
    }

    initWindow(gameConfig.m_windowConfig);
    initFont(gameConfig.m_fontConfig);
    m_playerConfig = gameConfig.m_playerConfig;
    m_enemyConfig = gameConfig.m_enemyConfig;
    m_bulletConfig = gameConfig.m_bulletConfig;
}

void Game::initWindow(const WindowConfig& wc)
{
    m_window.create(sf::VideoMode({wc.width, wc.height}), "Geometry Wars");
    m_window.setFramerateLimit(wc.frameLimit);
    LOG_INFO("Full screen mode disabled by default");
}


bool Game::initFont(const FontConfig& fc)
{
    std::vector<std::filesystem::path> foundFiles = searchDirectory(FONTS_DIR_PATH, fc.fileName);
    if(foundFiles.empty())
    {
        LOG_ERROR(fc.fileName, " not found in directory: ", FONTS_DIR_PATH);
        return false;
    }

    for(const auto& f : foundFiles)
    {
        if(m_font.openFromFile(f))
        {
            LOG_INFO("SUCCESS opened font file: ", f);
            m_text.setFont(m_font);
            m_text.setCharacterSize(fc.size);
            m_text.setFillColor(sf::Color(fc.color.red, fc.color.green, fc.color.blue));
            m_text.setString("TODO");
            return true;
        }
    }

    LOG_ERROR("Failed to open font file: ", fc.fileName);
    return false;
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
        }

        m_window.clear(sf::Color::Black);
        m_window.draw(m_text);
        m_window.display();
    }
}
