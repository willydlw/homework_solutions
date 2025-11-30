#include "GameEngine.h"
#include "Scene_Menu.h"
#include "Scene_Play.h"

#include <SFML/Window/Event.hpp>

#include <iostream>
#include <optional>
#include <utility>

GameEngine::GameEngine(const std::string& path)
{
    std::cerr << "Entering " << __PRETTY_FUNCTION__ << "\n";
    init(path);
    std::cerr << "Exiting " << __PRETTY_FUNCTION__ << "\n\n";
}

void GameEngine::init(const std::string& path)
{
    std::cerr << "Entering " << __PRETTY_FUNCTION__ << "\n";

    Assets::Instance().loadFromFile(path);

    m_window.create(sf::VideoMode({1280, 768}), "Definitely Not Mario");
    m_window.setFramerateLimit(60);

    changeScene("MENU", std::make_shared<Scene_Menu>(this));
    
    std::cerr << "Exiting " << __PRETTY_FUNCTION__ << "\n\n";
}


std::shared_ptr<Scene> GameEngine::currentScene()
{
    std::cerr << "Entering " << __PRETTY_FUNCTION__ << "\n";
    return m_sceneMap[m_currentScene];
    std::cerr << "Exiting " << __PRETTY_FUNCTION__ << "\n\n";
}

bool GameEngine::isRunning()
{
    std::cerr << "Entering function  " << __PRETTY_FUNCTION__ << "\n";
    std::cerr << std::boolalpha << "m_window.isOpen(): " << m_window.isOpen() << "\n";
    std::cerr << std::boolalpha << "m_running:         " << m_running << "\n";
    bool result = m_running && m_window.isOpen();
    std::cerr << std::boolalpha << "m_running && m_isOpen(): " << result << "\n";
    return result;
}

sf::RenderWindow& GameEngine::window()
{
    std::cerr << "Entering function  " << __PRETTY_FUNCTION__ << " next action is return m_window\n";
    return m_window;
}

void GameEngine::run()
{
    std::cerr << "Entering " << __PRETTY_FUNCTION__ << "\n";
    int count = 0;

    #if 0
    //sf::Font testFont = Assets::Instance().getFont("Mario");
    //sf::Text testText(testFont);
    sf::Text testText(Assets::Instance().getFont("Mario"));
    testText.setString("Test");
    testText.setCharacterSize(24);
    testText.setFillColor(sf::Color::Red);
   
    while(m_window.isOpen())
    {
        while(const std::optional event = m_window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                m_window.close();
            }
        }
        m_window.clear(sf::Color::Green);
        m_window.draw(testText);
        m_window.display();
    }
    #endif

    #if 1
    std::cerr << "Function: " << __PRETTY_FUNCTION__ << " ready to enter while(running) loop, "
            << " m_running: " << std::boolalpha << m_running << "\n";
    while(isRunning())
    {
        std::cerr << "Function " << __PRETTY_FUNCTION__ << " calling sUserInput()\n";
        sUserInput();

        std::cerr << "Function " << __PRETTY_FUNCTION__ << " back from sUserInput()\n";
        std::cerr << "Function " << __PRETTY_FUNCTION__ << " calling update()\n";
        update();
        std::cerr << "Function " << __PRETTY_FUNCTION__ << " back from update()\n";

        if(count % 20 == 0){
            std::cerr << "run count: " << count << "\n";
        }
        count++;

        m_window.display();

    }
    #endif
}

void GameEngine::sUserInput()
{
    std::cerr << "Entering function: " << __PRETTY_FUNCTION__ << "\n";

    
    // check all the window's events that were triggered since 
    // the last iteration of the loop 
    while(const std::optional event = m_window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            std::cerr << "Detected Event closed, calling quit()\n";
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
    std::cerr << "Exiting function  " << __PRETTY_FUNCTION__ << "\n";
    m_running = false;
    m_window.close();
    std::cerr << "Exiting function  " << __PRETTY_FUNCTION__ << "\n";
}

void GameEngine::update()
{
    std::cerr << "Entering function " << __PRETTY_FUNCTION__ 
             << ", current scene: " << m_currentScene << "\n";
    currentScene()->update();
    std::cerr << "Exiting function  " << __PRETTY_FUNCTION__ << "\n";
}