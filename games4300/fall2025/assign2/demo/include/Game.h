#pragma once


#include "EntityManager.hpp"

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S;};
struct EnemyConfig  { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX;};
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S;};

class Game{

public:
    Game() = delete;

    Game(const std::string & config);

    void run();
    
    // systems 
    void sMovement();
    void sLifespan();
    void sCollision();
    void sGUI();
    void sUserInput();
    void sEnemySpawner();
    void sRender();


private:
    sf::Window      m_window;           // window to which we draw
    EntityManager   m_entities;         // vector of entities to maintain
    sf::Font        m_font;
    sf::Text        m_text;
    PlayerConfig    m_playerConfig;
    EnemyConfig     m_enemyConfig;
    BulletConfig    m_bulletConfig;
    sf::Clock       m_deltaClock;
    unsigned int    m_score = 0;
    unsigned int    m_currentFrame = 0;
    unsigned int    m_lastEnemySpawnTime = 0;
    bool            m_paused = false;           // whether we update game logic
    bool            m_running = true;

    // private member functions 
    void init(const std::string& config);
    std::shared_ptr<Entity> player();


    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> e);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2f & target);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

};