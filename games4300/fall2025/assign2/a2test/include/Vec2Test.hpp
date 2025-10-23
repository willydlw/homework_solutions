#pragma once 

#include <sstream>

#include "../../a2solution/include/vec2.hpp"
#include "myAssert.h"
#include "randomNumberGenerator.hpp"

template <typename T>
class Vec2Test
{
    public:

    // FLOATING POINT TOLERANCE Constant
    static constexpr float EQUALITY_EPISLON = 1e-5;

    static constexpr int DEFAULT_NUM_RANDOM_TESTS = 5;

    // Random value test limits
    static constexpr int RAND_INT_MIN = -500;
    static constexpr int RAND_INT_MAX =  500;
    static constexpr float RAND_FLOAT_MIN = -500.0f;
    static constexpr float RAND_FLOAT_MAX =  500.0f;

    // Constructor
    Vec2Test() = default;

   
    void runAllTests()
    {
        singleVectorRandomValueTests(DEFAULT_NUM_RANDOM_TESTS, RAND_INT_MIN, RAND_INT_MAX);
        twoVectorRandomValueTests(DEFAULT_NUM_RANDOM_TESTS, RAND_INT_MIN, RAND_INT_MAX);

        singleVectorRandomValueTests(DEFAULT_NUM_RANDOM_TESTS, RAND_FLOAT_MIN, RAND_FLOAT_MAX);
        twoVectorRandomValueTests(DEFAULT_NUM_RANDOM_TESTS, RAND_FLOAT_MIN, RAND_FLOAT_MAX);
        // TODO Edge cases
    }


    private:

    RandomNumberGenerator rg;

    void singleVectorRandomValueTests(int numTests, const T& low, const T& high)
    {
        for(int i = 0; i < numTests; i++)
        {
            Vec2<T> v = {
                rg.generate(low, high), 
                rg.generate(low, high) 
            };

            int scalar = rg.generate(low, high);

            magnitudeTest(v);
            normalizeTest(v);
            operatorMultiplyTest(v, scalar);
            operatorMultiplyEqualsTest(v, scalar);
            operatorDivideTest(v, scalar);
            operatorDivideEqualsTest(v, scalar);
            unaryMinusTest(v);
        }
    }

    void twoVectorRandomValueTests(int numTests, const T& low, const T& high)
    {
        for(int i = 0; i < numTests; i++)
        {
            Vec2<T> v1 = {
                rg.generate(low, high), 
                rg.generate(low, high) 
            };


            Vec2<T> v2 = {
                rg.generate(low, high), 
                rg.generate(low, high) 
            };

            operatorPlusTest(v1, v2);
            operatorPlusEqualsTest(v1, v2);
            operatorMinusTest(v1, v2);
            operatorMinusEqualsTest(v1, v2);
            distanceTest(v1, v2);
            dotProductTest(v1, v2);
            angleTest(v1, v2);
        }

    }



    // Error Message Builder Functions
    std::string expectedResultMessage(const Vec2<T>& tv, const T& expected, const T& result)
    {
        std::ostringstream oss;
        oss << "\ntest vector: " <<  tv << ", expected: " << expected << ", result: " << result << "\n";
        return oss.str();
    }


    std::string expectedResultMessage(const Vec2<T>& tv, const Vec2<T>& expected, const Vec2<T>& result)
    {
        std::ostringstream oss;
        oss << "\ntest vector: " <<  tv 
            << "\nexpected:    " << expected 
            << "\nresult:      " << result << "\n";
        return oss.str();
    }

    std::string expectedResultMessage(const Vec2<T>& tv, const T& scalar, const Vec2<T>& expected, const Vec2<T>& result)
    {
        std::ostringstream oss;
        oss << "\ntest vector: " <<  tv 
            << "\nscalar     : " << scalar
            << "\nexpected:    " << expected 
            << "\nresult:      " << result << "\n";
        return oss.str();
    }

    std::string expectedResultMessage(const Vec2<T>& v1, const Vec2<T>& v2, const T& expected, const T& result)
    {
        std::ostringstream oss;
        oss << "\nv1:          " <<  v1 
            << "\nv2:          " <<  v2
            << "\nexpected:    " << expected 
            << "\nresult:      " << result << "\n";
        return oss.str();
    }

    std::string expectedResultMessage(const Vec2<T>& v1, const Vec2<T>& v2, const float& expected, const float& result)
    {
        std::ostringstream oss;
        oss << "\nv1:          " <<  v1 
            << "\nv2:          " <<  v2
            << "\nexpected:    " << expected 
            << "\nresult:      " << result << "\n";
        return oss.str();
    }

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


    void magnitudeTest(const Vec2<T>& v)
    {
        T expected = (T)sqrt(v.x * v.x + v.y * v.y);
        T result = v.magnitude();
        std::string errmsg = expectedResultMessage(v, expected, result);
        MY_ASSERT(result == expected, errmsg);
    }

    void normalizeTest(const Vec2<T>& v)
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
            expected = { static_cast<T>(v.x/mag), static_cast<T>(v.y/mag)};
            result = v.normalize();
        }
        catch (const std::runtime_error& e) 
        {
            std::cerr << "[RUNTIME ERROR] function: " << __PRETTY_FUNCTION__ << "\n"
                    << e.what()
                    << "\ttest vector: " << v << ", magnitude: << " << mag << "\n"; 
            expected = {0, 0};
        }

        std::string errmsg = expectedResultMessage(v, expected, result);
        MY_ASSERT(float_equality(expected, result), errmsg);
    }

    void operatorMultiplyTest(const Vec2<T>& v, const T& scalar)
    {
        Vec2<T> expected = {v.x * scalar, v.y * scalar};
        Vec2<T> result = v * scalar;
        std::string errmsg = expectedResultMessage(v, scalar, expected, result);
        MY_ASSERT(result == expected, errmsg);
    }

    void operatorMultiplyEqualsTest(const Vec2<T>& v, const T& scalar)
    {
        Vec2<T> expected = {v.x * scalar, v.y * scalar};
        Vec2<T> result = v;
        result *= scalar;
        std::string errmsg = expectedResultMessage(v, scalar, expected, result);
        MY_ASSERT(result == expected, errmsg);
    }

    void operatorDivideTest(const Vec2<T>& v, const T& scalar)
    {
        Vec2<T> expected; 
        Vec2<T> result; 
        
        try
        {
            expected = {v.x/scalar, v.y/scalar};
            result = v / scalar;
        }
        catch (const std::runtime_error& e) 
        {
            std::cerr << "[RUNTIME ERROR] function: " << __PRETTY_FUNCTION__ << "\n"
                    << e.what()
                    << "\ttest vector: " << v << ", scalar: << " <<  scalar << "\n"; 
            expected = {0, 0};
            result = Vec2<T>();
        }

        std::string errmsg = expectedResultMessage(v, scalar, expected, result);
        MY_ASSERT(result == expected, errmsg);
    }

    void operatorDivideEqualsTest(const Vec2<T>& v, const T& scalar)
    {
        Vec2<T> expected; 
        Vec2<T> result = v; 
        
        try
        {
            expected = {v.x/scalar, v.y/scalar};
            result /= scalar;
        }
        catch (const std::runtime_error& e) 
        {
            std::cerr << "[RUNTIME ERROR] function: " << __PRETTY_FUNCTION__ << "\n"
                    << e.what()
                    << "\ttest vector: " << v << ", scalar: << " <<  scalar << "\n"; 
            expected = {0, 0};
            result = Vec2<T>();
        }

        std::string errmsg = expectedResultMessage(v, scalar, expected, result);
        MY_ASSERT(result == expected, errmsg);
    }

    void unaryMinusTest(const Vec2<T>& v)
    {
        Vec2<T> expected = {-v.x, -v.y};
        Vec2<T> result = -v;
        std::string errmsg = expectedResultMessage(v, expected, result);
        MY_ASSERT(result == expected, errmsg);
    }

    void dotProductTest(const Vec2<T>& v1, const Vec2<T>& v2)
    {
        T result = v1.dotProduct(v2);
        T expected = (v1.x * v2.x + v1.y * v2.y);
        std::string errmsg = expectedResultMessage(v1, v2, expected, result);
        MY_ASSERT(expected == result, errmsg); 
    }

    void distanceTest(const Vec2<T>& v1, const Vec2<T>& v2)
    {
        float result = v1.distance(v2);
        float expected = sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));    
        std::string errmsg = expectedResultMessage(v1, v2, expected, result);
        MY_ASSERT(expected == result, errmsg);
    }

    void angleTest(const Vec2<T>& v1, const Vec2<T>& v2)
    {
        float result = v1.angle(v2);
        T dotP = v1.dotProduct(v2);
        float magv1 = v1.magnitude();
        float magv2 = v2.magnitude();
        
        // TO THINK ABOUT: probably should not be relying on class functions?
        float expected = acos(static_cast<float>(dotP) / (magv1 * magv2));   

        std::string errmsg = expectedResultMessage(v1, v2, expected, result);
        MY_ASSERT(float_equality(expected, result), errmsg);
    }


    void operatorMinusTest(const Vec2<T>& v1, const Vec2<T>& v2)
    {
        Vec2<T> expected = {v1.x - v2.x, v1.y - v2.y};
        Vec2<T> result = v1 - v2;
        std::string errmsg = expectedResultMessage(v1, v2, expected, result);
        MY_ASSERT(result == expected, errmsg);
    }

    void operatorMinusEqualsTest(const Vec2<T>& v1, const Vec2<T>& v2)
    {
        Vec2<T> result = v1;          // copy v1
        Vec2<T> expected = {v1.x - v2.x, v1.y - v2.y};

        result -= v2;
        std::string errmsg = expectedResultMessage(v1, v2, expected, result);
        MY_ASSERT(result == expected, errmsg);
    }


    void operatorPlusTest(const Vec2<T>& v1, const Vec2<T>& v2)
    {
        Vec2<T> expected = {v1.x + v2.x, v1.y+v2.y};
        Vec2<T> result = v1 + v2;
        std::string errmsg = expectedResultMessage(v1, v2, expected, result);
        MY_ASSERT(result == expected, errmsg);

    }

    void operatorPlusEqualsTest(const Vec2<T>& v1, const Vec2<T>& v2)
    {
        Vec2<T> result = v1;          // copy v1
        Vec2<T> expected = {v1.x + v2.x, v1.y + v2.y};

        result += v2;
        std::string errmsg = expectedResultMessage(v1, v2, expected, result);
        MY_ASSERT(result == expected, errmsg);
    }

    bool float_equality(const Vec2<T>& v1, const Vec2<T>& v2)
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

    bool float_equality(const float& v1, const float& v2)
    {
        if( fabs(v1 - v2) < EQUALITY_EPISLON)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
};
