#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <cstdlib>

#include "../include/Vec2.hpp"

#ifndef NDEBUG // Only active in debug builds
#define MY_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << #condition \
                      << " in " << __func__ \
                      << " line " << __LINE__ \
                      << ": " << message << std::endl; \
            std::exit(-1); \
        } \
    } while (false)
#else
#define MY_ASSERT(condition, message) do {} while (false) // Empty in release builds
#endif

// FLOATING POINT TOLERANCE Constant
static constexpr float EQUALITY_EPISLON = 1e-7;

// 
bool float_equality(const Vec2f& v1, const Vec2f& v2)
{
    if( fabs(v1.x - v2.x) < EQUALITY_EPISLON && fabs(v1.y - v2.y) < EQUALITY_EPISLON)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void testMagnitude(const Vec2f& v, float expected)
{
    std::ostringstream oss;
    
    float result = v.magnitude();

    oss << "\n" << v << ", expected: " << expected << ", result: " << result << "\n";
    MY_ASSERT(result == expected, oss.str());
}

void testNormalization(const Vec2f& v, const Vec2f& expected)
{
    std::ostringstream oss;
    Vec2f result; 
    
    try
    {
        result = v.normalize();
    }
    catch (const std::runtime_error& e) 
    {
        std::cerr << "[RUNTIME ERROR] function: " << __PRETTY_FUNCTION__ << "\n"
                << e.what()
                << "\ttest vector: " << v << "\n"; 
    }

    oss << "\ntest vector: " << v << "\nexpected: " << expected << "\nresult: " << result << "\n";
    MY_ASSERT(float_equality(expected, result), oss.str());
}


void singleVectorTests()
{
    {   // positive values
        float x = 3.0f;
        float y = 4.0f;
        Vec2f v(x, y);
        float expectedMagnitude = sqrt(x*x + y*y);
        testMagnitude(v, expectedMagnitude);
    }

    {   // negative values
        float x = -3.0f;
        float y = -4.0f;
        Vec2f v(x, y);
        float expectedMagnitude = sqrt(x*x + y*y);
        testMagnitude(v, expectedMagnitude);
    }

    {   // zero values
        float x = 0.0f;
        float y = 0.0f;
        Vec2f v(x, y);

        float expectedMagnitude = sqrt(x*x + y*y);
        testMagnitude(v, expectedMagnitude);

        #if 0
        Vec2f expectedNormal = {0.0f, 0.0f};          // divide by zero should return zeros
        testNormalization(v, expectedNormal);         // handle division by zero
        #endif
    }

    {   // basis vector (1, 0)
        float x = 1.0f;
        float y = 0.0f;
        Vec2f v(x, y);

        float expectedMagnitude = sqrt(x*x + y*y);
        testMagnitude(v, expectedMagnitude);

        Vec2f expectedNormal = {x/expectedMagnitude, y/expectedMagnitude};
        testNormalization(v, expectedNormal);      
    }

    {   // basis vector (0, 1)
        float x = 0.0f;
        float y = 1.0f;
        Vec2f v(x, y);

        float expectedMagnitude = sqrt(x*x + y*y);
        testMagnitude(v, expectedMagnitude);

        Vec2f expectedNormal = {x/expectedMagnitude, y/expectedMagnitude};
        testNormalization(v, expectedNormal);      
    }

    {   // diagonal vector (1, 1)
        float x = 1.0f;
        float y = 1.0f;
        Vec2f v(x, y);

        float expectedMagnitude = sqrt(x*x + y*y);
        testMagnitude(v, expectedMagnitude);

        Vec2f expectedNormal = {x/expectedMagnitude, y/expectedMagnitude};
        testNormalization(v, expectedNormal);      
    }

    {   // diagonal vector (-1, -1)
        float x = -1.0f;
        float y = -1.0f;
        Vec2f v(x, y);

        float expectedMagnitude = sqrt(x*x + y*y);
        testMagnitude(v, expectedMagnitude);

        Vec2f expectedNormal = {x/expectedMagnitude, y/expectedMagnitude};
        testNormalization(v, expectedNormal);      
    }

    {   // single component (5, 0)
        float x = 5.0f;
        float y = 0.0f;
        Vec2f v(x, y);

        float expectedMagnitude = sqrt(x*x + y*y);
        testMagnitude(v, expectedMagnitude);

        Vec2f expectedNormal = {x/expectedMagnitude, y/expectedMagnitude};
        testNormalization(v, expectedNormal);      
    }

    {   // floating point with decimals (0.5, -2.5)
        float x = 5.0f;
        float y = 0.0f;
        Vec2f v(x, y);

        float expectedMagnitude = sqrt(x*x + y*y);
        testMagnitude(v, expectedMagnitude);

        Vec2f expectedNormal = {x/expectedMagnitude, y/expectedMagnitude};
        testNormalization(v, expectedNormal);      
    }

    {   // floating point with decimals (0.1, 1.0/3.0)
        float x = 0.1f;
        float y = 1.0f/3.0f;
        Vec2f v(x, y);

        float expectedMagnitude = sqrt(x*x + y*y);
        testMagnitude(v, expectedMagnitude);

        Vec2f expectedNormal = {x/expectedMagnitude, y/expectedMagnitude};
        testNormalization(v, expectedNormal);      
    }
    
}


void divideByZeroTest()
{
    // Divide by zero 
    {
        Vec2f v1(3.0f, 4.0f);
        Vec2f v2;
        float divisor = 0.0f;;

        try{
            v2 = v1 / divisor;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "[RUNTIME ERROR] function: " << __PRETTY_FUNCTION__ << "\n"
                << e.what()
                << "\n\ttest vector: " << v1 << ", divisor: " << divisor << "\n"; 
        }
    }
}

void runTests()
{
    //divideByZeroTest();

    singleVectorTests();
}


int main()
{
    runTests();
    return 0;
}