#ifndef A3_ANIMATION_H
#define A3_ANIMATION_H

#include <iostream>
#include <string>

#include <SFML/Graphics/Rect.hpp>

class Animation 
{
    public:

    Animation() = default;

    Animation(const std::string& name, const std::string& textureName) 
        : Animation(name, textureName, 1, 0)
    {
        std::cerr << "Animation default constructor\n";
    }

    Animation(const std::string& name, const std::string& textureName, 
                size_t frameCount, size_t speed)
        : m_name(name)
        , m_textureName(textureName)
        , m_frameCount(frameCount)
        , m_currentFrame(0)
        , m_speed(speed)
    
    {
        std::cerr << "Animation constructor, data member values\n";
        std::cerr << *this << "\n";
    }

    // updates the animation to show the next frame, depending on its
    // animation loops when it reaches the end
    void update()
    {
        std::cerr << "TODO, function: " << __PRETTY_FUNCTION__ << "\n";
        m_currentFrame++;

        // TODO: 1) calculate the correct frame of animation to play based on currentFrame
        //       2) set the texture rectangle properly (see constructor for sample)
        std::cerr << "1. Calculate the correct fram of animation to play based on currentFrame\n";
        std::cerr << "2. Set the texture rectangle properly\n";
    }

    bool hasEnded() const 
    {
        // TODO: detect when animation has ended (last frame was played) and return true
        std::cerr << "TODO, function: " << __func__ << " detect when animation has ended\n";
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

    friend std::ostream& operator << (std::ostream& os, const Animation& obj)
    {
        os  << "m_name:          " << obj.m_name << "\n"
            << "m_textureName:   " << obj.m_textureName << "\n"
            << "m_frameCount:    " << obj.m_frameCount << "\n"
            << "m_currentFrame:  " << obj.m_currentFrame << "\n"
            << "m_speed:         " << obj.m_speed << "\n"
            << "m_textureRect position x:  " << obj.m_textureRect.position.x 
            << ", y: " << obj.m_textureRect.position.y
            << ", size x: " << obj.m_textureRect.size.x 
            << ", size y: " << obj.m_textureRect.size.y << "\n";
        return os;  
    }

    private:
    std::string m_name = "none";        // name of animation
    std::string m_textureName = "none"; // name of the texture to get the frames from
    std::size_t m_frameCount = 1;       // total number of frames of animation 
    std::size_t m_currentFrame = 0;     // the current frame of animation being played 
    std::size_t m_speed = 0;            // speed to play this animation
    sf::IntRect m_textureRect;          // sub-rectangle to draw
};

#endif // ANIMATION_H