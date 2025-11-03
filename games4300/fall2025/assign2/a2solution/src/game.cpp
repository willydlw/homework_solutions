#include <cmath>
#include <optional>
#include <vector>

#include "../include/fileUtility.h"
#include "game.h"
#include "logError.hpp"
#include "vec2.hpp"


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

    LOG_INFO("Completed reading configuration file\n");
    std::cerr << gameConfig << "\n";

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
    std::cerr << gameConfig;


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
        //sEnemySpawner();
        sLifespan();
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
    // Transform properties
    static const float SPAWN_ANGLE = 0.0f;

    // position window's center
    sf::Vector2u winSize = m_window.getSize();
    Vec2<float> pos = {winSize.x/2.0f, winSize.y/2.0f}; 

    // translational velocity
    Vec2<float> vel = {1.0f, 1.0f}; 
    vel = vel.normalize();
    vel *= m_playerConfig.speed;   
       
    if(m_entities.getEntities("player").empty())
    {
        std::cerr << "player does not exist, adding new player\n";

        // Entity Manager allocates memory for a new entity
        // with tag name: "player" and places it in the vector 
        // of entities to be added
        std::shared_ptr<Entity> e = m_entities.addEntity("player");

        // Now we need to populate the player's component properties
        e->add<CTransform>(pos, vel, SPAWN_ANGLE);

        // Shape properties
        e->add<CShape>(m_playerConfig.shapeRadius, m_playerConfig.shapeVertices,
                    m_playerConfig.fillColor, m_playerConfig.outlineColor, m_playerConfig.outlineThickness);

        // Add an input component to the player so we can use inputs 
        e->add<CInput>();
    }
    else
    {
        player()->get<CShape>().circle.setPosition(pos);
        player()->get<CTransform>().velocity = vel;
        player()->get<CTransform>().angle = SPAWN_ANGLE;
    }

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

#endif 

// spawns a bullet from a given entity to a target location
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2f & target)
{
    std::cerr << __PRETTY_FUNCTION__ << "TODO\n";
    // TODO: implement the spawning fo a bullet which travels toward target 
    //     - bullet speed is given as a scalar speed 
    //     - you must set the velocity of x, y componnents 

    std::shared_ptr<Entity> bullet = m_entities.addEntity("bullet");

    // bullet should be spawned at the origin of the parameter entity 
    Vec2f start = entity->get<CTransform>().pos;

    // Difference vector is target - startPos
    Vec2f diff = target - start;

    // speed is the desired magnitude of the vector from bullet start position 
    // to the target position. Two ways to calculate this 
    Vec2f bulletVel = diff.normalize();
    bulletVel *= m_bulletConfig.speed;

    // add bullet components
    bullet->add<CTransform>(start, bulletVel, 0.0f);
    bullet->add<CShape>(   m_bulletConfig.shapeRadius, 
                            m_bulletConfig.shapeVertices,
                            m_bulletConfig.fillColor,
                            m_bulletConfig.outlineColor,
                            m_bulletConfig.outlineThickness);
    bullet->add<CCollision>(m_bulletConfig.collisionRadius);
    bullet->add<CLifeSpan>(m_bulletConfig.lifespan);
}

#if 0
void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
    std::cerr << __PRETTY_FUNCTION__ << "TODO\n";
    // TODO: implement your own special weapon 
}

#endif

void Game::sMovement()
{
    // TODO: implement all entity movement in this function 
    //  you should read the m_player->cInput component to determine if the
    //  player is moving

    sPlayerMovement();
    sBulletMovement();
}

void Game::sPlayerMovement()
{
    auto& transform = player()->get<CTransform>();
    const auto& input = player()->get<CInput>();
    Vec2f currentVelocity = {0.0f, 0.0f};

    if(input.up == true)
    {
        currentVelocity.y = -transform.velocity.y;
        std::cerr << "up, current velocity y: " << currentVelocity.y << "\n";
    }
    else if(input.down == true)
    {
        currentVelocity.y = transform.velocity.y;
        std::cerr << "down, current velocity y: " << currentVelocity.y << "\n";
    }

    if(input.left == true)
    {
        currentVelocity.x = -transform.velocity.x;
        std::cerr << "left, current velocity x: " << currentVelocity.x << "\n";
    }
    else if(input.right == true)
    {
        currentVelocity.x = transform.velocity.x;
        std::cerr << "right, current velocity x: " << currentVelocity.x << "\n";
    }

    transform.pos.x += currentVelocity.x;
    transform.pos.y += currentVelocity.y;
}

void Game::sBulletMovement()
{
    for(auto& b : m_entities.getEntities("bullet"))
    {
        if(b->isAlive())
        {
            CLifeSpan lifespan = b->get<CLifeSpan>();

            auto& pos = b->get<CTransform>().pos;
            auto& vel = b->get<CTransform>().velocity;

            // update position 
            //b->get<CTransform>().pos.x += b->get<CTransform>().velocity.x;
            //b->get<CTransform>().pos.y += b->get<CTransform>().velocity.y;
            pos += vel;

            // update fill color alpha value 
            float alpha = static_cast<float>(lifespan.remaining) * 255.0f / 
                            static_cast<float>(lifespan.lifespan);
            
            sf::Color fillColor = 
            {
                m_bulletConfig.fillColor.r, 
                m_bulletConfig.fillColor.g, 
                m_bulletConfig.fillColor.b,
                static_cast<uint8_t>(alpha)
            };

            b->get<CShape>().circle.setFillColor(fillColor);

            std::cerr << "bullet id  " << b->id() << ", alive: " << b->isAlive() << "\n";
            std::cerr << "postion x  " << pos.x << ", y: " << pos.y << "\n";
            std::cerr << "velocity x " << vel.x << ", y: " << vel.y << "\n"; 
            std::cerr << "lifespan   " << lifespan.lifespan << ", remaining: " << lifespan.remaining << "\n";
            std::cerr << "alpha      " << alpha << "\n";
        }
    }
}




void Game::sLifespan()
{
    // TODO: implement all lifespan functionality 
    // for all entities
    //      if entity has no lifespan component, skip it 
    //      if entity has > 0 remaining lifespan, subtract 1 
    //      if it has lifespan and is alive 
    //          scale its alpha channel properly 
    //      if it has lifespan and its time is up 
    //          destroy the entity 

    for(auto& b : m_entities.getEntities("bullet"))
    {
        b->get<CLifeSpan>().remaining -= 1;

        if(b->get<CLifeSpan>().remaining <= 0)
        {
            b->destroy();
        }
    }
}


void Game::sCollision()
{
    // TODO: implement all proper collisions between entities 
    //      be sure to use the collision radius, NOT the shape radius 

    #if 0
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

    #endif 

    // also need to check player collision with all enemies

    /* Player collision with walls
    *  
    *  Because player movement is controlled by up,down,left,right 
    *  user input, when the player reaches a wall boundary, we 
    *  position the player so that it has not crossed the boundary.
    *  
    *  The player's translational velocity is not changed to bounce 
    *  off a wall and travel in the opposite direction. If the user
    *  wants the player to travel in the opposite direction, the 
    *  appropriate key input must be received.
    */
    Vec2f playerPos = player()->get<CTransform>().pos;
    float radius = player()->get<CShape>().circle.getRadius();
    Vec2f wallBoundary = m_window.getSize();
    if(playerPos.x - radius <= 0.0f)
    {
        player()->get<CTransform>().pos.x = radius;
    }
    else if(playerPos.x + radius >= wallBoundary.x)
    {
        player()->get<CTransform>().pos.x = wallBoundary.x - radius;
    }

    if(playerPos.y - radius <= 0.0f) 
    {
        player()->get<CTransform>().pos.y = radius;
    }
    else if(playerPos.y + radius >= wallBoundary.y)
    {
        player()->get<CTransform>().pos.y = wallBoundary.y - radius;
    }
}


void Game::sGUI()
{ 
    #if 0
    // state variables to store the currently selected item for each drop down
    static size_t selected_item1 = 0;
    static size_t selected_item2 = 1;
    static size_t selected_item3 = 0;

    // items for the drop down lists 
    const std::vector<std::string> items1 = {"Option A", "Option B", "Option C"};
    const std::vector<std::string> items2 = {"Apple", "Banana", "Cherry", "Orange"};
    const std::vector<std::string> items3 = {"Red", "Green", "Blue"};
    #endif

    ImGui::Begin("Geometry Wars");          // create main window

    if(ImGui::BeginTabBar("MyTabBar"))      // create tab bar within the window
    {
        if(ImGui::BeginTabItem("Systems"))    // create first tab 
        {
            ImGui::Text("Content of Tab 1");
            ImGui::Button("button in tab 1");
            ImGui::EndTabItem();
        }

        if(ImGui::BeginTabItem("Entity Manager"))
        {
            if(ImGui::CollapsingHeader("Entities By Tag"))
            {
                if(ImGui::CollapsingHeader("bullet"))
                {
                    // button followed by id number, string "bullet" and position (x, y)
                    // button should show lifespan state bright white for alive 
                    // graying over time to black when dead
                    // Letter D in button to indicate it is deletable by mouse right-click
                }

                if(ImGui::CollapsingHeader("enemy"))
                {
                    // buttos same color as enemy fill color
                }

                if(ImGui::CollapsingHeader("player"))
                {

                }

                if(ImGui::CollapsingHeader("small"))
                {

                }
                // content in this block will be rendered when the header is uncollapsed 

                #if 0
                // Dropdown 1 
                const char* preview1 = items1[selected_item1].c_str();
                // "##combo1" hides the label, but gives it a unique ID
                if(ImGui::BeginCombo("##combo1", preview1))
                {
                    for(size_t n = 0; n < items1.size(); n++)
                    {
                        const bool is_selected = (selected_item1 == n);
                        if(ImGui::Selectable(items1[n].c_str()), is_selected)
                        {
                            selected_item1 = n;
                        }
                        if(is_selected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }    

                // Dropdown 2
                const char* preview2 = items2[selected_item2].c_str();
                // "##combo1" hides the label, but gives it a unique ID
                if(ImGui::BeginCombo("Choose Fruit", preview2))
                {
                    for(size_t n = 0; n < items2.size(); n++)
                    {
                        const bool is_selected = (selected_item2 == n);
                        if(ImGui::Selectable(items2[n].c_str()), is_selected)
                        {
                            selected_item2 = n;
                        }
                        if(is_selected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                } 

                // Dropdown 3
                const char* preview3 = items3[selected_item3].c_str();
                // "##combo1" hides the label, but gives it a unique ID
                if(ImGui::BeginCombo("Choose Color", preview3))
                {
                    for(size_t n = 0; n < items3.size(); n++)
                    {
                        const bool is_selected = (selected_item3 == n);
                        if(ImGui::Selectable(items3[n].c_str()), is_selected)
                        {
                            selected_item3 = n;
                        }
                        if(is_selected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }

                #endif          
            }   // End top-level collapsing header

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();                       // end main window
}



void Game::sRender()
{
    if(!m_window.isOpen()) { return; }

    // TODO: change the code below to draw all of the entities 
    // sample drawing of the player Entity is given 
    m_window.clear(sf::Color::Black);




    sRenderPlayer();
    sRenderBullet();

    // draw the ui last 
    ImGui::SFML::Render(m_window);

    m_window.display();

}

void Game::sRenderPlayer()
{
    static int printCount = 0;
    if(printCount == 0)
    {
        auto playerPos = player()->get<CTransform>().pos;
        std::cerr << "Player position x: " << playerPos.x << ", y: " << playerPos.y << "\n";
        printCount++;
    }

    // set the position of the shape based on the entity's transform->pos 
    player()->get<CShape>().circle.setPosition(player()->get<CTransform>().pos);

    // set the rotation of the shape based on the entity's transform->angle 
    player()->get<CTransform>().angle += 1.0;
    player()->get<CShape>().circle.setRotation(sf::degrees(player()->get<CTransform>().angle));

    // draw the entity's sf::CircleShape
    m_window.draw(player()->get<CShape>().circle);

}

void Game::sRenderBullet()
{
    // draw bullets 
    for(const auto& b : m_entities.getEntities("bullet"))
    {
        b->get<CShape>().circle.setPosition(b->get<CTransform>().pos);
        m_window.draw(b->get<CShape>().circle);
    }
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
            //std::cout << "Key pressed = " << int(keyPressed->scancode) << "\n";

            if(keyPressed->scancode == sf::Keyboard::Scancode::W)
            {
                player()->get<CInput>().up = true;
            }
            else if(keyPressed->scancode == sf::Keyboard::Scancode::S)
            {
                player()->get<CInput>().down = true;
            }
            else if(keyPressed->scancode == sf::Keyboard::Scancode::A)
            {
                player()->get<CInput>().left = true;
            }
            else if(keyPressed->scancode == sf::Keyboard::Scancode::D)
            {
                player()->get<CInput>().right = true;
            }
           
        }

        // this event is triggered when a key is released 
        if(const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            //std::cout << "Key released = " << int(keyReleased->scancode) << "\n";
            if(keyReleased->scancode == sf::Keyboard::Scancode::W)
            {
                player()->get<CInput>().up = false;
            }
            else if(keyReleased->scancode == sf::Keyboard::Scancode::S)
            {
                player()->get<CInput>().down = false;
            }
            else if(keyReleased->scancode == sf::Keyboard::Scancode::A)
            {
                player()->get<CInput>().left = false;
            }
            else if(keyReleased->scancode == sf::Keyboard::Scancode::D)
            {
                player()->get<CInput>().right = false;
            }
        }

        if(const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            Vec2f mpos = {static_cast<float>(mousePressed->position.x), 
                            static_cast<float>(mousePressed->position.y)};
            if(mousePressed->button == sf::Mouse::Button::Left)
            {
                std::cout << "Left mouse (" << mpos.x << ", " << mpos.y << ")\n";
                // TODO: call spawn bullet here
                spawnBullet(player(), mpos);

            }
            else if(mousePressed->button == sf::Mouse::Button::Right)
            {
                // TODO: call special weapon here 
                std::cout << "Right mouse (" << mpos.x << ", " << mpos.y << ")\n";
            }
        }
    }
}