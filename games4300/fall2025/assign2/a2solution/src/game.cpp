#include <cmath>
#include <optional>
#include <vector>

#include "../include/fileUtility.h"
#include "game.h"
#include "logError.hpp"


#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

// Note: SFML 3, sf::text has no default constructor
// Constructing it with default font to avoid compilation 
// error. The m_font and m_text objects will be initialized 
// by calling the init function.
Game::Game(const std::string & config) : m_text(m_font, "Default", 24)
{
    init(config);
}

void Game::init(const std::string& configFile)
{
    GameConfig gameConfig;
    if(!gameConfig.readConfigFile(configFile))
    {
        LOG_FATAL("Configuration Failed\n");
        std::exit(EXIT_FAILURE);
    }

    initWindow(gameConfig.m_windowConfig);
    if(!initFont(gameConfig.m_fontConfig))
    {
        LOG_FATAL("Failure to load font");
        std::exit(EXIT_FAILURE);
    }

    m_playerConfig = gameConfig.m_playerConfig;
    m_enemyConfig = gameConfig.m_enemyConfig;
    m_bulletConfig = gameConfig.m_bulletConfig;

    LOG_INFO("Configuration complete\n");
    //std::cerr << gameConfig;

    std::cerr << "TODO: init ImGui\n";

    #if 0
    if(!ImGui::SFML::Init(m_window))
    {
        std::cerr << "ERROR, function: " << __PRETTY_FUNCTION__ 
            << ", line: " << __LINE__ 
            << " ImGui Init failure\n";
            std::exit(-1);
    }

    // scale the imgui ui and text size by 2 
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;
    #endif 

    spawnPlayer();

}

void Game::initWindow(const WindowConfig& wc)
{
    m_window.create(sf::VideoMode({wc.width, wc.height}), "Geometry Wars");
    m_window.setFramerateLimit(wc.frameLimit);
    m_window.setKeyRepeatEnabled(false);
    LOG_INFO("Full screen mode disabled by default");
}


bool Game::initFont(const FontConfig& fc)
{
    std::vector<std::filesystem::path> foundFiles = searchDirectory(FONTS_DIR_PATH, fc.fileName);
    if(foundFiles.empty())
    {
        LOG_ERROR(fc.fileName, " not found in directory: ", FONTS_DIR_PATH);
        return false;
    }

    for(const auto& f : foundFiles)
    {
        if(m_font.openFromFile(f))
        {
            LOG_INFO("SUCCESS opened font file: ", f);
            m_text.setFont(m_font);
            m_text.setCharacterSize(fc.size);
            m_text.setFillColor(fc.color);
            m_text.setString("TODO");
            return true;
        }
    }

    LOG_ERROR("Failed to open font file: ", fc.fileName);
    return false;
}

std::shared_ptr<Entity> Game::player()
{   
    if(!m_entities.getEntities("player").empty()){
        return m_entities.getEntities("player").back(); 
    }

    return nullptr;
}

void Game::run()
{
    #if 0
    while(m_window.isOpen())
    {
        while (const std::optional event = m_window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                m_window.close();
            }
        }

        m_window.clear(sf::Color::Black);
        m_window.draw(m_text);
        m_window.display();
    }
    #endif

    #if 1
    std::cerr << __PRETTY_FUNCTION__ << "TODO: "
        << " add PAUSE functionality\n";
    // Some systems should function while paused (rendering and gui)
    // some systems should not function (movement, input)
    // while rendering keep showing enemy rotation when rendering 

    while(true)
    {
        // update the entity manager
        m_entities.update();

        // required update call to imgui 
        //ImGui::SFML::Update(m_window, m_deltaClock.restart());

        //sUserInput();
        //sEnemySpawner();
        //sMovement();
        //sCollision();
        //sGUI();
        sRender();

        m_currentFrame++;
    }
    #endif 
}

// respawn the player in the middle of the screen
void Game::spawnPlayer()
{
    static const float SPAWN_ANGLE = 0.0f;

    if(m_entities.getEntities("player").empty())
    {
        std::cerr << "player does not exist, adding new player\n";
        auto e = m_entities.addEntity("player");

        // Transfom properties

        // Spawn player in window's center 
        sf::Vector2i pos = m_window.getPosition();

        // Velocity components - player config speed is magnitude
        float velx = m_playerConfig.speed * cos(SPAWN_ANGLE);
        float vely = m_playerConfig.speed * sin(SPAWN_ANGLE);

        e->add<CTransform>(Vec2f(pos.x, pos.y), Vec2f(velx, vely), SPAWN_ANGLE);

        // Shape properties
        e->add<CShape>(m_playerConfig.shapeRadius, m_playerConfig.shapeVertices,
                    m_playerConfig.fillColor, m_playerConfig.outlineColor, m_playerConfig.outlineThickness);

        // Add an input component to the player so we can use inputs 
        e->add<CInput>();
    }

   
    
    // We create every entity by calling EntityMangers.addEntity(tag)
    // This returns a std::shared_ptr<Entity>. We use auto to save typing 

    std::cerr << __PRETTY_FUNCTION__ << "TODO: "
        << "When a player already exists, we do not need to add a new player, just respawn it in widow center\n";

    
}

#if 0
// spawn an enemy at a random position
void Game::spawnEnemy()
{
    // Enemy must be spawned within bounds of the window
    std::cerr << __PRETTY_FUNCTION__ << "TODO: " 
        << " finish adding all properties of the ENEMY with the correct values from the config file\n";
    
  
    // record when the most recent enemy was spawned 
    m_lastEnemySpawnTime = m_currentFrame;
}


void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
    
    // TODO: spawn small enemies at the location of the input enemy e

    // When we create the smaller enemy, we have to read the values of the original 
    // enemy 
    // - spawn a number of small enemies equal to the vertices of the original entity 
    // - set each small enemy to the same color as the original, half the size 
    // - small enemies are worth double points of the original enemy

    //e->get<Shape>.circle.getPointCount();
}

// spawns a bullet from a given entity to a target location
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2f & target)
{
     std::cerr << __PRETTY_FUNCTION__ << "TODO\n";
     // TODO: implement the spawning fo a bullet which travels toward target 
     //     - bullet speed is given as a scalar speed 
     //     - you must set the velocity of x, y componnents 
}


void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
    std::cerr << __PRETTY_FUNCTION__ << "TODO\n";
    // TODO: implement your own special weapon 
}

void Game::sMovement()
{
    // TODO: implement all entity movement in this function 
    //  you should read the m_player->cInput component to determine if the
    //  player is moving

    // Sample movement speed update for the player 
    auto& transform = player()->get<CTransform>();
    transform.pos.x += transform.velocity.x;
    transform.pos.y += transform.velocity.y;
}

void Game::sLifespan()
{
    // TODO: implement all lifespan functionality 
    // for all entities
    //      if entity has no lifespan component, skip it 
    //      if entity has > 0 remaining lifespan, substract 1 
    //      if it has lifespan and is alive 
    //          scale its alpha channel properly 
    //      if it has lifespan and its time is up 
    //          destroy the entity 
}

void Game::sCollision()
{
    // TODO: implement all proper collisions between entities 
    //      be sure to use the collision radius, NOT the shape radius 

    // Note data types of b, e are shared_ptr so a copy of the pointer 
    // will make permanent changes to memory. We don't need auto&
    for(auto b : m_entities.getEntities("bullet"))
    {
        for(auto e : m_entities.getEntities("enemy"))
        {
            // do collsion logic
        }
        for(auto e : m_entities.getEntities("smallEnemy"))
        {
            // do collision logic
        }
    }

    // also need to check player collision with all enemies
    // player collision with walls
}

void Game::sGUI()
{
    ImGui::Begin("Geometry Wars");

    ImGui::Text("Stuff goes here");

    ImGui::End();
}

#endif

void Game::sRender()
{
    if(!m_window.isOpen()) { return; }

    // TODO: change the code below to draw all of the entities 
    // sample drawing of the player Entity is given 
    m_window.clear();

    static int printCount = 0;
    if(printCount == 0)
    {
        auto playerPos = player()->get<CTransform>().pos;
        std::cerr << "Player position x: " << playerPos.x << ", y: " << playerPos.y << "\n";
        printCount++;
    }

    // set the position o fthe shape based on the entity's transform->pos 
    player()->get<CShape>().circle.setPosition(player()->get<CTransform>().pos);

    #if 0
    // set the rotation of the shape based on the entity's transform->angle 
    player()->get<CTransform>().angle += 1.0;
    player()->get<CShape>().circle.setRotation(sf::degrees(player()->get<CTransform>().angle));
    #endif

    // draw the entity's sf::CircleShape
    m_window.draw(player()->get<CShape>().circle);

    // draw the ui last 
    //ImGui::SFML::Render(m_window);

    m_window.display();

}
