#pragma once 
#include <iostream>

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