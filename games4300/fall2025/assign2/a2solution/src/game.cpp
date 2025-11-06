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

const char* Game::TAG_NAME[] = {
    "bullet", "enemy", "player", "small"
};

// Note: SFML 3, sf::text has no default constructor
// Constructing it with default font to avoid compilation 
// error. The m_font and m_text objects will be properly configured 
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

    initWindow(gameConfig.m_windowConfig);
    if(!initFont(gameConfig.m_fontConfig))
    {
        LOG_FATAL("Failure to load font");
        std::exit(EXIT_FAILURE);
    }

    m_playerConfig = gameConfig.m_playerConfig;
    m_enemyConfig = gameConfig.m_enemyConfig;
    m_bulletConfig = gameConfig.m_bulletConfig;

    m_spawnInterval = m_enemyConfig.spawnInterval;

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
    if(!m_entities.getEntities(TAG_NAME[static_cast<int>(Tag::PLAYER)]).empty()){
        return m_entities.getEntities(TAG_NAME[static_cast<int>(Tag::PLAYER)]).back(); 
    }

    return nullptr;
}

void Game::run()
{
    while(true)
    {
        // update the entity manager
        m_entities.update();

        // required update call to imgui 
        ImGui::SFML::Update(m_window, m_deltaClock.restart());

        if(m_pauseMovement == false)
        {
            sUserInput();
        }

        if(m_pauseSpawning == false)
        {
            // Enemies will spawn in a random location on the screen every X frames,
            // where X is defined in the configuration file.
            if(m_currentFrame - m_lastEnemySpawnTime >= m_spawnInterval)
            {
                spawnEnemy();
            }
        }
        
        if(m_pauseLifeSpan == false)
        {
            sLifespan();
        }

        if(m_pauseMovement == false)
        {
            sMovement();
        }

        if(m_pauseCollision == false)
        {
            sCollision();
        }

        std::string score = {"Score "};
        score += std::to_string(m_score);
        m_text.setString(score);

        sGUI();
        sRender();       
        m_currentFrame++;
    }
}

// respawn the player in the middle of the screen
void Game::spawnPlayer()
{
    // Transform properties
    // position in window's center
    sf::Vector2u winSize = m_window.getSize();
    Vec2<float> pos = {winSize.x/2.0f, winSize.y/2.0f}; 

    // translational velocity
    Vec2<float> vel = {1.0f, 1.0f}; 
    vel = vel.normalize();
    vel *= m_playerConfig.speed;   
       
    if(m_entities.getEntities(TAG_NAME[static_cast<int>(Tag::PLAYER)]).empty())
    {
        std::cerr << "player does not exist, adding new player\n";

        // Entity Manager allocates memory for a new entity
        // with tag name: "player" and places it in the vector 
        // of entities to be added
        std::shared_ptr<Entity> e = m_entities.addEntity(TAG_NAME[static_cast<int>(Tag::PLAYER)]);

        // Now we need to populate the player's component properties
        e->add<CTransform>(pos, vel, SPAWN_ANGLE);

        // Collision Properties 
        e->add<CCollision>(m_playerConfig.collisionRadius);

        // Shape properties
        e->add<CShape>(m_playerConfig.shapeRadius, m_playerConfig.shapeVertices,
                    m_playerConfig.fillColor, m_playerConfig.outlineColor, m_playerConfig.outlineThickness);

        // Add an input component to the player so we can use inputs 
        e->add<CInput>();
    }
    else
    {
        std::cerr << __PRETTY_FUNCTION__ << "TODO: "
        << "When a player already exists, we do not need to add a new player, just respawn it in widow center\n";
        player()->get<CShape>().circle.setPosition(pos);
        player()->get<CTransform>().velocity = vel;         // likely redundant due to way current vel calculated
        player()->get<CTransform>().angle = SPAWN_ANGLE;
    }
}


// spawn an enemy at a random position
void Game::spawnEnemy()
{
    // Enemy must be spawned within bounds of the window
    // Enemies will spawn in a random location
    // Enemies must not overlap the sides of the screen at the time of spawn.
    sf::Vector2u boundary = m_window.getSize();
    Vec2f pos;
    pos.x = m_rg.generate(m_enemyConfig.shapeRadius, boundary.x - m_enemyConfig.shapeRadius);
    pos.y = m_rg.generate(m_enemyConfig.shapeRadius, boundary.y - m_enemyConfig.shapeRadius);

    // Enemies will be given a random speed upon spawning, between a minimum and 
    // maximum value specified in the config file.
    float speed = m_rg.generate(m_enemyConfig.minSpeed, m_enemyConfig.maxSpeed);
    Vec2<float> vel = {1.0f, 1.0f}; 
    vel = vel.normalize();
    vel *= speed;   

    // Enemies shapes have random number of vertices, between a given minimum and
    // maximum number, which is also specified in the config file.
    int vertices = m_rg.generate(m_enemyConfig.minVertices, m_enemyConfig.maxVertices);

    // Enemies will be given a random color upon spawning
    sf::Color fillColor;
    fillColor.r = m_rg.generate(0,255);
    fillColor.g = m_rg.generate(0,255);
    fillColor.b = m_rg.generate(0,255);

    // Entity Manager allocates memory for a new entity
    // with tag name: "enemy" and places it in the vector 
    // of entities to be added
    std::shared_ptr<Entity> e = m_entities.addEntity(TAG_NAME[static_cast<int>(Tag::ENEMY)]);

    // Now we need to populate the player's component properties
    e->add<CTransform>(pos, vel, SPAWN_ANGLE);

    // Shape properties
    //Enemy shape radius will be specified in the config file.
    e->add<CShape>(m_enemyConfig.shapeRadius, vertices, fillColor, 
                    m_enemyConfig.outlineColor, m_enemyConfig.outlineThickness);

    // no lifespan component. Remains alive until shot with bullet
    // no input component

    e->add<CScore>(vertices*SCORE_MULTIPLE);
    e->add<CCollision>(m_enemyConfig.collisionRadius);
  
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

    Vec2f origin = e->get<CTransform>().pos;
    float speed = e->get<CTransform>().velocity.magnitude();

    size_t vertices = e->get<CShape>().circle.getPointCount();
    int score = e->get<CScore>().score * 2;

    float shapeRadius = m_enemyConfig.shapeRadius / 2.0f;
    int collisionRadius = m_enemyConfig.collisionRadius / 2.0f;

    float angleIncrement = 360.0f / vertices;
    float angleDegree = 0.0f;

    sf::Color fillColor = e->get<CShape>().circle.getFillColor();

    for(size_t i = 0; i < vertices; i++, angleDegree += angleIncrement)
    {
        std::shared_ptr<Entity> e = m_entities.addEntity(TAG_NAME[static_cast<int>(Tag::SMALL_ENEMY)]);
        
        // transform properties
        float angleRad = angleDegree * PI / 180.0f;
        Vec2f vel = {speed * std::cos(angleRad), speed * std::sin(angleRad)};
        e->add<CTransform>(origin, vel, angleDegree);

        e->add<CShape>(shapeRadius, vertices, fillColor, m_enemyConfig.outlineColor, m_enemyConfig.outlineThickness);
        e->add<CCollision>(collisionRadius);
        e->add<CScore>(score);
        e->add<CLifeSpan>(m_enemyConfig.smallLifespan);
    }
}



void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2f & target)
{
    
    // Implement the spawning fo a bullet which travels toward target 
    //     - bullet speed is given as a scalar speed 
    //     - you must set the velocity of x, y componnents 

    std::shared_ptr<Entity> bullet = m_entities.addEntity(TAG_NAME[static_cast<int>(Tag::BULLET)]);

    // bullet should be spawned at the entity origin
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
    sEnemyMovement();
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
    }
    else if(input.down == true)
    {
        currentVelocity.y = transform.velocity.y;
    }

    if(input.left == true)
    {
        currentVelocity.x = -transform.velocity.x;
    }
    else if(input.right == true)
    {
        currentVelocity.x = transform.velocity.x;
    }

    transform.pos.x += currentVelocity.x;
    transform.pos.y += currentVelocity.y;
}

void Game::sEnemyMovement()
{
    for(auto& e : m_entities.getEntities(TAG_NAME[static_cast<int>(Tag::ENEMY)]))
    {
       e->get<CTransform>().pos += e->get<CTransform>().velocity;
    }

    for(auto& e : m_entities.getEntities(TAG_NAME[static_cast<int>(Tag::SMALL_ENEMY)]))
    {
       e->get<CTransform>().pos += e->get<CTransform>().velocity;
    }
}

void Game::sBulletMovement()
{
    for(auto& b : m_entities.getEntities("bullet"))
    {
        if(b->isAlive())
        {
            // update position 
            b->get<CTransform>().pos += b->get<CTransform>().velocity;
        }
    }
}

void Game::sLifeSpan(Tag tag )
{
    for(auto& e : m_entities.getEntities(TAG_NAME[static_cast<int>(tag)]))
    {
        CLifeSpan& lifespan = e->get<CLifeSpan>();
       
         // if entity has > 0 remaining lifespan, subtract 1 
        if(lifespan.remaining > 0)
        {
            lifespan.remaining -= 1;

            // scale alpha channel remaining / total lifespan
            float alpha = static_cast<float>(lifespan.remaining) * 255.0f / 
                                static_cast<float>(lifespan.lifespan);
                
            sf::Color fillColor = 
            {
                m_bulletConfig.fillColor.r, 
                m_bulletConfig.fillColor.g, 
                m_bulletConfig.fillColor.b,
                static_cast<uint8_t>(alpha)
            };

            e->get<CShape>().circle.setFillColor(fillColor);
        }
        else
        {
            e->destroy();
        }
    }
}


void Game::sLifespan()
{
    // TODO: implement all lifespan functionality 
    // for all entities
    //      if entity has no lifespan component, skip it 
    
    sLifeSpan(Tag::BULLET);
    sLifeSpan(Tag::SMALL_ENEMY); 
}


void Game::sCollision()
{
    // TODO: implement all proper collisions between entities 
    //      be sure to use the collision radius, NOT the shape radius 

    // Note data types of b, e are shared_ptr so a copy of the pointer 
    // will make permanent changes to memory. We don't need auto&
    for(auto b : m_entities.getEntities("bullet"))
    {
        Vec2f& bpos = b->get<CTransform>().pos; 
        float bRadius = b->get<CCollision>().radius;
        bool collisionDetected = false;                 // determines if bullet is destroyed

        for(auto e : m_entities.getEntities(TAG_NAME[static_cast<int>(Tag::ENEMY)]))
        {
            // calc distance between centers 
            float dist = bpos.distance(e->get<CTransform>().pos);
            if(dist <=  (bRadius + e->get<CCollision>().radius))
            {
                // Not destroying bullet here. Assuming bullet can destroy 
                // multiple enemies when those enemies are overlapping.
                // Enemies are allowed to collide with each other.
                // Bullet will be destroyed later when this state variable is checked.
                collisionDetected = true;

                m_score += e->get<CScore>().score;          // update score
                spawnSmallEnemies(e);
                e->destroy();                               // destroy enemy entity          
            }
            
        }

        for(auto e : m_entities.getEntities(TAG_NAME[static_cast<int>(Tag::SMALL_ENEMY)]))
        {
            // calc distance between centers 
            float dist = bpos.distance(e->get<CTransform>().pos);
            if(dist <=  (bRadius + e->get<CCollision>().radius))
            {
                collisionDetected = true;
                m_score += e->get<CScore>().score;
                e->destroy();   
            }
        }

        if(collisionDetected == true)
        {
            b->destroy();
        }
    }       // end of bullet loop


    // TODO: also need to check player collision with all enemies

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
   
    Vec2f wallBoundary = m_window.getSize();
    sWallBoundaryNoBounce(player(), wallBoundary);

    for(auto& e : m_entities.getEntities(TAG_NAME[static_cast<int>(Tag::ENEMY)]))
    {
        sWallBoundary(e, wallBoundary);
    }
    
}

void Game::sWallBoundaryNoBounce(std::shared_ptr<Entity> entity, const Vec2f& boundary)
{
    Vec2f pos = entity->get<CTransform>().pos;
    float radius = entity->get<CCollision>().radius;
    if(pos.x - radius <= 0.0f)
    {
        entity->get<CTransform>().pos.x = radius;
    }
    else if(pos.x + radius >= boundary.x)
    {
        entity->get<CTransform>().pos.x = boundary.x - radius;
    }

    if(pos.y - radius <= 0.0f) 
    {
        entity->get<CTransform>().pos.y = radius;
    }
    else if(pos.y + radius >= boundary.y)
    {
        entity->get<CTransform>().pos.y = boundary.y - radius;
    }

}

// entity bounces off wall when colliding
void Game::sWallBoundary(std::shared_ptr<Entity> entity, const Vec2f& boundary)
{
    Vec2f pos = entity->get<CTransform>().pos;
    float radius = entity->get<CCollision>().radius;
    if(pos.x - radius <= 0.0f)
    {
        entity->get<CTransform>().pos.x = radius;
        entity->get<CTransform>().velocity.x *= -1;
    }
    else if(pos.x + radius >= boundary.x)
    {
        entity->get<CTransform>().pos.x = boundary.x - radius;
        entity->get<CTransform>().velocity.x *= -1;
    }

    if(pos.y - radius <= 0.0f) 
    {
        entity->get<CTransform>().pos.y = radius;
        entity->get<CTransform>().velocity.y *= -1;
    }
    else if(pos.y + radius >= boundary.y)
    {
        entity->get<CTransform>().pos.y = boundary.y - radius;
        entity->get<CTransform>().velocity.y *= -1;
    }
}

void Game::sSystemGui()
{
    static bool checkBoxMovement = true;
    static bool checkBoxLifeSpan = true;
    static bool checkBoxCollision = true;
    static bool checkBoxSpawning = true;
    
    static int spawnInterval = m_spawnInterval;

    static constexpr int MIN_SPAWN_INTERVAL = 0;
    static constexpr int MAX_SPAWN_INTERVAL = 240;

     if(ImGui::BeginTabItem("Systems"))    // create first tab 
    {
        if(ImGui::Checkbox("Movement", &checkBoxMovement))
        {
            if(checkBoxMovement == true)
            {
                m_pauseMovement = false;
            }
            else 
            {
                m_pauseMovement = true;
            }
        }

        if(ImGui::Checkbox("LifeSpan", &checkBoxLifeSpan))
        {
            if(checkBoxLifeSpan == true)
            {
                m_pauseLifeSpan = false;
            }
            else 
            {
                m_pauseLifeSpan = true;
            }
        }

        if(ImGui::Checkbox("Collision", &checkBoxCollision))
        {
            if(checkBoxCollision == true) 
            { 
                m_pauseCollision = false;
            }
            else 
            { 
                m_pauseCollision = true; 
            }
        }

        if(ImGui::Checkbox("Spawning", &checkBoxSpawning))
        {
            if(checkBoxSpawning == true) 
            { 
                m_pauseSpawning = false;
            }
            else 
            { 
                m_pauseSpawning = true; 
            }
        }

        ImGui::Indent();
        if(ImGui::SliderInt("Spawn Rate", &spawnInterval, MIN_SPAWN_INTERVAL, MAX_SPAWN_INTERVAL))
        {
            m_spawnInterval = spawnInterval;
        }

        if(ImGui::Button("Manual Spawn"))
        {
            spawnEnemy();
        }
        ImGui::Unindent();

        ImGui::EndTabItem();
    }
}

void Game::sEntityManagerGui()
{   
    static constexpr size_t NUM_TAGS = 4;

    if(ImGui::BeginTabItem("Entity Manager"))
    {
        if(ImGui::CollapsingHeader("Entities By Tag"))
        {
            ImGui::Indent();
            for(size_t i = 0; i < NUM_TAGS; i++)
            {
                if(ImGui::CollapsingHeader(TAG_NAME[i]))
                {
                    // button followed by id number, string "bullet" and position (x, y)
                    // button should show lifespan state bright white for alive 
                    // graying over time to black when dead
                    // Letter D in button to indicate it is deletable by mouse right-click
                    int buttonId = 0;
                    for(auto& e : m_entities.getEntities(TAG_NAME[i]))
                    {
                        ImGui::PushID(buttonId);

                        // set button text color to black
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

                        // set button background color, same as bullet fill color
                        ImVec4 buttonColor = e->get<CShape>().circle.getFillColor();
                        ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
                        std::string buttonLabel = "D##" + std::to_string(buttonId);
                        

                        if(ImGui::Button(buttonLabel.c_str()))
                        {
                            e->destroy();
                            std::cerr << "button " << buttonId << " clicked\n";
                            std::cerr << "remaining " << e->get<CLifeSpan>().remaining << "\n";
                        }

                        ImGui::PopStyleColor();
                        ImGui::PopStyleColor();

                        ImGui::SameLine();
                        std::string id = std::to_string(e->id());
                        ImGui::Text("%4lu", e->id());
                        ImGui::SameLine();
                        ImGui::Text("%s", e->tag().c_str());
                        ImGui::SameLine();
                        ImGui::Text("(%.0f, %.0f)", e->get<CTransform>().pos.x, e->get<CTransform>().pos.y);

                        ImGui::PopID();
                        buttonId++;
                    }
                }
            }       // end for loop iterating through tags

            ImGui::Unindent();
          
        }   // End top-level collapsing header

        ImGui::EndTabItem();
    }

}


void Game::sGUI()
{ 
    ImGui::Begin("Geometry Wars");          // create main window

    if(ImGui::BeginTabBar("MyTabBar"))      // create tab bar within the window
    {
        sSystemGui();
        sEntityManagerGui();
        ImGui::EndTabBar();
    }

    ImGui::End();                       // end main window
}



void Game::sRender()
{
    if(!m_window.isOpen()) { return; }

    m_window.clear(sf::Color::Black);
    sRenderPlayer();
    sRenderBullet();
    sRenderEnemy();

    m_window.draw(m_text);

    // draw the ui last 
    ImGui::SFML::Render(m_window);

    m_window.display();

}

void Game::sRenderPlayer()
{
    
    // set the position of the shape based on the entity's transform->pos 
    player()->get<CShape>().circle.setPosition(player()->get<CTransform>().pos);
    
    // set the rotation of the shape based on the entity's transform->angle 
    player()->get<CTransform>().angle += 1.0;
    player()->get<CShape>().circle.setRotation(sf::degrees(player()->get<CTransform>().angle));

    // draw the entity's sf::CircleShape
    m_window.draw(player()->get<CShape>().circle);

}

void Game::sRenderEnemy()
{
    // draw enemies
    for(auto& e : m_entities.getEntities(TAG_NAME[static_cast<int>(Tag::ENEMY)]))
    {
        // set the shape rotation based on entity's transform angle
        e->get<CTransform>().angle += 1.0;
        e->get<CShape>().circle.setRotation(sf::degrees(e->get<CTransform>().angle));

        e->get<CShape>().circle.setPosition(e->get<CTransform>().pos);
            
        m_window.draw(e->get<CShape>().circle);
    }

}

void Game::sRenderBullet()
{
    // draw bullets 
    for(const auto& e : m_entities.getEntities(TAG_NAME[static_cast<int>(Tag::BULLET)]))
    {
        e->get<CShape>().circle.setPosition(e->get<CTransform>().pos);
        m_window.draw(e->get<CShape>().circle);
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
        // Get the ImGui IO object
        auto& io = ImGui::GetIO();

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

        // Check the ImGui IO object flag before processing a mouse click 
        // If the flag is true, skip the game's click logic because the click occurred
        // in the ImGui 
        if(!io.WantCaptureMouse)
        {            
            if(const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                Vec2f mpos = {static_cast<float>(mousePressed->position.x), 
                                static_cast<float>(mousePressed->position.y)};
                if(mousePressed->button == sf::Mouse::Button::Left)
                {
                    spawnBullet(player(), mpos);

                }
                else if(mousePressed->button == sf::Mouse::Button::Right)
                {
                    // TODO: call special weapon here 
                    std::cout << "Right mouse (" << mpos.x << ", " << mpos.y << "), no special weapon added yet\n";
                }
            }
        }
    }
}