#pragma once 

#include "Action.hpp"
#include "EntityManager.hpp"
#include "GameEngine.h"
#include "Vec2.hpp"

#include <map>

/* Base class

    Stores common scene data 
        Entities, Frame Count, Actions 
    
    Scene-specific functionality is carried out in derived class 
    Base class scene is abstract, cannot be instantiated 
    simulate() calls derived scene's update a given number of times 
        - Ex: may want to simulate physics multiple times 

*/

typedef std::map<int, std::string> ActionMap;

class GameEngine;

class Scene
{
    protected:

    GameEngine*     m_game= nullptr;
    EntityManager   m_entityManager;
    ActionMap       m_actionMap;
    bool            m_pause = false;
    bool            m_hadEnded = false;
    size_t          m_currentFrame = 0;

    virtual void onEnd() = 0;
    void setPaused(bool paused);

    public:

    Scene();
    Scene(GameEngine* gameEngine);
    virtual ~Scene();

    // pure virtual functions
    virtual void update() = 0; 
    virtual void sDoAction(const Action& action) = 0;
    virtual void sRender() = 0;

    
    virtual void doAction(const Action& action);
    void simulate(const size_t frames);
    void registerAction(int inputKey, const std::string& actionName);

    size_t width() const;
    size_t height() const;
    size_t currentFrame() const;

    bool hasEnded() const;
    ActionMap& getActionMap();
    void drawLine(const Vec2f& p1, const Vec2f& p2);

};