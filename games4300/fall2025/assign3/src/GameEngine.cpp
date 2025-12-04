#include "GameEngine.h"
#include "Scene_Menu.h"
#include "Scene_Play.h"

#include <SFML/Window/Event.hpp>

#include <iostream>
#include <optional>
#include <utility>

GameEngine::GameEngine(const std::string& path)
{
    init(path);
}

void GameEngine::init(const std::string& path)
{
    Assets::Instance().loadFromFile(path);

    m_window.create(sf::VideoMode({1280, 768}), "Definitely Not Mario");
    m_window.setFramerateLimit(60);

    changeScene("MENU", std::make_shared<Scene_Menu>(this));
}


std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_sceneMap[m_currentScene];
}

bool GameEngine::isRunning()
{
    return m_running && m_window.isOpen();
}

sf::RenderWindow& GameEngine::window()
{
    return m_window;
}

void GameEngine::run()
{
    int count = 0;

    while(isRunning())
    {
        sUserInput();
        update();
    
        if(count % 300 == 0){
            std::cerr << __PRETTY_FUNCTION__ << " run count: " << count << "\n";
        }
        count++;

        m_window.display();
    }
}

void GameEngine::sUserInput()
{ 
    // check all the window's events that were triggered since 
    // the last iteration of the loop 
    while(const std::optional event = m_window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            std::cerr << __PRETTY_FUNCTION__ << " Detected Event closed, calling quit()\n";
            quit();
        }

        const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
        const auto* keyReleased = event->getIf<sf::Event::KeyReleased>();

        //if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        if(keyPressed)
        {
            std::cerr << "Key pressed with scancode = " 
                << static_cast<int>(keyPressed->scancode) << "\n";
            
            if(keyPressed->scancode == sf::Keyboard::Scan::X)
            {
                std::cerr << "X was pressed\n";
                std::cerr << "TODO: save screenshot to image file\n";
            }
        }

        if( keyPressed || keyReleased) 
        {
            int keyCode;
            if(keyPressed)
            {
                keyCode = static_cast<int>(keyPressed->code);
            }
            else // keyReleased
            {
                keyCode = static_cast<int>(keyReleased->code);
            }

            // if the current scene does not have an action associated with this key, skip the event
            if(currentScene()->getActionMap().find(keyCode) == currentScene()->getActionMap().end())
            {
                continue;
            }

            // determine start or end action by whether it was a key press or release
            const std::string actionType = (keyPressed)? "START" : "END";

            // look up the action and send the action to the scene 
            currentScene()->doAction(Action(currentScene()->getActionMap().at(keyCode), actionType));
        }
    }
}


void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, 
        bool endCurrentScene)
{
    std::cerr << "Entering function " << __PRETTY_FUNCTION__ << "\n";
    std::cerr << "parameter sceneName: " << sceneName << "\n";

    if(endCurrentScene == true)
    {
        std::cerr << "TODO function: " << __PRETTY_FUNCTION__ << " endCurrentScene is true\n";
        std::cerr << "m_currentScene: " << m_currentScene << ", parameter: sceneName: "
                    << sceneName << "will be next scene?\n";
        std::cerr << "How do I end the scene? which I think means call onEnd()\n";
    }
    
    m_currentScene = sceneName;
    m_sceneMap[sceneName] = scene;

    std::cerr << "Exiting function  " << __PRETTY_FUNCTION__ << "\n";
}

void GameEngine::quit()
{
    std::cerr << "Entering function  " << __PRETTY_FUNCTION__ << "\n";
    m_running = false;
    m_window.close();
    std::cerr << "Exiting function  " << __PRETTY_FUNCTION__ << "\n";
}

void GameEngine::update()
{
    currentScene()->update();
}