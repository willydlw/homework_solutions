#include <iostream>
#include <string>
#include <filesystem>
#include <optional>

#include <SFML/Graphics.hpp>

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

    sf::RenderWindow window(sf::VideoMode({gameConfig.window.width, gameConfig.window.height}), "Assign 1");


    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::Blue);
        window.display();
    }

    return 0;
}