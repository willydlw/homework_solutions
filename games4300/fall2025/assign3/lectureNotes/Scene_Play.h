#include "Scene.h"
#include "EntityManager.hpp"

#include <memory>


class Scene_Play : Scene 
{
    struct PlayerConfig 
    {
        float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
        std::string WEAPON;
    };

    protected:
    std::shared_ptr<Entity> m_player;
    std::string             m_levelPath;
    PlayerConfig            m_playerConfig;
    bool                    m_drawTextures = true;
    bool                    m_drawCollision = false;
    bool                    m_drawGrid = false;
    const Vec2f             m_gridSize = {64, 64};

    void init(const std::string& levelPath);
    void loadLevel(const std::string& filename);

    void update();
    void onEnd();
    void spawnPlayer();
    void spawnBullet(std::shared_ptr<Entity> entity);

    // Systems 
    void sAnimation();
    void sMovement();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    void sDoAction(const Action& action);
    void sDebug();
};