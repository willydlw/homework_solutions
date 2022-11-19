#include "Game.h"

#include <iostream>

Game::Game(const std::string & config)
{
   init(config);
}

void Game::init(const std::string & path)
{
   // TODO; read in config file here 
   //    use the premade PlayerConfig, EnemyConfig, BulletConfig variables 

   // set up default window parameters
   m_window.create(sf::VideoMode(1280, 720), "Geometry Wars");
   m_window.setFramerateLimit(60);

   spawnPlayer();
}

void Game::run()
{
   // TODO: add pause functionality in here 
   //    some systems should function while paused (rendering)
   //    some systems should not function (movement / input)

   while(m_running)
   {
      m_entities.update();

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
   m_lastEnemySpawTime = m_currentFrame;

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
   m_player->cShape->circlle.setRotation(m_player->cTransform->angle);

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