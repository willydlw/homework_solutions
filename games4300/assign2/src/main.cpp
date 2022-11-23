#include <SFML/Graphics.hpp>

#include "game.h"
#include <iostream>

int main()
{ 
   Game g("config.txt");
   g.run();

   return 0;
}