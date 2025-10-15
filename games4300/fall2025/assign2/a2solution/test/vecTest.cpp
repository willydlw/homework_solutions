#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <utility>          // std::pair
#include <cmath>
#include <cstdlib>

#include "../include/vec2.hpp"
#include "randomNumberGenerator.hpp"

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

static constexpr float MIN_RANDOM_FLOAT = -2048;
static constexpr float MAX_RANDOM_FLOAT = 2048;

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
    oss << "\ntest vector: " <<  tv 
        << "\nexpected:    " << expected 
        << "\nresult:      " << result << "\n";
    return oss.str();
}

std::string expectedResultMessage(const Vec2f& tv, const float& scalar, const Vec2f& expected, const Vec2f& result)
{
    std::ostringstream oss;
    oss << "\ntest vector: " <<  tv 
        << "\nscalar     : " << scalar
        << "\nexpected:    " << expected 
        << "\nresult:      " << result << "\n";
    return oss.str();
}


std::string expectedResultMessage(const Vec2f& tv1, const Vec2f& tv2, 
            const Vec2f& expected, const Vec2f& result)
{
    std::ostringstream oss;
    oss << "\ntest vector 1: " <<  tv1 
        << "\ntest vector 2: " <<  tv2
        << "\nexpected:      " << expected 
        << "\nresult:        " << result << "\n";
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


void testOperatorMultiply(const Vec2f& v, float scalar)
{
    Vec2f expected = {v.x * scalar, v.y * scalar};
    Vec2f result = v * scalar;
    std::string errmsg = expectedResultMessage(v, scalar, expected, result);
    MY_ASSERT(result == expected, errmsg);
}


void testOperatorDivide(const Vec2f& v, float scalar)
{
    Vec2f expected; 
    Vec2f result; 
    
    try
    {
        expected = {v.x/scalar, v.y/scalar};
        result = v / scalar;
        std::string errmsg = expectedResultMessage(v, scalar, expected, result);
        MY_ASSERT(result == expected, errmsg);
    }
    catch (const std::runtime_error& e) 
    {
        std::cerr << "[RUNTIME ERROR] function: " << __PRETTY_FUNCTION__ << "\n"
                << e.what()
                << "\ttest vector: " << v << ", scalar: << " <<  scalar << "\n"; 
        return;
    }
}



void testOperatorMinus(const Vec2f& v1, const Vec2f& v2)
{
    Vec2f expected = {v1.x - v2.x, v1.y - v2.y};
    Vec2f result = v1 - v2;
    std::string errmsg = expectedResultMessage(v1, v2, expected, result);
    MY_ASSERT(result == expected, errmsg);
}


void testOperatorMinusEquals(const Vec2f& v1, const Vec2f& v2)
{
    Vec2f result = v1;          // copy v1
    Vec2f expected = {v1.x - v2.x, v1.y - v2.y};

    result -= v2;
    std::string errmsg = expectedResultMessage(v1, v2, expected, result);
    MY_ASSERT(result == expected, errmsg);
}



void testOperatorPlus(const Vec2f& v1, const Vec2f& v2)
{
    Vec2f expected = {v1.x + v2.x, v1.y+v2.y};
    Vec2f result = v1 + v2;
    std::string errmsg = expectedResultMessage(v1, v2, expected, result);
    MY_ASSERT(result == expected, errmsg);

}

void testOperatorPlusEquals(const Vec2f& v1, const Vec2f& v2)
{
    Vec2f result = v1;          // copy v1
    Vec2f expected = {v1.x + v2.x, v1.y + v2.y};

    result += v2;
    std::string errmsg = expectedResultMessage(v1, v2, expected, result);
    MY_ASSERT(result == expected, errmsg);
}


void singleVectorTests()
{
    std::vector<Vec2f> testVecs = 
    {
        { 3.0f,  4.0f},     // positive values
        {-3.0f, -4.0f},     // negative values
        { 1.0f,  0.0f},     // basis vector
        { 0.0f,  1.0f},
        { 1.0f,  1.0f},     // diagonal vector 
        {-1.0f, -1.0f}, 
        { 5.0f,  0.0f},     // single component 
        { 0.0f,  5.0f},
        { 0.25f,  0.50f},    // decimal values
        { 0.10f, 1.0f/3.0f}
    };

    for(auto & tv : testVecs)
    {
        testMagnitude(tv);
        testNormalization(tv);
    }


    {   // Random Number tests 
        RandomNumberGenerator rg;
        for(int i = 0; i < 100; i++)
        {
            float x = rg.Generate(MIN_RANDOM_FLOAT, MAX_RANDOM_FLOAT);
            float y = rg.Generate(MIN_RANDOM_FLOAT, MAX_RANDOM_FLOAT);
            float scalar = rg.Generate(MIN_RANDOM_FLOAT, MAX_RANDOM_FLOAT);
            Vec2f v(x,y);

            testOperatorMultiply(v, scalar);
            testOperatorDivide(v, scalar);
            
            testMagnitude(v);
            testNormalization(v);
        }
    }
}


void twoVectorTests()
{
    {
        std::vector<std::pair<Vec2f, Vec2f>> testVecs = {
            {{1.0f, 1.0f}, {-1.0f, -1.0f}},
            {{2.0f, 3.0f}, {5.0, 1.0f}}
        };

        for(auto tv : testVecs)
        {
            Vec2f v1 = tv.first;
            Vec2f v2 = tv.second;
            testOperatorPlus(v1, v2);
            testOperatorPlusEquals(v1, v2);
            testOperatorMinus(v1, v2);
            testOperatorMinusEquals(v1, v2);
        } 
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


void testEdgeCases()
{

    {   // zero vector
        float x = 0.0f;
        float y = 0.0f;
        Vec2f v(x, y);

        testMagnitude(v);

        
        testNormalization(v);       // handle division by zero
        
        testOperatorMultiply(v, 0);
        testOperatorMultiply(v, 5);

        testOperatorDivide(v, 0);   // handle division by zero
        testOperatorDivide(v, 5);
    }
    
}

void runTests()
{
    //divideByZeroTest();
    singleVectorTests();
    twoVectorTests();
    testEdgeCases();
}


int main()
{
    runTests();
    return 0;
}