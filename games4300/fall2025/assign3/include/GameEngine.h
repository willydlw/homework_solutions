#ifndef A3_GAME_ENGINE_H
#define A3_GAME_ENGINE_H

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Assets.h"
#include "Scene.h"

/*  Stores top level game data 
        Assets, sf::Window, Scenes 
    Performs top level functionality 
        Changing scenes, Handling input 
    run() contains main game loop 
    GameEngine pointer will be passed to Scenes in constructor 
        Access to assets, window, scenes
    GameEngine may be implemented as a singleton class, instead of pointer,  in assignment 3
*/

// forward declaration 
class Scene;

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{
    public:

    GameEngine(const std::string& path);

    void changeScene(
        const std::string& sceneName,
        std::shared_ptr<Scene> scene,
        bool endCurrentScene = false
    );

    void quit();
    void run();

    sf::RenderWindow& window();
    bool isRunning();

    protected:

    sf::RenderWindow    m_window;
    std::string         m_currentScene;
    SceneMap            m_sceneMap;
    size_t              m_simulationSpeed = 1;
    bool                m_running = true;


    void init(const std::string& path);
    void update();
    void sUserInput();
    std::shared_ptr<Scene> currentScene();

};


/* Scene switching 
    - Game Engine stores a map from strings to shared_ptr<Scene> 
    - Also stores a currentScene string
    - currentScene() looks up the currently active scene by map[currentScene]
    - changeScene(string, scene) changes the scene to a new, or previously stored Scene
    - map structure mimics a finite state machine for scene switching
*/

/*  Scene switching example 
    1. Game engine constructed:
        - changeScene<T>("string", args)
            - currentScene = "menu"
            - scenes["menu"] = shared_ptr<SceneMenu>(args)
    2. Player presented with menu scene 
    3. Player selects a level on the menu 
        - LevelPath = currently selected menu item 
        - Menu tells game engine to change scenes 
        - game->changScene<Scene_play>("play", LevelPath)
*/


#endif
