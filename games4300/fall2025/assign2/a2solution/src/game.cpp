#include "game.h"
#include "logError.hpp"

Game::Game() {}

void Game::init(const std::string& configFile)
{
    // TODO
    initConfig(configFile);
    
}


void Game::initConfig(const std::string& configFile)
{
    // TODO
    GameConfig gameConfig;
    if(!gameConfig.readConfigFile(configFile))
    {
        LOG_FATAL("Configuration Failed\n");
        std::exit(EXIT_FAILURE);
    }

    LOG_INFO("***Initial Configuration***");
    std::cerr << gameConfig;
}

#if 0
std::vector<std::string> searchForFiles(const std::string& targetFile)
{
    std::vector<std::string> foundFiles;

    return foundFiles;
}
#endif