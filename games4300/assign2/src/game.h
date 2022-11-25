#include <string>
#include <SFML/Graphics.hpp>
#include "entityManager.h"

/* W  -  width 
*  H  -  height 
*  FL -  frame limit 
*  FS -  full screen mode (1 - yes, 0 - no)
*/
struct WindowConfig { int W, H, FL, FS; };



/* F  -  font file 
*  S  -  font size 
*  R  -  font color red 
*  G  -  font color green 
*  B  -  font color blue  
*/
struct FontConfig { std::string F; int S, R, G, B; };





/* SR -  shape radius 
*  CR -  collision radius 
*  FR -  fill red 
*  FG -  fill green 
*  FB -  fill blue 
*  OR -  outline red 
*  OG -  outline green
*  OB -  outline blue 
*  OT -  outline thickness 
*  V  -  shape vertices  
*  S  -  speed magnitude (pixels per frame)
*  VMIN  -  minimum vertices 
*  VMAX  -  maximum vertices
*  L     -  lifespan 
*  SI    -  spawn interval 
*  SMIN  -  minimum speed 
*  SMAX  -  maximum speed 
*/
struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S;};
struct EnemyConfig  {int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX;};
struct BulletConfig {int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S;};





class Game
{
   static const std::string DEFAULT_FONT_FILE; 
   static const WindowConfig WINDOW_CONFIG_DEFAULT;
   static const FontConfig FONT_CONFIG_DEFAULT;
   static const PlayerConfig PLAYER_CONFIG_DEFAULT;
   static const EnemyConfig ENEMY_CONFIG_DEFAULT;
   static const BulletConfig BULLET_CONFIG_DEFAULT;

   enum class GameState {INIT_SUCCESS, INIT_FAILURE, GAME_OVER};
   enum class ConfigState{WINDOW_DEFAULT, FONT_DEFAULT, PLAYER_DEFAULT, 
                           ENEMY_DEFAULT, BULLET_DEFAULT, HANDLE_ERROR};

   
   sf::RenderWindow     m_window;            // window we will draw to 
   EntityManager        m_entityManager;     // manages all entities
   sf::Font             m_font;              // font used to draw 
   sf::Text             m_text;              // the score text to be drawn to the screen 
   WindowConfig         m_windowConfig;
   FontConfig           m_fontConfig;
   PlayerConfig         m_playerConfig;
   EnemyConfig          m_enemyConfig;
   BulletConfig         m_bulletConfig;
   GameState            m_gameState;
   int                  m_score = 0;
   int                  m_currentFrame = 0;
   int                  m_lastEnemySpawnTime = 0;
   bool                 m_paused = false;       // whether we update game logic
   bool                 m_running = true;       // whether the game is running 

   std::shared_ptr<Entity> m_player;

   void init(const std::string & config);    // initialize the GameState with a config file path
   void setPaused(bool paused);              // pause the game 

   void sMovement();                         // System: Entity position / movement update 
   void sUserInput();                        // System: User input 
   void sLifeSpan();                         // System: Lifespan 
   void sRender();                           // System: Render / drawing 
   void sEnemySpawner();                     // System: Spawns enemies 
   void sCollision();                        // System: Collisions 

   void spawnPlayer();
   void spawnEnemy();
   void spawnSmallEnemies(std::shared_ptr<Entity> entity);
   void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousePos);
   void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

   void loadConfigFromFile(const std::string &path);
   void loadDefaultConfig(ConfigState state);
   std::istream& loadWindowConfig(std::istream & ins);
   std::istream& loadFontConfig(std::istream & ins);
   std::istream& loadPlayerConfig(std::istream & ins);
   std::istream& loadEnemyConfig(std::istream & ins);
   std::istream& loadBulletConfig(std::istream & ins);

   std::ostream& printWindowConfig(std::ostream& os)const;
   std::ostream& printFontConfig(std::ostream& os)const;
   std::ostream& printPlayerConfig(std::ostream& os) const;
   std::ostream& printEnemyConfig(std::ostream& os) const;
   std::ostream& printBulletConfig(std::ostream& os) const;



   public:

      Game(const std::string & config);      // constructor, takes in game config 
      void run();
};

