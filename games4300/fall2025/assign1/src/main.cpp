#include <iostream>
#include <string>
#include <filesystem>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>


#include "game.h"
#include "gameConfig.h"


int main(void)
{
    Game game;
    GameConfig gameConfig;

    // UI variables 
    int selectedItem = -1;
   
    std::string configFileName("config.txt");
    readConfigFile(configFileName, &gameConfig);

    game.init(&gameConfig);

    sf::RenderWindow window(sf::VideoMode({gameConfig.window.width, gameConfig.window.height}), "Assign 1");
    window.setFramerateLimit(60);

    // initialize imgui and create a clock used for its internal timing
    if(!ImGui::SFML::Init(window))
    {
        std::cerr << "ImGui::SFML::Init failure\n";
        std::exit(-1);
    }
    sf::Clock deltaClock;

    // scale the imgui ui and text by a given factor
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

 
    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            
            #if 1
            // pass the event to imgui to be parsed 
            ImGui::SFML::ProcessEvent(window, *event);
            #endif 

            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        // update imgui for this frame with the time that the last frame took
        ImGui::SFML::Update(window, deltaClock.restart());

        // Update from UI elements
        ImGui::Begin("Shapes List");
        
        for(int i = 0; i < (int)game.shapeNames.size(); i++)
        {
            if(ImGui::Selectable(game.shapeNames[i].c_str(), selectedItem == i))
            {
                selectedItem = i;
                std::cerr << "selected shape: " << game.shapeNames[i] << "\n";
            }
        }
       
        ImGui::End();

        game.update(window.getSize());

        window.clear(sf::Color::White);
        game.draw(window);
        ImGui::SFML::Render(window); // draw the UI last so its on top
        window.display();
    }


    return 0;
}