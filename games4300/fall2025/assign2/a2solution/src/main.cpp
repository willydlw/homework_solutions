#include <iostream>

#include "game.h"

int main()
{
    std::string configFile = {"config.txt"};
    std::cout << "Assign 2\n";
    Game game;
    game.init(configFile);

    return 0;
}