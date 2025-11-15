#pragma once 

/* Base class

    Stores common scene data 
        Entities, Frame Count, Actions 
    
    Scene-specific functionality is carried out in derived class 
    Base class scene is abstract, cannot be instantiated 
    simulate() calls derived scene's update a given number of times 
        - Ex: may want to simulate physics multiple times 

*/

class Scene
{
    // functions

    virtual void update() = 0;  // pure virtual function
    virtual void soDoAction(action) = 0;
    virtual void sRender() = 0;

    void simulate(int);
    void doAction(action);
    void registerAction(action);

    private:

    GameEngine*         m_game;
    EntityManger        m_entities;
    int                 m_frame;
    std::map<int, std::string>  m_actionMap;
    bool                m_paused;
};


/*  Scene Derived Class 

    Stores scene-specific data
        - Level, player pointer, config 
    Scene-specific systems are defined within the derived class 
    Some scene derived classes may require quite different systmes based on fucntionality
*/

class Scene_Derived_Class : public Scene 
{
    // data 
    SceneConfig         m_level;
    PlayerConfig        m_config;

    // functions 
    void init();
    void update();
    void sAnimation();
    void sMovement();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    void sDoAction(action);
    void sGui();
};