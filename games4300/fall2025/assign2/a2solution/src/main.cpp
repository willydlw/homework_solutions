#include <iostream>

#include "gameConfig.h"

int main()
{
    std::cout << "Assign 2\n";
    GameConfig gameConfig;

    gameConfig.readConfigFile("config.txt");

    return 0;
}