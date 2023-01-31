#include "Game.h"
#include "Vec2.h"

#include <algorithm> // transform
#include <fstream>
#include <iostream>
#include <utility> // make_pair
#include <cmath>
#include <cstdlib> // rand
#include <string>

/* ============================
   Class Constants
*/

const int Game::LARGE_ENTITY_SCORE = 200;
const int Game::SMALL_ENTITY_SCORE = 100;
const float Game::DEFAULT_ROTATION_ANGLE = 0.0f;

std::string const Game::DEFAULT_FONT_FILE = "../fonts/tech.ttf";

const WindowConfig Game::WINDOW_CONFIG_DEFAULT = {
    1280, 720, // W, H
    60,        // FL
    0          // FS
};

const FontConfig Game::FONT_CONFIG_DEFAULT = {
    Game::DEFAULT_FONT_FILE, // F
    32,                      // S
    255, 255, 255            // R, G, B
};

const PlayerConfig Game::PLAYER_CONFIG_DEFAULT = {
    32, 32,     // SR, CR
    10, 10, 10, // FR, FG, FB
    255, 0, 0,  // OR, OG, OB
    4,          // OT
    8,          // V
    4.0f        // S
};

const EnemyConfig Game::ENEMY_CONFIG_DEFAULT = {
    16, 16,        // SR, CR
    255, 255, 255, // OR, OG, OB
    3,             // OT
    3, 10,         // VMIN, VMAX
    30,            // L
    60,            // SI
    1, 10          // SMIN, SMAX
};

const BulletConfig Game::BULLET_CONFIG_DEFAULT = {
    10,            // SR
    10,            // CR
    0, 255, 0,     // FR, FG, FB,
    255, 255, 255, // OR, OG, OB
    2,             // OT
    3,             // V
    60,            // L
    10.0f          // S
};

const std::map<std::string, Game::ConfigCategory> Game::CONFIG_CATEGORY_MAP = {
    std::make_pair(std::string("unknown"), Game::ConfigCategory::UNKNOWN),
    std::make_pair(std::string("bullet"), Game::ConfigCategory::BULLET),
    std::make_pair(std::string("enemy"), Game::ConfigCategory::ENEMY),
    std::make_pair(std::string("font"), Game::ConfigCategory::FONT),
    std::make_pair(std::string("player"), Game::ConfigCategory::PLAYER),
    std::make_pair(std::string("window"), Game::ConfigCategory::WINDOW)};

Game::Game(const std::string &config)
{
    init(config);
}

Game::ConfigCategory Game::readConfigCategory(std::istream &ins)
{
    std::string category;

    if (!(ins >> category))
    {
        if (ins.eof())
        {
            return ConfigCategory::ENDFILE;
        }
        else
        {
            printErrorMessage("ERROR reading category", __FILE__, __FUNCTION__, __LINE__);
            return ConfigCategory::UNKNOWN;
        }
    }

    std::transform(category.begin(), category.end(), category.begin(), ::tolower);

    auto c = CONFIG_CATEGORY_MAP.find(category);
    if (c == CONFIG_CATEGORY_MAP.end())
    {
        std::string msg("WARNING, category: ");
        msg.append(category);
        msg.append(" not found in config map");
        printErrorMessage(msg, __FILE__, __FUNCTION__, __LINE__);
        return ConfigCategory::UNKNOWN;
    }

    return c->second;
}

bool Game::processConfigCategory(std::istream &ins, ConfigCategory category, int &configStatus)
{
    int success = false;
    switch (category)
    {
    case ConfigCategory::BULLET:
        std::cerr << __FILE__ << ", " << __FUNCTION__ << ", line: " << __LINE__ << ", calling loadBulletConfig\n";
        if (loadBulletConfig(ins))
        {
            configStatus |= (1 << (int)ConfigCategory::BULLET);
            std::cout << "\nBullet Config\n";
            printBulletConfig(std::cout);
            std::cout << "\n\n";
            success = true;
        }
        break;
    case ConfigCategory::ENEMY:
        std::cerr << __FILE__ << ", " << __FUNCTION__ << ", line: " << __LINE__ << ", calling loadEnemyConfig\n";
        if (loadEnemyConfig(ins))
        {
            configStatus |= (1 << (int)ConfigCategory::ENEMY);
            std::cout << "\nEnemy Config\n";
            printEnemyConfig(std::cout);
            std::cout << "\n\n";
            success = true;
        }
        break;
    case ConfigCategory::FONT:
        std::cerr << __FILE__ << ", " << __FUNCTION__ << ", line: " << __LINE__ << ", calling loadFontConfig\n";
        if (loadFontConfig(ins))
        {
            configStatus |= (1 << (int)ConfigCategory::FONT);
            std::cout << "\nFont Config\n";
            printFontConfig(std::cout);
            std::cout << "\n\n";
            success = true;
        }
        break;
    case ConfigCategory::PLAYER:
        std::cerr << __FILE__ << ", " << __FUNCTION__ << ", line: " << __LINE__ << ", calling loadPlayerConfig\n";
        if (loadPlayerConfig(ins))
        {
            configStatus |= (1 << (int)ConfigCategory::PLAYER);
            std::cout << "\nPlayer Config\n";
            printPlayerConfig(std::cout);
            std::cout << "\n\n";
            success = true;
        }
        break;
    case ConfigCategory::WINDOW:
        std::cerr << __FILE__ << ", " << __FUNCTION__ << ", line: " << __LINE__ << ", calling loadWindowConfig\n";
        if (loadWindowConfig(ins))
        {
            configStatus |= (1 << (int)ConfigCategory::WINDOW);
            std::cout << "\nWindow Config\n";
            printWindowConfig(std::cout);
            std::cout << "\n\n";
            success = true;
        }
        break;

    // why ENDFILE state? to handle final new line extraction
    // when reading config file
    case ConfigCategory::ENDFILE:
        success = true;
        break;
    case ConfigCategory::UNKNOWN:
        std::cerr << __FILE__ << ", "
                  << __FUNCTION__ << ", line: " << __LINE__
                  << ", Error, unhandled Category, "
                  << "\n";
        break;
    }

    return success;
}

void Game::verifyCompleteConfig(int configStatus)
{
    if (!(configStatus & (1 << (int)ConfigCategory::BULLET)))
    {
        printErrorMessage("Warning: Using default bullet configuration",
                          __FILE__, __FUNCTION__, __LINE__);
        m_bulletConfig = BULLET_CONFIG_DEFAULT;
    }

    if (!(configStatus & (1 << (int)ConfigCategory::FONT)))
    {
        printErrorMessage("Warning: Using default font configuration",
                          __FILE__, __FUNCTION__, __LINE__);
        m_fontConfig = FONT_CONFIG_DEFAULT;
    }

    if (!(configStatus & (1 << (int)ConfigCategory::ENEMY)))
    {
        printErrorMessage("Warning: Using default enemy configuration",
                          __FILE__, __FUNCTION__, __LINE__);
        m_enemyConfig = ENEMY_CONFIG_DEFAULT;
    }

    if (!(configStatus & (1 << (int)ConfigCategory::PLAYER)))
    {
        printErrorMessage("Warning: Using default player configuration",
                          __FILE__, __FUNCTION__, __LINE__);
        m_playerConfig = PLAYER_CONFIG_DEFAULT;
    }

    if (!(configStatus & (1 << (int)ConfigCategory::WINDOW)))
    {
        printErrorMessage("Warning: Using default window configuration",
                          __FILE__, __FUNCTION__, __LINE__);
        m_windowConfig = WINDOW_CONFIG_DEFAULT;
    }
}

void Game::loadConfigFromFile(const std::string &path)
{
    ConfigCategory category = ConfigCategory::UNKNOWN;

    int configStatus = 0;

    std::ifstream infile(path);

    if (!infile)
    {
        std::string msg("WARNING: file open failure, path: ");
        msg.append(path);
        msg.append(", using default configuration\n");
        printErrorMessage(msg, __FILE__, __FUNCTION__, __LINE__);
        loadDefaultConfig(ConfigState::WINDOW_DEFAULT);
        return;
    }

    while (infile)
    {
        category = readConfigCategory(infile);

        if (category != ConfigCategory::UNKNOWN)
        {
            if (!processConfigCategory(infile, category, configStatus))
            {
                break;
            }
        }
        else
        {
            std::cerr << __FUNCTION__ << ", category is UKNOWN, value: " << (int)category << "\n\n";
            break;
        }
    }

    verifyCompleteConfig(configStatus);
}

void Game::loadDefaultConfig(Game::ConfigState state)
{
    printErrorMessage("DEBUG status, entering function\n", __FUNCTION__, __FILE__, __LINE__);
    // Note: There are intentionally no break statements. Once there
    // is a failure to load the configuration data, we need to
    // configure all states below the case with the defaults.
    switch (state)
    {
    case ConfigState::WINDOW_DEFAULT:
        printErrorMessage("DEBUG status, case WINDOW_DEFAULT\n", __FUNCTION__, __FILE__, __LINE__);
        m_windowConfig = Game::WINDOW_CONFIG_DEFAULT;
        [[fallthrough]]; // fallthrough is explicit
    case ConfigState::FONT_DEFAULT:
        printErrorMessage("DEBUG status, case FONT_DEFAULT\n", __FUNCTION__, __FILE__, __LINE__);
        m_fontConfig = Game::FONT_CONFIG_DEFAULT;
        [[fallthrough]]; // fallthrough is explicit
    case ConfigState::PLAYER_DEFAULT:
        printErrorMessage("DEBUG status, case PLAYER_DEFAULT\n", __FUNCTION__, __FILE__, __LINE__);
        m_playerConfig = Game::PLAYER_CONFIG_DEFAULT;
        [[fallthrough]]; // fallthrough is explicit
    case ConfigState::ENEMY_DEFAULT:
        printErrorMessage("DEBUG status, case ENEMY_DEFAULT\n", __FUNCTION__, __FILE__, __LINE__);
        m_enemyConfig = Game::ENEMY_CONFIG_DEFAULT;
        [[fallthrough]]; // fallthrough is explicit
    case ConfigState::BULLET_DEFAULT:
        printErrorMessage("DEBUG status, case BULLET_DEFAULT\n", __FUNCTION__, __FILE__, __LINE__);
        m_bulletConfig = Game::BULLET_CONFIG_DEFAULT;
    };

    printErrorMessage("DEBUG status, leaving function\n", __FUNCTION__, __FILE__, __LINE__);
}

bool Game::loadWindowConfig(std::istream &ins)
{
    if (!(ins >> m_windowConfig.W))
    {
        printErrorMessage("ERROR reading width", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_windowConfig.H))
    {
        printErrorMessage("ERROR reading height", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_windowConfig.FL))
    {
        printErrorMessage("ERROR reading frame limit", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_windowConfig.FS))
    {
        printErrorMessage("ERROR reading full screen mode", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    return true;
}

bool Game::loadFontConfig(std::istream &ins)
{
    if (!(ins >> m_fontConfig.F))
    {
        printErrorMessage("ERROR reading font file", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_fontConfig.S))
    {
        printErrorMessage("ERROR reading font size", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_fontConfig.R))
    {
        printErrorMessage("ERROR reading font red", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_fontConfig.G))
    {
        printErrorMessage("ERROR reading font green", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_fontConfig.B))
    {
        printErrorMessage("ERROR reading font blue", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    return true;
}

bool Game::loadPlayerConfig(std::istream &ins)
{
    if (!(ins >> m_playerConfig.SR))
    {
        printErrorMessage("ERROR reading shape radius", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_playerConfig.CR))
    {
        printErrorMessage("ERROR reading collision radius", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_playerConfig.S))
    {
        printErrorMessage("ERROR reading speed", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_playerConfig.FR))
    {
        printErrorMessage("ERROR reading fill red", __FILE__, __FUNCTION__, __LINE__);
        return false;
    } // fill color
    if (!(ins >> m_playerConfig.FG))
    {
        printErrorMessage("ERROR reading fill green", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_playerConfig.FB))
    {
        printErrorMessage("ERROR reading fill blue", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_playerConfig.OR))
    {
        printErrorMessage("ERROR reading outline red", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_playerConfig.OG))
    {
        printErrorMessage("ERROR reading outline green", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_playerConfig.OB))
    {
        printErrorMessage("ERROR reading outline blue", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_playerConfig.OT))
    {
        printErrorMessage("ERROR reading outline thickness", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_playerConfig.V))
    {
        printErrorMessage("ERROR reading vertices", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    return true;
}

bool Game::loadEnemyConfig(std::istream &ins)
{
    if (!(ins >> m_enemyConfig.SR))
    {
        printErrorMessage("ERROR reading shape radius", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_enemyConfig.CR))
    {
        printErrorMessage("ERROR reading collision radius", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_enemyConfig.SMIN))
    {
        printErrorMessage("ERROR reading speed min", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_enemyConfig.SMAX))
    {
        printErrorMessage("ERROR reading speed max", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_enemyConfig.OR))
    {
        printErrorMessage("ERROR reading outline red", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_enemyConfig.OG))
    {
        printErrorMessage("ERROR reading outline green", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_enemyConfig.OB))
    {
        printErrorMessage("ERROR reading outline blue", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_enemyConfig.OT))
    {
        printErrorMessage("ERROR reading outline thickness", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_enemyConfig.VMIN))
    {
        printErrorMessage("ERROR reading vertices min", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_enemyConfig.VMAX))
    {
        printErrorMessage("ERROR reading vertices max", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_enemyConfig.L))
    {
        printErrorMessage("ERROR reading lifespan", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_enemyConfig.SI))
    {
        printErrorMessage("ERROR reading spawn interval", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    return true;
}

void Game::printErrorMessage(std::string msg, std::string file, std::string function,
                             int line) const
{
    std::cerr << msg
              << ", " << file
              << ", " << function
              << ", line: " << line
              << "\n";
}

bool Game::loadBulletConfig(std::istream &ins)
{
    // Bullet SR CR S FR FG OR OG OB OT V L

    if (!(ins >> m_bulletConfig.SR))
    {
        printErrorMessage("ERROR reading shape radius", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_bulletConfig.CR))
    {
        printErrorMessage("ERROR reading collision radius", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_bulletConfig.S))
    {
        printErrorMessage("ERROR reading speed", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_bulletConfig.FR))
    {
        printErrorMessage("ERROR reading fill red", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_bulletConfig.FG))
    {
        printErrorMessage("ERROR reading fill green", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_bulletConfig.FB))
    {
        printErrorMessage("ERROR reading fill blue", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_bulletConfig.OR))
    {
        printErrorMessage("ERROR reading outline red", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_bulletConfig.OG))
    {
        printErrorMessage("ERROR reading outline green", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_bulletConfig.OB))
    {
        printErrorMessage("ERROR reading outline blue", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_bulletConfig.OT))
    {
        printErrorMessage("ERROR reading outline thickness", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_bulletConfig.V))
    {
        printErrorMessage("ERROR reading vertices", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    if (!(ins >> m_bulletConfig.L))
    {
        printErrorMessage("ERROR reading lifespan", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    return true;
}

void Game::init(const std::string &path)
{
    loadConfigFromFile(path);

    // window parameters - full screen mode not working in a dual monitor setup
    // disabling for development and testing
    printErrorMessage("INFO:  ignoring full screen mode option", __FILE__, __FUNCTION__, __LINE__);
    m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "Geometry Wars");
    m_window.setFramerateLimit(m_windowConfig.FL);

    // text object
    m_text.setFont(m_font);
    m_text.setCharacterSize(m_fontConfig.S);
    m_text.setFillColor(sf::Color(m_fontConfig.R, m_fontConfig.G, m_fontConfig.B));

    spawnPlayer();

    m_gameState = GameState::INIT_SUCCESS;
}

void Game::end(void)
{
    m_window.close();
}

void Game::run()
{
    // TODO: add pause functionality in here
    //    some systems should function while paused (rendering)
    //    some systems should not function (movement / input)

    if (m_gameState != GameState::INIT_SUCCESS)
    {
        printErrorMessage("ERROR: Program terminating due to initialization error",
                          __FUNCTION__, __FILE__, __LINE__);
        this->end();
        return;
    }
    else
    {
        printErrorMessage("DEBUG: gameState is INIT_SUCCESS",
                          __FUNCTION__, __FILE__, __LINE__);
    }

    while (m_running)
    {

        m_entityManager.update();

        if (!m_paused)
        {
            //sEnemySpawner();
            sMovement();
            //sCollision();
            sLifeSpan();
        }

        sUserInput();
        sRender();

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
    // This returns a std::shared_ptr<Entity> and we use 'auto' to let
    // C++ determine data type
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

    /*** DEBUGGING ****/
    std::cerr << "\nPlayer Transform\n";
    printCTransform(std::cout, m_player->cTransform);
    std::cerr << "\n";
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

    // change 100,100 to posX, posY
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

// spawns a bullet from a given entity to a target location
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &mousePos)
{
    // TODO: Implement the spawning of a bullet which travels toward target
    //      - bullet speed is given as a scalar speed
    //      - you must set the velocity by using formula in notes
    auto bullet = m_entityManager.addEntity("bullet");

    // bullet should be spawned at the origin of the player entity
    Vec2 startPos = entity->cTransform->pos;

    // calculate per frame bullet velocity based on speed magnitude
    // specified in the configuration
    Vec2 targetPos = mousePos;

    // Difference vector D = Mouse Pos - Player Pos
    Vec2 diff = targetPos - startPos;

    // speed is the desired magnitude of the vector from bullet pos to target pos
    // need to calculate angle theta

    float theta = std::atan2(diff.y, diff.x);

    std::cout << "startPos,  x: " << startPos.x << ", y: " << startPos.y << "\n";
    std::cout << "targetPos, x: " << targetPos.x << ", y: " << targetPos.y << "\n";
    std::cout << "diff,      x: " << diff.x << ", y: " << diff.y << "\n";
    std::cout << "theta,   rad: " << theta << ", deg: "
              << theta * 180.0f / 3.1415f << "\n";

    // compute x, y components of bullet velocity
    Vec2 bulletVel(m_bulletConfig.S * cos(theta), m_bulletConfig.S * sin(theta));

    std::cout << "speed: " << m_bulletConfig.S << ", bullet vel x: " << bulletVel.x
              << ", y: " << bulletVel.y << "\n";

    // give bullet its properties
    bullet->cTransform = std::make_shared<CTransform>(startPos, bulletVel, 0);
    bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR,
                                              m_bulletConfig.V,
                                              sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
                                              sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB),
                                              m_bulletConfig.OT);

    bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);

    bullet->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
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
    if ((m_currentFrame - m_lastEnemySpawnTime) >= m_enemyConfig.SI)
    {
        spawnEnemy();
    }
}

void Game::sPlayerMovement()
{
    // set velocity to zero
    m_player->cTransform->velocity = {0, 0};

    // Update velocity based on user input
    if (m_player->cInput->up)
    {
        m_player->cTransform->velocity.y = -m_playerConfig.S;
    }

    if (m_player->cInput->down)
    {
        m_player->cTransform->velocity.y = +m_playerConfig.S;
    }

    if (m_player->cInput->left)
    {
        m_player->cTransform->velocity.x = -m_playerConfig.S;
    }

    if (m_player->cInput->right)
    {
        m_player->cTransform->velocity.x = +m_playerConfig.S;
    }

    // Update position
    m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
    m_player->cTransform->pos.y += m_player->cTransform->velocity.y;

    float radius = m_player->cShape->circle.getRadius();

    // constrain to window
    if ((m_player->cTransform->pos.x + radius) >= m_window.getSize().x)
    {
        m_player->cTransform->pos.x = m_window.getSize().x - radius;
    }
    else if ((m_player->cTransform->pos.x - radius) <= 0)
    {
        m_player->cTransform->pos.x = radius;
    }

    if ((m_player->cTransform->pos.y + radius) >= m_window.getSize().y)
    {
        m_player->cTransform->pos.y = m_window.getSize().y - radius;
    }
    else if ((m_player->cTransform->pos.y - radius) <= 0)
    {
        m_player->cTransform->pos.y = radius;
    }
}

void Game::sBulletMovement()
{
    for(auto& b : m_entityManager.getEntities("bullet"))
    {
        std::cout << "bullet id: " << b.get()->id() 
                << ", alive: " << b.get()->isActive() << "\n";
        // update position
        b->cTransform->pos.x += b->cTransform->velocity.x;
        b->cTransform->pos.y += b->cTransform->velocity.y;
        
        // update fill color alpha value
        if(b->cLifespan->remaining > 0)
        {
            std::cout << "lifespan remaining: " << b->cLifespan->remaining 
            << ", total: " << b->cLifespan->total  
            << ", alpha: " << b->cLifespan->remaining * 255 /b->cLifespan->total << "\n";
        }
        
        b->cShape->circle.setFillColor(sf::Color(m_bulletConfig.FR, m_bulletConfig.FG,
            m_bulletConfig.FB, b->cLifespan->remaining * 255 /b->cLifespan->total));
    }

}

void Game::sLifeSpan()
{
    for(auto& b : m_entityManager.getEntities("bullet"))
    {
        //printErrorMessage("There is a bullet, updating its lifespan\n", 
        //                __FILE__, __FUNCTION__, __LINE__);
        b->cLifespan->remaining -= 1;

        if(b->cLifespan->remaining <= 0)
        {
            //std::cerr << "bullet number " << b->id() << " has no lifespan\n";
            b->destroy();
        }
    }
}

void Game::sMovement()
{
    // TODO: implement all entity movement in this function
    sPlayerMovement();
    sBulletMovement();
}

void Game::sRender()
{
    // TODO: change the code below to draw all the entities
    //    sample drawing of the player Entity that we have created

    m_window.clear();

    for (auto e : m_entityManager.getEntities())
    {
        // set the position of the shape based on the entity's tranform->pos
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

        // set the rotation of the shape based on the entity's transform->angle
        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);

        // draw the entity's sf::CircleShape
        m_window.draw(e->cShape->circle);
    }

    m_window.display();
}

void Game::sUserInput()
{
    // TODO: handle user input here
    //    note that you should only be setting the player's input component variables here
    //    you should not implement the player's movement logic here
    //    the movement system will read the variables you set in this function

    sf::Event event;

    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_running = false;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                m_player->cInput->up = true;
                break;
            case sf::Keyboard::A:
                m_player->cInput->left = true;
                break;
            case sf::Keyboard::S:
                m_player->cInput->down = true;
                break;
            case sf::Keyboard::D:
                m_player->cInput->right = true;
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                m_player->cInput->up = false;
                break;
            case sf::Keyboard::A:
                m_player->cInput->left = false;
                break;
            case sf::Keyboard::S:
                m_player->cInput->down = false;
                break;
            case sf::Keyboard::D:
                m_player->cInput->right = false;
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Left Mouse button clicked at ("
                          << event.mouseButton.x << ", "
                          << event.mouseButton.y << ")\n";

                // call spawnBullet here
                spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                std::cout << "Right Mouse button clicked at ("
                          << event.mouseButton.x << ", "
                          << event.mouseButton.y << ")\n";

                // call spawnSpecialWeapon here
            }
        }
    }
}

/**** Debugging Print Functions *****/
std::ostream &Game::printWindowConfig(std::ostream &os) const
{
    os << "width:              " << m_windowConfig.W << "\n"
       << "height:             " << m_windowConfig.H << "\n"
       << "frame limit:        " << m_windowConfig.FL << "\n"
       << "full screen mode:   " << m_windowConfig.FS << "\n";
    return os;
}

std::ostream &Game::printFontConfig(std::ostream &os) const
{
    os << "font file:          " << m_fontConfig.F << "\n"
       << "font size:          " << m_fontConfig.S << "\n"
       << "font color red:     " << m_fontConfig.R << "\n"
       << "font color green:   " << m_fontConfig.G << "\n"
       << "font color blue:    " << m_fontConfig.B << "\n";
    return os;
}

std::ostream &Game::printPlayerConfig(std::ostream &os) const
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

std::ostream &Game::printEnemyConfig(std::ostream &os) const
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

std::ostream &Game::printBulletConfig(std::ostream &os) const
{
    os << "shape radius:             " << m_bulletConfig.SR << "\n"
       << "collision radius:         " << m_bulletConfig.CR << "\n"
       << "fill color red:           " << m_bulletConfig.FR << "\n"
       << "fill color green:         " << m_bulletConfig.FG << "\n"
       << "fill color blue:          " << m_bulletConfig.FB << "\n"
       << "outline color red:        " << m_bulletConfig.OR << "\n"
       << "outline color green:      " << m_bulletConfig.OG << "\n"
       << "outline color blue:       " << m_bulletConfig.OB << "\n"
       << "outline color thickness:  " << m_bulletConfig.OT << "\n"
       << "vertices:                 " << m_bulletConfig.V << "\n"
       << "lifespan:                 " << m_bulletConfig.L << "\n"
       << "speed:                    " << m_bulletConfig.S << "\n";
    return os;
}

std::ostream &Game::printCTransform(std::ostream &os, std::shared_ptr<CTransform> ct) const
{
    os << "pos x: " << ct->pos.x << "\n"
       << "pos y: " << ct->pos.y << "\n"
       << "vel x: " << ct->velocity.x << "\n"
       << "vel y: " << ct->velocity.y << "\n"
       << "angle: " << ct->angle << "\n"
       << "\n";
    return os;
}
