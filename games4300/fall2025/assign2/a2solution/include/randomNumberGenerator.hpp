#pragma once 
#include <random>

class RandomNumberGenerator{

private:

    std::random_device m_randomDevice{};
    std::mt19937 m_engine{m_randomDevice()};    // seed 

public:

    RandomNumberGenerator() = default;
    
    float generate(float low, float high){
        return std::uniform_real_distribution<float>{low,high}(m_engine);
    }

    int generate(int low, int high){
        return std::uniform_int_distribution<int>{low, high}(m_engine);
    }

    uint8_t generate(uint8_t low, uint8_t high){
        return std::uniform_int_distribution<uint8_t>{low, high}(m_engine);
    }

};