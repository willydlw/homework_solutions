#include <iostream>

#include "game.h"

int main()
{
    std::string configFile = {"config.txt"};
    std::cout << "Assign 2\n";
    Game game(configFile);
    game.run();

    return 0;
}