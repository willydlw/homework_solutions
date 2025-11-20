class Animation 
{
    sf::Sprite sprite;
    int frameCount;
    int currentFrame;
    int speed;
    Vec2 size;
    std::string name;

    void update();
    void (bool?) hasEnded();
    std::string& getName();
    Vec2& getSize();
    sf::Sprite& getSprite();
};