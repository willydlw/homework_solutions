#pragma once 

#include <string>

class Animation 
{
    public:

    Animation() = default;

    Animation(const std::string& name, const std::string& textureName) 
        : Animation(name, textureName, 1, 0)
    {

    }

    Animation(const std::string& name, const std::string& textureName, size_t frameCount, speed)
        : m_name(name)
        , m_frameCount(frameCount)
        , m_currentFrame(0)
        , m_speed(speed)
        , m_textureName(textureName)
    
    {

    }

    // updates the animation to show the next frame, depending on its
    // animation loops when it reaches the end
    void update()
    {
        m_currentFrame++;

        // TODO: 1) calculate the correct frame of animation to play based on currentFrame
        //       2) set the texture rectangle properly (see constructor for sample)
    }

    bool hasEnded() const 
    {
        // TODO: detect when animation has ended (last frame was played) and return true
        return false;
    }

    const std::string& getName() const 
    { 
        return m_name;
    }

    const sf::IntRect& getRect() const 
    {
        return m_textureRect;
    }

    private:
    std::size_t m_frameCount = 1;       // total number of frames of animation 
    std::size_t m_currentFrame = 0;     // the current frame of animation being played 
    std::size_t m_speed = 0;            // speed to play this animation
    std::string m_name = "none";    // name of animation
    std::string m_textureName = "none"; // name of the texture to get the frames from
    sf::IntRect m_textureRect;      // sub-rectangle to draw



    // from lecture notes (may not be needed)
    sf::Sprite sprite;
    Vec2 size;
   
    Vec2& getSize();
    sf::Sprite& getSprite();
};

