#ifndef A3_ANIMATION_H
#define A3_ANIMATION_H

#include <iostream>
#include <string>

#include <cmath>        // floor

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Vec2.hpp"

class Animation 
{
    public:

    Animation() = default;

    Animation(const std::string& name, const sf::Texture &texture) 
        : Animation(name, texture, 1, 0)
    {
        std::cerr << "Animation default constructor\n";
    }

    Animation(const std::string& name, const sf::Texture& texture, 
                size_t frameCount, size_t speed)
        : m_sprite(texture) 
        , m_frameCount(frameCount)
        , m_currentFrame(0)
        , m_speed(speed)
        , m_name(name)
    {

        FIX THIS
        m_size = Vec2f{(float)texture.getSize().x, (float)texture.getSize().y};
        m_sprite.setOrigin({m_size.x / 2.0f, m_size.y / 2.0f});
        m_sprite.setTextureRect(sf::IntRect({static_cast<int>(std::floor(static_cast<float<(m_currentFrame) * m_size.x)), 0}, {m_size.x, m_size.y}));
        std::cerr << "Animation constructor, data member values\n";
        std::cerr << *this << "\n";
    }

    // updates the animation to show the next frame, depending on its speed
    // animation loops when it reaches the end
    void update()
    {
        std::cerr << "TODO, function: " << __PRETTY_FUNCTION__ << "\n";

        // add the speed variable to the current frame?
        m_currentFrame++;

        // TODO: 1) calculate the correct frame of animation to play based on currentFrame
        //       2) set the texture rectangle properly (see constructor for sample)
        std::cerr << "1. Calculate the correct frame of animation to play based on currentFrame\n";
        std::cerr << "2. Set the texture rectangle properly\n";
    }

    bool hasEnded() const 
    {
        // TODO: detect when animation has ended (last frame was played) and return true
        std::cerr << "TODO, function: " << __func__ << " detect when animation has ended\n";
        return false;
    }

    const Vec2f& getSize() const
    {
        return m_size;
    }

    const std::string& getName() const 
    { 
        return m_name;
    }

    sf::Sprite& getSprite()
    {
        return m_sprite;
    }

    friend std::ostream& operator << (std::ostream& os, const Animation& obj)
    {
        os  << "m_name:          " << obj.m_name << "\n"
            << "m_frameCount:    " << obj.m_frameCount << "\n"
            << "m_currentFrame:  " << obj.m_currentFrame << "\n"
            << "m_speed:         " << obj.m_speed << "\n";
        return os;  
    }

    private:
    sf::Sprite  m_sprite;
    std::size_t m_frameCount = 1;       // total number of frames of animation 
    std::size_t m_currentFrame = 0;     // the current frame of animation being played 
    std::size_t m_speed = 0;            // speed to play this animation
    std::string m_name = "none";        // name of animation
    Vec2f       m_size = {1.0f, 1.0f};  // size of the animation frame
};

#endif // ANIMATION_H