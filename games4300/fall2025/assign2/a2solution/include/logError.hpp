#include <iostream>
#include <string>
#include <sstream>

enum class LogLevel
{
    INFO,
    WARNING,
    ERROR,
    FATAL
};

std::string logLevelToString(LogLevel level)
{
    switch(level)
    {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}


// Base case for variadic template recursion (no arguments)
void logBuildMessage(std::ostringstream& oss)
{
    // end of recursion, do nothing
    // Explicity cast to void to silence unused parameter warning
    (void) oss;         
}


// Recursive variadic template function for format arguments
template <typename T, typename... Args>
void logBuildMessage(std::ostringstream& oss, const T& arg, const Args&... args)
{
    oss << arg;
    logBuildMessage(oss, args...);
}


// Main logging function
template <typename... Args>
void logMessage(LogLevel level, const char* file, const char* func,
                int line, const Args&... args)
{
    std::ostringstream oss;
    oss << "[" << logLevelToString(level) << "] ";
    oss << file << ":" << line << " (" << func << ") - ";
    logBuildMessage(oss, args...);
    std::cerr << oss.str() << std::endl;
}



#define LOG_INFO(...) logMessage(LogLevel::INFO, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...) logMessage(LogLevel::WARNING, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) logMessage(LogLevel::ERROR, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) logMessage(LogLevel::ERROR, __FILE__, __func__, __LINE__, __VA_ARGS__)