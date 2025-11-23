#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H

#include "Entity.hpp"
#include "GameEngine.h"
#include "Scene.h"
#include "Vec2.hpp"

#include <SFML/Graphics/Text.hpp>

#include <memory>


class Scene_Play : public Scene 
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
    //sf::Text                m_gridText;

    void init(const std::string& levelPath);
    Vec2f gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity>);
    void loadLevel(const std::string& filename);

   
    void onEnd() override;
    void spawnPlayer();
    void spawnBullet(std::shared_ptr<Entity> entity);

    // Systems 
    void sMovement();
    void sLifespan();
    void sCollision();
    void sAnimation();
    void sGui();
    
    void sRender() override;
    void sDoAction(const Action& action) override;

public:

    Scene_Play(GameEngine* gameEngine, const std::string &levelPath);
    void update() override;
};

#endif // SCENE_PLAY_H