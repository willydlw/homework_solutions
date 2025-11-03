#pragma once 

#include <memory>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../include/Entity.hpp"
#include "../include/EntityManager.hpp"
#include "../include/gameConfig.h"

class Game 
{

public:

    static constexpr const char* FONTS_DIR_PATH = "assets/fonts";

    Game() = delete;
    Game(const std::string & config);

    void run();
    
    // systems 
    void sMovement();
    void sLifespan();
    void sCollision();
    //void sEnemySpawner();
     
    void sGUI();
    void sUserInput();
    void sRender();

private:

    // Data members
    sf::RenderWindow    m_window;
    EntityManager       m_entities;         // vector of entities to maintain
    sf::Font            m_font;
    sf::Text            m_text;             // SFML 3 Text has no default constructor
    FontConfig          m_fontConfig;       
    PlayerConfig        m_playerConfig;
    EnemyConfig         m_enemyConfig;
    BulletConfig        m_bulletConfig;
    sf::Clock           m_deltaClock;
    unsigned int        m_score = 0;
    unsigned int        m_currentFrame = 0;
    unsigned int        m_lastEnemySpawnTime = 0;
    bool                m_paused = false;           // whether we update game logic
    bool                m_running = true;

   
       
    // private member functions
    void init(const std::string& configFile);
    void initWindow(const WindowConfig& wc);
    bool initFont(const FontConfig& fc);

    std::shared_ptr<Entity> player();
    
    void spawnPlayer();

    #if 0
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> e);
    #endif 

    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2f & target);

    #if 0
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);
    #endif

    void sRenderPlayer();
    void sRenderBullet();
    void sPlayerMovement();
    void sBulletMovement();
};