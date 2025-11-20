class Scene_Play : Scene 
{
    string levelPath;
    Entity* player;
    PlayerConfig playerConfig;

    void init();
    void update();

    // Systems 
    void sAnimation();
    void sMovement();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    void sDoAction(action);
    void sDebug();
};