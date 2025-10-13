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

std::string expectedResultMessage(const Vec2f& tv, float expected, float result)
{
    std::ostringstream oss;
    oss << "\ntest vector: " <<  tv << ", expected: " << expected << ", result: " << result << "\n";
    return oss.str();
}

std::string expectedResultMessage(const Vec2f& tv, const Vec2f& expected, const Vec2f& result)
{
    std::ostringstream oss;
    oss << "\ntest vector: " <<  tv << "\nexpected: " << expected << "\nresult: " << result << "\n";
    return oss.str();
}




void testMagnitude(const Vec2f& v)
{
    float expected = sqrt(v.x * v.x + v.y * v.y);
    float result = v.magnitude();

    std::string errmsg = expectedResultMessage(v, expected, result);
    MY_ASSERT(result == expected, errmsg);
}

void testNormalization(const Vec2f& v)
{
    /* Best Practice?? 
            Using the Vec2f magnitude member function magnitude. 
            Because the magnitude function is also subject to 
            test, it is used here assuming other tests will 
            detect any errors in that function.
    */
    float mag = v.magnitude();
    Vec2f expected; 
   
    Vec2f result; 
    
    try
    {
        expected = {v.x/mag, v.y/mag};
        result = v.normalize();
    }
    catch (const std::runtime_error& e) 
    {
        std::cerr << "[RUNTIME ERROR] function: " << __PRETTY_FUNCTION__ << "\n"
                << e.what()
                << "\ttest vector: " << v << ", magnitude: << " << mag << "\n"; 
        return;
    }

    std::string errmsg = expectedResultMessage(v, expected, result);
    MY_ASSERT(float_equality(expected, result), errmsg);
}


void singleVectorTests()
{
    {   // positive values
        float x = 3.0f;
        float y = 4.0f;
        Vec2f v(x, y);
        testMagnitude(v);
    }

    {   // negative values
        float x = -3.0f;
        float y = -4.0f;
        Vec2f v(x, y);
        testMagnitude(v);
    }

    {   // zero values
        float x = 0.0f;
        float y = 0.0f;
        Vec2f v(x, y);
        testMagnitude(v);
        std::cerr << "\n*** Expecting Division Test Normalization to throw Division by Zero Error ***\n";
        testNormalization(v);   // handle division by zero

        std::cerr << "*** End of Division by Zero Test ***\n\n";
    }

    {   // basis vector (1, 0)
        float x = 1.0f;
        float y = 0.0f;
        Vec2f v(x, y);

        testMagnitude(v);
        testNormalization(v);      
    }

    {   // basis vector (0, 1)
        float x = 0.0f;
        float y = 1.0f;
        Vec2f v(x, y);

        testMagnitude(v);
        testNormalization(v);      
    }

    {   // diagonal vector (1, 1)
        float x = 1.0f;
        float y = 1.0f;
        Vec2f v(x, y);

        testMagnitude(v);
        testNormalization(v);      
    }

    {   // diagonal vector (-1, -1)
        float x = -1.0f;
        float y = -1.0f;
        Vec2f v(x, y);

        testMagnitude(v);
        testNormalization(v);      
    }

    {   // single component (5, 0)
        float x = 5.0f;
        float y = 0.0f;
        Vec2f v(x, y);

        testMagnitude(v);
        testNormalization(v);      
    }

    {   // floating point with decimals (0.5, -2.5)
        float x = 5.0f;
        float y = 0.0f;
        Vec2f v(x, y);

        testMagnitude(v);
        testNormalization(v);      
    }

    {   // floating point with decimals (0.1, 1.0/3.0)
        float x = 0.1f;
        float y = 1.0f/3.0f;
        Vec2f v(x, y);

        testMagnitude(v);
        testNormalization(v);      
    }
    
}

#if 0
void testOperatorPlus(const Vec2f& v1 const Vec2f& v2)
{
    Vec2f expected = {v1.x + v2.x, v1.y+v2.y};
    Vec2f result = v1 + v2;

}

void twoVectorTests()
{
    {
        Vec2f v1 = {2.0f, 3.0f};
        Vec2f v2 = {5.0f, 1.0f};
        
        Vec2f vadd = {v1.x + v2.x, v1.y+v2.y}
    }
}

#endif 


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