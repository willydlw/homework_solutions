#include <iostream>
#include <string>

#include <optional>


#include "game.h"



int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "Usage: ./assign1 configFileName\n";
        return 1;
    }

    std::string configFileName(argv[1]);
    Game game;

    game.init(configFileName);
    game.run();

    return 0;
}