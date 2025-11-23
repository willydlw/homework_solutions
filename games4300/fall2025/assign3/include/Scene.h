#ifndef SCENE_H
#define SCENE_H 

#include "Action.hpp"
#include "EntityManager.hpp"
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

// forward declarations
class GameEngine;

// typedefs
typedef std::map<int, std::string> ActionMap;


class Scene
{

protected:

    GameEngine*     m_game= nullptr;
    EntityManager   m_entityManager;
    ActionMap       m_actionMap;
    bool            m_paused = false;
    bool            m_hasEnded = false;
    size_t          m_currentFrame = 0;

    // pure virtual function
    virtual void onEnd() = 0;

    // toggles action in game play
    void setPaused(bool paused);

public:

    // constructors
    Scene();
    explicit Scene(GameEngine* gameEngine);

    // destructor
    virtual ~Scene();

    // pure virtual functions
    virtual void update() = 0; 
    virtual void sDoAction(const Action& action) = 0;
    virtual void sRender() = 0;

    
    virtual void doAction(const Action& action);

    void simulate(const size_t frames);
    void registerAction(int inputKey, const std::string& actionName);

    [[nodiscard]] size_t width() const;
    [[nodiscard]] size_t height() const;
    [[nodiscard]] size_t currentFrame() const;

    [[nodiscard]] bool hasEnded() const;
    [[nodiscard]] const ActionMap& getActionMap() const;
    
    void drawLine(const Vec2f& p1, const Vec2f& p2);

};

#endif // SCENE_H