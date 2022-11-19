#include "config.h"
#include <string>
#include <vector>
#include <iostream>

/* g++ -Wall readConfigFile.cpp configFile.cpp 
*/

int main(int argc, char * argv[])
{
   std::string configFileName = "config.txt";
   bounce::window_t windowConfig = {640, 480};
   bounce::font_t fontConfig = {.fileName="unknown", .size = 0, .color = {0,0,0}};
   std::vector<bounce::rectangle_t> rects;
   std::vector<bounce::circle_t> circles;

   if(argc > 1)
   {
      configFileName = argv[1];
   }

   if(!loadConfiguration(configFileName, &windowConfig, &fontConfig, rects, circles))
   {
      std::cerr << "Error loading configuration file\n";
      return 1;
   }

   return 0;
}