#include "vecTest.hpp"
#include "randomNumberGenerator.hpp"

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
            float x = rg.generate(MIN_RANDOM_FLOAT, MAX_RANDOM_FLOAT);
            float y = rg.generate(MIN_RANDOM_FLOAT, MAX_RANDOM_FLOAT);
            float scalar = rg.generate(MIN_RANDOM_FLOAT, MAX_RANDOM_FLOAT);
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
    divideByZeroTest();
    singleVectorTests();
    twoVectorTests();
    testEdgeCases();
}



int main()
{
    runTests();
    return 0;
}