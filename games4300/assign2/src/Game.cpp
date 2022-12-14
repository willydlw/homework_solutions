#include "Game.h"
#include "Vec2.h"

#include <fstream>
#include <iostream>
#include <utility>         // make_pair
#include <cmath>
#include <cstdlib>         // rand

/* ============================
   Class Constants
*/

const int Game::LARGE_ENTITY_SCORE = 200;
const int Game::SMALL_ENTITY_SCORE = 100;
const float Game::DEFAULT_ROTATION_ANGLE = 0.0f;

std::string const Game::DEFAULT_FONT_FILE = "../fonts/tech.ttf";

const WindowConfig Game::WINDOW_CONFIG_DEFAULT = { 
    1280, 720,  // W, H
    60,         // FL
    0           // FS
};


const FontConfig Game::FONT_CONFIG_DEFAULT = { 
    Game::DEFAULT_FONT_FILE,  // F
    32,                 // S
    255, 255, 255       // R, G, B
};


const PlayerConfig Game::PLAYER_CONFIG_DEFAULT = {
    32, 32,         // SR, CR
    10, 10, 10,     // FR, FG, FB
    255, 0, 0,      // OR, OG, OB
    4,              // OT
    8,              // V
    4.0f            // S
};


const EnemyConfig Game::ENEMY_CONFIG_DEFAULT ={ 
    16, 16,         // SR, CR
    255, 255, 255,  // OR, OG, OB
    3,              // OT
    3, 10,          // VMIN, VMAX
    30,             // L
    60,             // SI
    1, 10           // SMIN, SMAX
};


const BulletConfig Game::BULLET_CONFIG_DEFAULT = { 
    10,             // SR 
    10,             // CR
    0, 255, 0,      // FR, FG, FB,
    255, 255, 255,  // OR, OG, OB
    2,              // OT
    3,              // V 
    60,             // L
    10.0f           // S
 };

const std::map<std::string, Game::ConfigCategory> Game::CONFIG_CATEGORY_MAP = {
    std::make_pair(std::string("unknown"), Game::ConfigCategory::UNKNOWN),
    std::make_pair(std::string("bullet"), Game::ConfigCategory::BULLET),
    std::make_pair(std::string("enemy"), Game::ConfigCategory::ENEMY),
    std::make_pair(std::string("font"), Game::ConfigCategory::FONT),
    std::make_pair(std::string("player"), Game::ConfigCategory::PLAYER),
    std::make_pair(std::string("window"), Game::ConfigCategory::WINDOW)  
};

Game::Game(const std::string& config)
{
    init(config);
}

Game::ConfigCategory Game::readConfigCategory(std::istream& ins)
{
    std::string category("unknown");
    
    ins >> category;    // read category

    std::cerr << __FUNCTION__ << " ,category: " << category << "\n";

    std::cerr << "Troubleshooting, will now print CONFIG_CATEGORY_MAP\n";

    for(auto& m : CONFIG_CATEGORY_MAP)
    {
        std::cerr << "first: " << m.first << ", second: " << (int) m.second << "\n";
    }

    auto c = CONFIG_CATEGORY_MAP.find(category);

    if(c != CONFIG_CATEGORY_MAP.end())
    {
        std::cerr << "not the end\n";
    }

    std::cerr << __FUNCTION__ << ", c->second: "
        << int(c->second) << "\n";
    return c->second;
}

void Game::processConfigCategory(std::istream& ins, ConfigCategory category)
{
    std::cerr << "Entering " << __FUNCTION__ << "\n";
    switch(category)
    {
        case ConfigCategory::BULLET:
            std::cerr << "calling loadBulletConfig\n";
            loadBulletConfig(ins);
            break;
        case ConfigCategory::ENEMY:
            loadEnemyConfig(ins);
            break;
        case ConfigCategory::FONT:
            loadFontConfig(ins);
            break;
        case ConfigCategory::PLAYER:
            loadPlayerConfig(ins);
            break;
        case ConfigCategory::WINDOW:
            loadWindowConfig(ins);
            break;
        case ConfigCategory::UNKNOWN:
            std::cerr << "Error, unhandled Category, " << __FUNCTION__ 
                << "\n";
            break;
    }

    std::cerr << "leaving " << __FUNCTION__ << "\n\n";
}

void Game::loadConfigFromFile(const std::string& path)
{
    ConfigCategory category = ConfigCategory::UNKNOWN;

    std::ifstream infile(path);

    if (!infile)
    {
        std::cerr << "WARNING: file open failure, path: " << path
            << ", using default configuration\n";
        loadDefaultConfig(ConfigState::WINDOW_DEFAULT);
        return;
    }

    std::cerr << __FUNCTION__ << ", Opened file: " << path << "\n";

    while(infile)
    {
        category = readConfigCategory(infile);

        std::cerr << __FUNCTION__ << ", returned from readConfighCategory, category value: " << (int)category << "\n";
        
        if(category != ConfigCategory::UNKNOWN)
        {
            processConfigCategory(infile, category);
            category = ConfigCategory::UNKNOWN;
        }
        else
        {
            std::cerr << __FUNCTION__ << ", category is UKNOWN, value: " << (int)category << "\n\n";
            //loadDefaultConfig(ConfigState::WINDOW_DEFAULT);
            break;
        }
    }
    
    /*
    if(infile)
    {
        processConfigCategory(infile, category);
    }
    

    if (!loadWindowConfig(infile))
    {
        std::cerr << "WARNING: failure to load window configuration from file " << path
            << ", using default configuration\n";
        loadDefaultConfig(ConfigState::WINDOW_DEFAULT);
        infile.close();
        return;
    }

    if (!loadFontConfig(infile))
    {
        std::cerr << "WARNING: failure to load font configuration from file " << path
            << ", using default configuration\n";
        loadDefaultConfig(ConfigState::FONT_DEFAULT);
        infile.close();
        return;
    }

    if (!loadPlayerConfig(infile))
    {
        std::cerr << "WARNING: failure to load player configuration from file "
            << path << ", using default configuration\n";
        loadDefaultConfig(ConfigState::PLAYER_DEFAULT);
        infile.close();
        return;
    }

    if (!loadEnemyConfig(infile))
    {
        std::cerr << "WARNING: failure to load enemy configuration from file "
            << path << ", using default configuration\n";
        loadDefaultConfig(ConfigState::ENEMY_DEFAULT);
        infile.close();
        return;
    }

    if (!loadBulletConfig(infile))
    {
        std::cerr << "WARNING: failure to load bullet configuration from file "
            << path << ", using default configuration\n";
        loadDefaultConfig(ConfigState::BULLET_DEFAULT);
        infile.close();
        return;
    }
    */
}

void Game::loadDefaultConfig(Game::ConfigState state)
{
    // Note: There are intentionally no break statements. Once there 
    // is a failure to load the configuration data, we need to 
    // configure all states below the case with the defaults.
    switch (state)
    {
    case ConfigState::WINDOW_DEFAULT:
        m_windowConfig = Game::WINDOW_CONFIG_DEFAULT;
        [[fallthrough]]; // fallthrough is explicit
    case ConfigState::FONT_DEFAULT:
        m_fontConfig = Game::FONT_CONFIG_DEFAULT;
        [[fallthrough]]; // fallthrough is explicit
    case ConfigState::PLAYER_DEFAULT:
        m_playerConfig = Game::PLAYER_CONFIG_DEFAULT;
        [[fallthrough]]; // fallthrough is explicit
    case ConfigState::ENEMY_DEFAULT:
        m_enemyConfig = Game::ENEMY_CONFIG_DEFAULT;
        [[fallthrough]]; // fallthrough is explicit
    case ConfigState::BULLET_DEFAULT:
        m_bulletConfig = Game::BULLET_CONFIG_DEFAULT;
    };
}

std::istream& Game::loadWindowConfig(std::istream& ins)
{
    ins >> m_windowConfig.W >> m_windowConfig.H >> m_windowConfig.FL >> m_windowConfig.FS;

    return ins;
}

std::istream& Game::loadFontConfig(std::istream& ins)
{
    ins >> m_fontConfig.F >> m_fontConfig.S >> m_fontConfig.R >> m_fontConfig.G >> m_fontConfig.B;
    return ins;
}

std::istream& Game::loadPlayerConfig(std::istream& ins)
{
    ins >> m_playerConfig.SR                                           // shape radius
        >> m_playerConfig.CR                                           // collision radius
        >> m_playerConfig.FR                                           // fill color
        >> m_playerConfig.FG >> m_playerConfig.FB >> m_playerConfig.OR // outline color
        >> m_playerConfig.OG >> m_playerConfig.OB >> m_playerConfig.OT // outline thickness
        >> m_playerConfig.V                                            // shape vertices
        >> m_playerConfig.S;                                           // speed
    return ins;
}

std::istream& Game::loadEnemyConfig(std::istream& ins)
{
    ins >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.OR >> m_enemyConfig.OG >> m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX;
    return ins;
}

std::istream& Game::loadBulletConfig(std::istream& ins)
{
    // Bullet SR CR S FR FG OR OG OB OT V L
    ins >> m_bulletConfig.SR >> m_bulletConfig.CR 
        >> m_bulletConfig.S
        >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB 
        >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB 
        >> m_bulletConfig.OT 
        >> m_bulletConfig.V 
        >> m_bulletConfig.L;

    std::cerr << __FUNCTION__ << " finished\n\n";
    printBulletConfig(std::cout);
    return ins;
}

/* Assumptions:
      no file stream read errors

   File Stream exceptions are not handled.
*/
void Game::init(const std::string& path)
{
    loadConfigFromFile(path);

    // set up default window parameters
    std::cerr << __func__ << ", WARNING: ignoring full screen mode option\n";
    m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "Geometry Wars");
    m_window.setFramerateLimit(m_windowConfig.FL);

    // set up font object
    if (!m_font.loadFromFile(m_fontConfig.F))
    {
        std::cerr << "ERROR: failed to load font from file: " << m_fontConfig.F << "\n";
        m_gameState = GameState::INIT_FAILURE;
        return;
    }

    // set up text object
    m_text.setFont(m_font);
    m_text.setCharacterSize(m_fontConfig.S);
    m_text.setFillColor(sf::Color(m_fontConfig.R, m_fontConfig.G, m_fontConfig.B));

    spawnPlayer();

    m_gameState = GameState::INIT_SUCCESS;
}

void Game::run()
{
    // TODO: add pause functionality in here
    //    some systems should function while paused (rendering)
    //    some systems should not function (movement / input)

    if (m_gameState != GameState::INIT_SUCCESS)
    {
        std::cerr << "Program terminating due to initialization error\n";
        return;
    }

    while (m_running)
    {
        /*m_entityManager.update();

        if (!m_paused)
        {
            sEnemySpawner();
            sMovement();
            sCollision();
        }

        sUserInput();
        sRender();
        */
        // increment the current frame
        // may need to be moved when pause implemented
        m_currentFrame++;
    }
}

void Game::setPaused(bool paused)
{
    // TODO
}


void Game::spawnPlayer()
{
    // We create every entity by calling EntityManager.addEntity(tag)
    // This returns a std::shared_ptr<Entity> and we use 'auto' to let C++ do the typing
    auto entity = m_entityManager.addEntity("player");

    // Player must spawn in the center of the screen at the beginning of the
    // game, and after it dies (collides with an enemy)
    float middleX = m_window.getSize().x / 2.0f;
    float middleY = m_window.getSize().y / 2.0f;

    // find velocity vector x, y values
    // when rotation angle is 0, cos(0) = 1, sin(0) = 0
    // could eliminate these calculations but will keep them in the implementation
    // in case the initial rotation angle is not zero in the future
    float velX = m_playerConfig.S * cos(DEFAULT_ROTATION_ANGLE);
    float velY = m_playerConfig.S * sin(DEFAULT_ROTATION_ANGLE);

    entity->cTransform = std::make_shared<CTransform>(Vec2(middleX, middleY),
        Vec2(velX, velY),
        DEFAULT_ROTATION_ANGLE);

    entity->cShape = std::make_shared<CShape>(
        m_playerConfig.SR,
        m_playerConfig.V,
        sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB),
        sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB),
        m_playerConfig.OT);

    entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);

    // add an input component to the player so that we can use inputs
    entity->cInput = std::make_shared<CInput>();

    // NOTE: Player does not have a score component or lifespan component
    // Leave these members of the entity class as null pointers. Do not
    // construct these components with make_shared.

    // since we want this entity to be our player, set our Game's player variable
    // to be this Entity. This goes slightly against the EntityManager paradigm, 
    // but we use the player so much it's worth it
    m_player = entity;
}

// spawn an enemy at a random position
void Game::spawnEnemy()
{
    // TODO: make sure the enemy is spawned properly with the m_enemyConfig variables
    //       the enemy must be spawned completely within the bounds of the window

    // optional: ensure enemy is not spawned in same location as player

    // create an entity with the tag name enemy
    auto entity = m_entityManager.addEntity("enemy");

    /*  Enemies are spawned in a random position within the bounds of the window

        Enemies must not overlap the sides of the screen at the time of spawn.

       x = random(0 + radius, width - radius)
       y = random(0 + radius, height - radius)
    */
    
    float posX = static_cast<float>(rand() % (m_window.getSize().x - m_enemyConfig.SR)) + m_enemyConfig.SR;
    float posY = static_cast<float>(rand() % (m_window.getSize().y - m_enemyConfig.SR)) + m_enemyConfig.SR;

    /* Enemies shapes have random number of vertices, between a given minimum and
       maximum number, which is also specified in the config file.
    */
    int numVertices = (rand() % (m_enemyConfig.VMAX - m_enemyConfig.VMIN + 1)) + m_enemyConfig.VMIN;

    // Enemies will be given a random color upon spawning
    sf::Color fillColor(rand() % 256, rand() % 256, rand() % 256);

    // Outline color specified in config
    sf::Color outlineColor(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB);

    /* Enemies will be given a random speed upon spawning, between a minimum and
       maximum value specified in the config file.
    */
    int speed = (rand() % ((int)m_enemyConfig.SMAX - (int)m_enemyConfig.SMIN + 1)) + (int)m_enemyConfig.SMIN;
    float velX = speed * cos(DEFAULT_ROTATION_ANGLE);
    float velY = speed * sin(DEFAULT_ROTATION_ANGLE);

    entity->cTransform = std::make_shared<CTransform>(Vec2(posX, posY),
        Vec2(velX, velY),
        DEFAULT_ROTATION_ANGLE);

    entity->cShape = std::make_shared<CShape>(
        m_enemyConfig.SR,
        numVertices,
        fillColor,
        outlineColor,
        m_enemyConfig.OT);

    entity->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);

    entity->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);

    // record when the most recent enemy was spawned
    m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
    // TODO: spawn small enemies at the location of the input enemy e

    // when we create the smaller enemy, we have to read the values of the original enemy
}

void Game::sCollision()
{
    // TODO: implement all proper collisions between entities
    //    be sure to use the collision radius, NOT the shape radius
}

void Game::sEnemySpawner()
{
    // TODO: code which implements enemy spawing should go here
    //    (use m_currentFrame - m_lastEnemySpawnTime) to determine
    //    how long it has been since the last enemy spawned
}

void Game::sRender()
{
    // TODO: change the code below to draw all the entities
    //    sample drawing of the player Entity that we have created

    m_window.clear();

    // set the position of the shape based on the entity's tranform->pos
    m_player->cShape->circle.setPosition(m_player->cTransform->pos.x, m_player->cTransform->pos.y);

    // set the rotation of the shape based on the entity's transform->angle
    m_player->cTransform->angle += 1.0f;
    m_player->cShape->circle.setRotation(m_player->cTransform->angle);

    // draw the entity's sf::CircleShape
    m_window.draw(m_player->cShape->circle);

    m_window.display();
}

void Game::sUserInput()
{
    // TODO: handle user input here
    //    note taht you should only be setting the player's input component variables here
    //    you should not implement teh player's movement logic here
    //    the movement system will read the variables you set in this function

    //sf::Event event;
}

std::ostream& Game::printWindowConfig(std::ostream& os) const
{
    os << "width:              " << m_windowConfig.W << "\n"
        << "height:             " << m_windowConfig.H << "\n"
        << "frame limit:        " << m_windowConfig.FL << "\n"
        << "full screen mode:   " << m_windowConfig.FS << "\n";
    return os;
}

std::ostream& Game::printFontConfig(std::ostream& os) const
{
    os << "font file:          " << m_fontConfig.F << "\n"
        << "font size:          " << m_fontConfig.S << "\n"
        << "font color red:     " << m_fontConfig.R << "\n"
        << "font color green:   " << m_fontConfig.G << "\n"
        << "font color blue:    " << m_fontConfig.B << "\n";
    return os;
}

std::ostream& Game::printPlayerConfig(std::ostream& os) const
{
    os << "shape radius:             " << m_playerConfig.SR << "\n"
        << "collision radius:         " << m_playerConfig.CR << "\n"
        << "fill color red:           " << m_playerConfig.FR << "\n"
        << "fill color green:         " << m_playerConfig.FG << "\n"
        << "fill color blue:          " << m_playerConfig.FB << "\n"
        << "outline color red:        " << m_playerConfig.OR << "\n"
        << "outline color green:      " << m_playerConfig.OG << "\n"
        << "outline color blue:       " << m_playerConfig.OB << "\n"
        << "outline color thickness:  " << m_playerConfig.OT << "\n"
        << "vertices:                 " << m_playerConfig.V << "\n"
        << "speed:                    " << m_playerConfig.S << "\n";
    return os;
}

std::ostream& Game::printEnemyConfig(std::ostream& os) const
{
    os << "shape radius:             " << m_enemyConfig.SR << "\n"
        << "collision radius:         " << m_enemyConfig.CR << "\n"
        << "outline color red:        " << m_enemyConfig.OR << "\n"
        << "outline color green:      " << m_enemyConfig.OG << "\n"
        << "outline color blue:       " << m_enemyConfig.OB << "\n"
        << "outline color thickness:  " << m_enemyConfig.OT << "\n"
        << "minimum vertices:         " << m_enemyConfig.VMIN << "\n"
        << "maximum vertices:         " << m_enemyConfig.VMAX << "\n"
        << "small lifespan:           " << m_enemyConfig.L << "\n"
        << "spawn interval:           " << m_enemyConfig.SI << "\n"
        << "minimum speed:            " << m_enemyConfig.SMIN << "\n"
        << "maximum speed:            " << m_enemyConfig.SMAX << "\n";
    return os;
}

std::ostream& Game::printBulletConfig(std::ostream& os) const
{
    os << "shape radius:             " << m_bulletConfig.SR << "\n"
        << "collision radius:         " << m_bulletConfig.CR << "\n"
        << "fill color red:           " << m_bulletConfig.FR << "\n"
        << "fill color green:         " << m_bulletConfig.FG << "\n"
        << "fill color blue:          " << m_bulletConfig.FB << "\n"
        << "outline color red:        " << m_playerConfig.OR << "\n"
        << "outline color green:      " << m_bulletConfig.OG << "\n"
        << "outline color blue:       " << m_bulletConfig.OB << "\n"
        << "outline color thickness:  " << m_bulletConfig.OT << "\n"
        << "vertices:                 " << m_bulletConfig.V << "\n"
        << "lifespan:                 " << m_bulletConfig.L << "\n"
        << "speed:                    " << m_bulletConfig.S << "\n";
    return os;
}
