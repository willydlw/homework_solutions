#include "GameEngine.h"
#include "Scene_Menu.h"

#include <optional>

GameEngine::GameEngine(const std::string& path)
{
    init(path);
}

void GameEngine::init(const std::string& path)
{
    std::cerr << "Entering " << __func__ << "\n";
    Assets::Instance().loadFromFile(path);
    m_window.create(sf::VideoMode({1280, 768}), "Assignment 3");
    m_window.setFramerateLimit(60);
    changeScene("MENU", std::make_shared<Scene_Menu>(this));
    std::cerr << "Exiting " << __func__ << "\n\n";
}


std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_sceneMap[m_currentScene];
}

bool GameEngine::isRunning()
{
    return m_running & m_window.isOpen();
}

sf::RenderWindow& GameEngine::window()
{
    return m_window;
}

void GameEngine::run()
{
    while(isRunning())
    {
        sUserInput();
        update();
        m_window.display();
    }
}

void GameEngine::sUserInput()
{
    while(m_window.isOpen())
    {
        // check all the window's events that were triggered since 
        // the last iteration of the loop 
        while(const std::optional event = m_window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                quit();
            }

            if(event->is<sf::Event::KeyPressed>())
            {
                std::cerr << "Detected keypress\n";
                std::cerr << "TODO: implement game key codes\n";
            }
        }
    }
}


void GameEngine::quit()
{
    m_running = false;
    m_window.close();
}

void GameEngine::update()
{
    currentScene()->update();
}