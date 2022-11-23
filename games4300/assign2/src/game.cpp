#include "game.h"

#include <fstream>
#include <iostream>

Game::Game(const std::string & config)
{
   init(config);
}

/* Assumptions:
      no file stream read errors

   File Stream exceptions are not handled.
*/
void Game::init(const std::string & path)
{
   std::ifstream infile(path);  

   if(!infile)
   {
      std::cerr << "ERROR: file open failure, path: " << path << "\n";
      m_gameState = GameState::INIT_FAILURE;
      return;
   } 

   infile   >> m_windowConfig.W 
            >> m_windowConfig.H 
            >> m_windowConfig.FL 
            >> m_windowConfig.FS;

   infile   >> m_fontConfig.F
            >> m_fontConfig.S 
            >> m_fontConfig.R 
            >> m_fontConfig.G 
            >> m_fontConfig.B;

   infile   >> m_playerConfig.SR    // shape radius
            >> m_playerConfig.CR    // collision radius 
            >> m_playerConfig.FR    // fill color
            >> m_playerConfig.FG 
            >> m_playerConfig.FB 
            >> m_playerConfig.OR    // outline color
            >> m_playerConfig.OG 
            >> m_playerConfig.OB
            >> m_playerConfig.OT    // outline thickness
            >> m_playerConfig.V     // shape vertices
            >> m_playerConfig.S;    // speed (pixels per frame)

   infile   >> m_enemyConfig.SR
            >> m_enemyConfig.CR
            >> m_enemyConfig.OR
            >> m_enemyConfig.OG 
            >> m_enemyConfig.OB
            >> m_enemyConfig.OT
            >> m_enemyConfig.VMIN
            >> m_enemyConfig.VMAX
            >> m_enemyConfig.L 
            >> m_enemyConfig.SI     
            >> m_enemyConfig.SMIN 
            >> m_enemyConfig.SMAX;

   infile   >> m_bulletConfig.SR 
            >> m_bulletConfig.CR
            >> m_bulletConfig.FR 
            >> m_bulletConfig.FG
            >> m_bulletConfig.FB 
            >> m_bulletConfig.OR 
            >> m_bulletConfig.OG 
            >> m_bulletConfig.OB 
            >> m_bulletConfig.OT 
            >> m_bulletConfig.V 
            >> m_bulletConfig.L 
            >> m_bulletConfig.S;
   
   infile.close();

   // set up default window parameters
   std::cerr << __func__ << ", WARNING: ignoring full screen mode option\n";
   m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "Geometry Wars");
   m_window.setFramerateLimit(m_windowConfig.FL);

   // set up font object
   if(!m_font.loadFromFile(m_fontConfig.F))
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

   if(m_gameState != GameState::INIT_SUCCESS)
   {
      std::cerr << "Program terminating due to initialization error\n";
      return;
   }

   while(m_running)
   {
      m_entityManager.update();

      sEnemySpawner();
      sMovement();
      sCollision();
      sUserInput();
      sRender();

      // increment the current frame 
      // may need to be moved when pause implemented 
      m_currentFrame++;
   }
}

GameState Game::queryState()const
{
   return m_gameState;
}

void Game::setPaused(bool paused)
{
   // TODO
}


// respawn the playe in the middle of the screen 
void Game::spawnPlayer()
{
   // TODO: finish adding all properties of the player with the correct values from the config 

   // We create every entity by calling EntityManager.addEntity(tag)
   // This returns a std::shared_ptr<Entity> so we use 'auto' to save typing 
   auto entity = m_entities.addEntity("player");

   // give this entity a transform so it spawns at 200,200 with velocity 1,1 and angle 0

   // find window center
   float middleX = m_window.getSize().x / 2.0f;
   float middleY = m_window.getSize().y / 2.0f;

   entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);

   // the entity's shape will have radius 32, 8 sides, dark grey fill, red outline of thickness 4
   entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10,10,10), 4.0f);

   // add an input component to the player so that we can use inputs
   entity->cInput = std::make_shared<CInput>();

   // since we want this entity to be our player, set our Game's player variable to be this Entity
   // This goes slightly against the EntityManager paradigm, but we use the player so much it's worth it 
   m_player = entity;
}

// spawn an enemy at a random position
void Game::spawnEnemy()
{
   // TODO: make sure the enemy is spawned properly with the m_enemyConfig variables
   //       the enemy must be spawned completely within the bounds of the window

   // optional: ensure enemy is not spawned in same location as player

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

   sf::Event event;

}


std::ostream& Game::printWindowConfig(std::ostream& os)const
{
   os << "width:              " << m_windowConfig.W << "\n"
      << "height:             " << m_windowConfig.H << "\n"
      << "frame limit:        " << m_windowConfig.FL << "\n"
      << "full screen mode:   " << m_windowConfig.FS << "\n";
   return os;
}

std::ostream& Game::printFontConfig(std::ostream& os)const
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