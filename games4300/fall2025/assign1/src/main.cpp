#include <iostream>
#include <string>
#include <filesystem>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>


#include "game.hpp"
#include "gameConfig.hpp"
#include "circle.hpp"
#include "rectangle.hpp"



int main(void)
{
    Game game;
    GameConfig gameConfig;
   
    std::string configFileName("assign1/config/config.txt");
    readConfigFile(configFileName, &gameConfig);

    game.init(&gameConfig);

    sf::RenderWindow window(sf::VideoMode({gameConfig.window.width, gameConfig.window.height}), "Assign 1");
    window.setFramerateLimit(60);

    std::cerr << "\n" << game << "\n";

    #if 0
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


    #endif

 
    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            
            #if 0
            // pass the event to imgui to be parsed 
            ImGui::SFML::ProcessEvent(window, *event);
            #endif 

            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        game.update(window.getSize());

        window.clear(sf::Color::Blue);
        game.draw(window);
        window.display();
    }


    return 0;
}