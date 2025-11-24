#include "GameEngine.h"
#include "Scene_Menu.h"

#include <iostream>
#include <optional>

GameEngine::GameEngine(const std::string& path)
{
    init(path);
}

void GameEngine::init(const std::string& path)
{
    std::cerr << "Entering " << __PRETTY_FUNCTION__ << "\n";
    Assets::Instance().loadFromFile(path);
    m_window.create(sf::VideoMode({1280, 768}), "Definitely Not Mario");
    m_window.setFramerateLimit(60);

    std::cerr << "calling changeScene\n";
    changeScene("MENU", std::make_shared<Scene_Menu>(this));
    
    std::cerr << "Exiting " << __PRETTY_FUNCTION__ << "\n\n";
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
    std::cerr << "Entering " << __PRETTY_FUNCTION__ << "\n";
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

            if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                std::cerr << "Key pressed with scancode = " 
                    << static_cast<int>(keyPressed->scancode) << "\n";
                std::cerr << "TODO: implement game key codes\n";

                #if 0
                if(keyPressed->scancode == sf::Keyboard::Scancode::X)
                {
                    std::cout << "Save screenshot to " << "test.png" << std::endl;
                    sf::Texture texture;
                    texture.create(m_window.getSize().x, m_window.getSize().y);
                    texture.update(m_window);
                    if(texture.copyToImage().saveToFile("test.png"))
                    {
                        std::cerr << "Screenshot saved to test.png\n";
                    }
                }
                #endif
            }

            std::cerr << "TODO: handle KeyPressed/KeyReleased to send action to scene\n";
            #if 0
            if(event->is<sf::Event::KeyPressed>() == sf::Event::KeyPressed || event->is<sf::Event::KeyReleased>())
            {
                if(currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end())
                {
                    continue;
                }

                // determine start or end action by whether it was a key press or release
                const std::string actionType = (event->is<sf::Event::KeyPressed == sf::Event::KeyPressed)? "START" : "END";

                // look up the action and send the action to the scene 
                currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
            }
            #endif
        }
    }
}


void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, 
        bool endCurrentScene)
{
    std::cerr << "TODO function " << __PRETTY_FUNCTION__
    
    
     << " understand code\n";
    m_currentScene = sceneName;
    m_sceneMap[sceneName] = scene;
    std::cerr << "TODO function " << __PRETTY_FUNCTION__ << " endCurrentScene: " << endCurrentScene 
        << " is unused parameter\n";
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