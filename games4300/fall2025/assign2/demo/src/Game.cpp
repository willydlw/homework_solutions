#include "Game.h"

#include <iostream>

Game::Game(const std::string& config) 
    : m_text(m_font, "Default", 24)
{
    init(config);
}


void Game::init(const std::string& path)
{
    std::cerr << __PRETTY_FUNCTION__ << " TODO: read in config file here\n"
        << " Use the premade PlayerConfig, EnemyConfig, BulletConfig\n\n";

    // set up default window parameters 
    std::cerr << __PRETTY_FUNCTION__ << "TODO: replace hard coded window width and height with config variables\n";
    m_window.create(sf::VideoMode({1280, 720}), "Assignment 2");
    m_window.setKeyRepeatEnabled(false);

    std::cerr << __PRETTY_FUNCTION__ << "TODO: "
        << "replace hard coded FRAME RATE with config variables\n";
    m_window.setFramerateLimit(60);

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

    spawnPlayer();

}

std::shared_ptr<Entity> Game::player()
{
    return m_entities.getEntities("player").back();   
}

void Game::run()
{
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
        ImGui::SFML::Update(m_window, m_deltaClock.restart());

        sUserInput();
        sEnemySpawner();
        sMovement();
        sCollision();
        sGUI();
        sRender();

        m_currentFrame++;
    }
}

// respawn the player in the middle of the screen
void Game::spawnPlayer()
{
    std::cerr << __PRETTY_FUNCTION__ << "TODO: " 
        << " finish adding all properties of the player with the correct values from the config file\n";
    
    // We create every entity by calling EntityMangers.addEntity(tag)
    // This returns a std::shared_ptr<Entity>. We use auto to save typing 

    std::cerr << __PRETTY_FUNCTION__ << "TODO: "
        << "When a player already exists, we do not need to add a new player, just respawn it in widow center\n";

    std::cerr << __PRETTY_FUNCTION__ << "TODO: " 
        << " Replace hard coded player values with CONFIG values\n";
    auto e = m_entities.addEntity("player");

    // Give this entity a transform so it spawns ate (200,200) with velocit (1,1)
    // and angle 0
    e->add<CTransform>(Vec2f(200.0f, 200.0f), Vec2f(1.0f, 1.0f), 0.0f);

    // The entity's shape has radius 32, 8 sides, dark grey fill, and red outline
    // with thickness 4
    e->add<CShape>(32.0f, 8, sf::Color(10,10,10), sf::Color(255,0,0), 4.0f);

    // Add an input component to the player so we can use inputs 
    e->add<CInput>();
}


// spawn an enemy at a random position
void Game::spawnPlayer()
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

void Game::sRender()
{
    if(!m_window.isOpen()) { return; }

    // TODO: change the code below to draw all of the entities 
    // sample drawing of the player Entity is given 
    m_window.clear();

    // set the position o fthe shape based on the entity's transform->pos 
    player()->get<CShape>().circle.setPosition(player()->get<CTransform>().pos);

    // set the rotation of the shape based on the entity's transform->angle 
    player()->get<CTransform>().angle += 1.0;
    player()->get<Cshape>().circle.setRotation(sf::degrees(player()->get<CTransform>().angle));

    // draw the entity's sf::CircleShape
    m_window.draw(player()->get<CShape>().circle);

    // draw the ui last 
    ImGui::SFML::Render(m_window);

    m_window.display();

}

void Game::sUserInput()
{
    // TODO: handle user input here 
    //  note that yous should only be setting the player's input component variables here 
    //  you should not implement the player's movement logic here 
    //  the movement system will read the variables you set in this function 

    while(auto event = m_window.pollEvent())
    {
        // pass the event to imgui to be parsed 
        ImGui::SFML::ProcessEvent(m_window, *event);

        // this event triggers when the window is closed 
        if(event->is<sf::Event::Closed>())
        {
            std::exit(0);
        }

        // this event is triggered when a key is pressed 
        if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            std::cout << "Key pressed = " << int(keyPressed->scancode) << "\n";

            if(keyPressed->scancode == sf::Keyboard::Scancode::W)
            {
                 // TODO: set player's input component up to true
                std::cout << "W key pressed\n";
            }
           
        }

        // this event is triggered when a key is released 
        if(const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            std::cout << "Key released = " << int(keyReleased->scancode) << "\n";
            if(keyReleased->scancode == sf::Keyboard::Scancode::W)
            {
                 // TODO: set player's input component to false
                 std::cout << "W key released\n";
            }
        }

        if(const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            Vec2f mpos(mousePressed->position);
            if(mousePressed->button == sf::Mouse::Button::Left)
            {
                std::cout << "Left mouse (" << mpos.x << ", " << mpos.y << ")\n";
                // TODO: call spawn bullet here
            }
            else if(mousePressed->button == sf::Mouse::Button::Right)
            {
                // TODO: call special weapon here 
                std::cout << "Right mouse (" << mpos.x << ", " << mpos.y << ")\n";
            }
        }
    }
}