#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

#include "config.h"
#include "circle.h"
#include "helper.h"
#include "rectangle.h"

// g++ -Wall main.cpp helper.cpp circle.cpp rectangle.cpp config.cpp -lsfml-graphics -lsfml-window -lsfml-system


int main(int argc, char * argv[])
{
   // configuration variables
   std::string configFileName = "config.txt";
   bounce::window_t windowConfig = {.width = 640, .height = 480};
   bounce::font_t fontConfig = {.fileName="unknown", .size = 18, .color = {0,0,0}};
   std::vector<bounce::rectangle_t> rectConfig;
   std::vector<bounce::circle_t> circleConfig;

   // drawing variables
   std::vector<bounce::Circle> circles;
   std::vector<bounce::Rectangle> rectangles;
   sf::Vector2f windowBoundary;

   if(argc > 1)
   {
      configFileName = argv[1];
   }

   if(!bounce::loadConfiguration(configFileName, &windowConfig, &fontConfig, rectConfig, circleConfig))
   {
      std::cerr << "Program terminating due to file open error, file name: " << configFileName << "\n";
      exit(-1);
   }


   // create a new window of size width * height pixels
   // top-left of window is (0,0) and bottom-right is (w,h)
   sf::RenderWindow window(sf::VideoMode(windowConfig.width, windowConfig.height), "Bouncing Shapes");
   window.setFramerateLimit(60);

   // load a font so we can display text
   sf::Font gameFont;

   // attempt to load the font from a file
   if(!gameFont.loadFromFile(fontConfig.fileName))
   {
      std::cerr << "Could not load font from file: " << fontConfig.fileName << "\n";
      exit(-1);
   }

   // initialize circle shape objects and their speeds
   bounce::initCircleShapes(circleConfig, circles, gameFont, &fontConfig);
   bounce::initRectangleShapes(rectConfig, rectangles, gameFont, &fontConfig);

  
   
   // DEBUG code: print circle data
   for(auto& c : circles)
   {
      std::cout << c << "\n";

      sf::FloatRect gbounds = c.circle.getGlobalBounds();
      sf::FloatRect lbounds = c.circle.getLocalBounds();
     
      bounce::printBounds(lbounds, "Local Bounds");
      bounce::printBounds(gbounds, "Global Bounds");  

      c.updatePosition(windowBoundary);
   }

   windowBoundary.x = windowConfig.width;
   windowBoundary.y = windowConfig.height;

   while(window.isOpen())
   {
      // check all the window's events taht were triggered since the last loop iteration
      sf::Event event;
      while(window.pollEvent(event))
      {
         // this event triggers when the window is closed
         if(event.type == sf::Event::Closed)
         {
            window.close();
         }

         // key pressed event
         if(event.type == sf::Event::KeyPressed)
         {
            std::cout << "Key pressed with code = " << event.key.code << "\n";
            
            if(event.key.code == sf::Keyboard::X)
            {
               std::cout << "X key pressed\n";
            }
         }
      }

      // Update

      for(auto& c : circles)
      {
         c.updatePosition(windowBoundary);
      }

      for(auto& r : rectangles)
      {
         r.updatePosition(windowBoundary);
      }
      

      // Draw - rendering function calls

      window.clear(sf::Color::Black);

      for(auto& c : circles)
      {
         c.draw(window);
      } 

      for(auto& r : rectangles)
      {
         r.draw(window);
      } 


      // display the current frame
      window.display();
   
   }
   
   return 0;
}