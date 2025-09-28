#pragma once

#include "entityManager.h"

class GameEngine{
    public:
    GameEngine();

    void mainLoop();

    void init();
    void update();

    // systems 
    void sMovement();
    void sUserInput();
    void sEnemySpawner();
    void sRender();


    private:
    sf::Window      m_window;
    bool            m_paused;
    bool            m_running;

    EntityManager m_entityManager;
};