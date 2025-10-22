#pragma once 

#include <sstream>

#include "../../a2solution/include/vec2.hpp"
#include "myAssert.h"
#include "randomNumberGenerator.hpp"

template <typename T>
std::string expectedResultMessage(const Vec2<T>& tv, T expected, T result)
{
    std::ostringstream oss;
    oss << "\ntest vector: " <<  tv << ", expected: " << expected << ", result: " << result << "\n";
    return oss.str();
}


template <typename T>
std::string expectedResultMessage(const Vec2<T>& tv, const Vec2<T>& expected, const Vec2<T>& result)
{
    std::ostringstream oss;
    oss << "\ntest vector: " <<  tv 
        << "\nexpected:    " << expected 
        << "\nresult:      " << result << "\n";
    return oss.str();
}

template <typename T>
std::string expectedResultMessage(const Vec2<T>& tv, const T& scalar, const Vec2<T>& expected, const Vec2<T>& result)
{
    std::ostringstream oss;
    oss << "\ntest vector: " <<  tv 
        << "\nscalar     : " << scalar
        << "\nexpected:    " << expected 
        << "\nresult:      " << result << "\n";
    return oss.str();
}

template <typename T>
std::string expectedResultMessage(const Vec2<T>& v1, const Vec2<T>& v2, const T& expected, const T& result)
{
    std::ostringstream oss;
    oss << "\nv1:          " <<  v1 
        << "\nv2:          " <<  v2
        << "\nexpected:    " << expected 
        << "\nresult:      " << result << "\n";
    return oss.str();
}

template <typename T>
std::string expectedResultMessage(const Vec2<T>& tv1, const Vec2<T>& tv2, 
            const Vec2<T>& expected, const Vec2<T>& result)
{
    std::ostringstream oss;
    oss << "\ntest vector 1: " <<  tv1 
        << "\ntest vector 2: " <<  tv2
        << "\nexpected:      " << expected 
        << "\nresult:        " << result << "\n";
    return oss.str();
}


template <typename T>
void testMagnitude(const Vec2<T>& v)
{
    float expected = sqrt(v.x * v.x + v.y * v.y);
    float result = v.magnitude();

    std::string errmsg = expectedResultMessage(v, expected, result);
    MY_ASSERT(result == expected, errmsg);
}


template <typename T>
void testNormalization(const Vec2<T>& v)
{
    /* Best Practice?? 
            Using the Vec2<T> magnitude member function magnitude. 
            Because the magnitude function is also subject to 
            test, it is used here assuming other tests will 
            detect any errors in that function.
    */
    float mag = v.magnitude();
    
    Vec2<T> expected; 
    Vec2<T> result; 
    
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

template <typename T>
void testDotProduct(const Vec2<T>& v1, const Vec2<T>& v2)
{
    T result = v1.dotProduct(v2);
    T expected = (v1.x * v2.x + v1.y * v2.y);
    std::string errmsg = expectedResultMessage(v1, v2, expected, result);
    MY_ASSERT(expected == result, errmsg); 
}

template <typename T>
float testDistance(const Vec2<T>& v1, const Vec2<T>& v2)
{
    // TODO
}

template <typename T>
float testAngle(const Vec2<T>& v1, const Vec2<T>& v2)
{
    // TODO
}


template <typename T>
void testOperatorMultiply(const Vec2<T>& v, float scalar)
{
    Vec2<T> expected = {v.x * scalar, v.y * scalar};
    Vec2<T> result = v * scalar;
    std::string errmsg = expectedResultMessage(v, scalar, expected, result);
    MY_ASSERT(result == expected, errmsg);
}


template <typename T>
void testOperatorDivide(const Vec2<T>& v, float scalar)
{
    Vec2<T> expected; 
    Vec2<T> result; 
    
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


template <typename T>
void testOperatorMinus(const Vec2<T>& v1, const Vec2<T>& v2)
{
    Vec2<T> expected = {v1.x - v2.x, v1.y - v2.y};
    Vec2<T> result = v1 - v2;
    std::string errmsg = expectedResultMessage(v1, v2, expected, result);
    MY_ASSERT(result == expected, errmsg);
}

template <typename T>
void testOperatorMinusEquals(const Vec2<T>& v1, const Vec2<T>& v2)
{
    Vec2<T> result = v1;          // copy v1
    Vec2<T> expected = {v1.x - v2.x, v1.y - v2.y};

    result -= v2;
    std::string errmsg = expectedResultMessage(v1, v2, expected, result);
    MY_ASSERT(result == expected, errmsg);
}


template <typename T>
void testOperatorPlus(const Vec2<T>& v1, const Vec2<T>& v2)
{
    Vec2<T> expected = {v1.x + v2.x, v1.y+v2.y};
    Vec2<T> result = v1 + v2;
    std::string errmsg = expectedResultMessage(v1, v2, expected, result);
    MY_ASSERT(result == expected, errmsg);

}

template <typename T>
void testOperatorPlusEquals(const Vec2<T>& v1, const Vec2<T>& v2)
{
    Vec2<T> result = v1;          // copy v1
    Vec2<T> expected = {v1.x + v2.x, v1.y + v2.y};

    result += v2;
    std::string errmsg = expectedResultMessage(v1, v2, expected, result);
    MY_ASSERT(result == expected, errmsg);
}


template <typename T>
void testAddition(const Vec2<T>& v1, const Vec2<T>& v2)
{
    testOperatorPlus(v1, v2);
    testOperatorPlusEquals(v1, v2);
}

template <typename T>
void testSubtraction(const Vec2<T>& v1, const Vec2<T>& v2)
{
    testOperatorMinus(v1, v2);
    testOperatorMinusEquals(v1, v2);
}


template <typename T>
std::vector<Vec2<T>> generateTestVectors(int n, T low, T high)
{
    RandomNumberGenerator rg;
    std::vector<Vec2<T>> arr;    
    for(int i = 0; i < n; i++)
    {
        arr.push_back({rg.generate(low, high), rg.generate(low, high)});
    }

    return arr;
}



template <typename T>
void testAddSubtractEdgeCases(const std::vector<Vec2<T>>& v, int n)
{
    for(int i = 0; i < n; i++)
    {
        Vec2<T> v1 = v[i];
        Vec2<T> v2 = {0, 0};
        Vec2<T> v3 = {-v1.x, -v1.y};
        

        // vector with zero vector
        testAddition(v1, v2);
        testSubtraction(v1, v2);

        // vector and its negative 
        testAddition(v1, -v1);
        testSubtraction(v1, -v1);

        // component with opposite directions
        testAddition(v1, v3);
        testSubtraction(v1, v3);
    }
}


template <typename T>
void testAllOps(const Vec2<T>& v1, const Vec2<T>& v2)
{
    testAddition(v1, v2);
    testSubtraction(v1, v2);
    testOperatorMultiply(v1, v2);
    testOperatorDivide(v1, v2);
    testDotProduct(v1, v2);
}