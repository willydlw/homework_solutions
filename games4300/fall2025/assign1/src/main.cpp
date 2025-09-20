#include <iostream>
#include <string>
#include <filesystem>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>


#include "config.h"
#include "circle.hpp"
#include "rectangle.hpp"



int main(void)
{
    GameConfig gameConfig;
    std::vector<Circle> circles;
    std::vector<Rectangle> rects;

    std::string configFileName("assign1/config/config.txt");
    readConfigFile(configFileName, &gameConfig);

    std::filesystem::path workingDirPath = getWorkingDirectory();

    std::vector<std::filesystem::path> foundFontFiles;
    foundFontFiles = findFileRecursive(workingDirPath, gameConfig.font.fileName);

    if(foundFontFiles.empty()){
        std::cerr << "ERROR, failed to find file: " << gameConfig.font.fileName 
            << " in working directory: " << workingDirPath 
            << "\n";
        std::exit(-1);
    }

    

    sf::Font myFont;

    for(const auto &found : foundFontFiles){
        std::cerr << found << "\n";

        if(myFont.openFromFile(found)){
            std::cerr << "Opened Font\n";
            break;
        }
       
    }


    #if 0
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


    // let's load a font so we can display some text
    sf::Font myFont(gameConfig.font.fileName);

    #endif

    #if 0
    // attempt to load the font from a file
    if(myFont.openFromFile(gameConfig.font.fileName))
    //if(myFont.openFromFile("/fonts/tech.ttf"))
    {
        std::cerr << "Failed to load font from file: "
            << gameConfig.font.fileName << "\n";
        std::exit(-1);
    }
    

    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            
            // pass the event to imgui to be parsed 
            ImGui::SFML::ProcessEvent(window, *event);

            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::Blue);
        window.display();
    }

    #endif

    return 0;
}