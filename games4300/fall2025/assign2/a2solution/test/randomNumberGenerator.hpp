#pragma once 
#include <random>

class RandomNumberGenerator{

private:

    std::random_device m_randomDevice{};
    std::mt19937 m_engine{m_randomDevice()};    // seed 

public:
    float Generate(float low, float high){
        return std::uniform_real_distribution<float>{low,high}(m_engine);
    }

};