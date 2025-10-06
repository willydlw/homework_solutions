#include <iostream>
#include <string>

#include "game.h"

int main(int argc, char* argv[])
{
    std::string configFileName;

    if(argc == 2)
    {
        configFileName = argv[1];
    }
    else
    {
        std::cerr << "\n[INFO] Specify configuration file\n";
        std::cerr << "usage 1: " << argv[0] << " configFileName\n";
        return 1;
    }

   
    Game game;

    game.init(configFileName);
    game.run();

    return 0;
}