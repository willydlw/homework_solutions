#pragma once 

/*  Stores top level game data 
        Assets, sf::Window, Scenes 
    Performs top level functionality 
        Changing scenes, Handling input 
    run() contains main game loop 
    GameEngine pointer will be passed to Scenes in constructor 
        Access to assets, window, scenes
    GameEngine may be implemented as a singleton class, instead of pointer,  in assignment 3
*/

#include <map>
#include <string>

class GameEngine
{
    // functions

    void init();
    void update();
    void run();         
    void quit();
    void changeScene<T>();
    Assets& getAssets();
    sf::Window& window();
    void sUserInput();

    // data

    std::map<std::string, Scene>    m_scenes;
    sf::Window                      m_window;
    Assets                          m_assets;
    std::string                     m_scene;
    bool                            m_running;
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