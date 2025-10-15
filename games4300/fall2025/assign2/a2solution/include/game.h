#pragma once 

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

class Game 
{
    public:

    Game();

    void init(const std::string& configFile);

    private:
        sf::RenderWindow    m_window;

    void initConfig(const std::string& configFile);
    std::vector<std::string> searchForFiles(const std::string& targetFile);
    
};