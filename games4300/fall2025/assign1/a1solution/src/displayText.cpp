#include <iostream>
#include <string>
#include <filesystem>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <array>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

std::filesystem::path getWorkingDirectory(void){
    try {
        std::filesystem::path currentPath = std::filesystem::current_path();
        return currentPath;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error getting current path: " << e.what() << std::endl;
        std::exit(-1);
    }
}

// Function to recursively search a directory and its subdirectories for a file
std::vector<fs::path> findFileRecursive(const fs::path& startPath, const std::string& filenameToFind) {
    std::vector<fs::path> foundFiles;

    // Check if the starting path is a directory
    if (!fs::is_directory(startPath)) {
        std::cerr << "Error: " << startPath << " is not a directory." << std::endl;
        return foundFiles;
    }

    // Iterate through the directory recursively
    for (const auto& entry : fs::recursive_directory_iterator(startPath)) {
        // Check if the current entry is a regular file and its name matches the target
        if (entry.is_regular_file() && entry.path().filename() == filenameToFind) {
            foundFiles.push_back(entry.path());
        }
    }
    return foundFiles;
}


bool openFont(const std::string& fontFileName, sf::Font& font)
{
    // Get the current working directory
    std::filesystem::path workingDirPath = getWorkingDirectory();

    // Search for font file in current working directory
    std::vector<std::filesystem::path> foundFontFiles;
    foundFontFiles = findFileRecursive(workingDirPath, fontFileName);

    if(foundFontFiles.empty()){
        std::cerr << "[FATAL] failed to find file: " << fontFileName
            << " in working directory: " << workingDirPath 
            << "\n";
        return false;
    }

    for(const auto &found : foundFontFiles){
    
        if(font.openFromFile(found)){
            //std::cerr << "[SUCCESS] font.openFromFile(" << found << ")\n";
            return true;
        }
        else{
            std::cerr << "[WARNING] function: " << __func__ 
                << " failed to open font file: " 
                << found << "\n";
        }
    }

    return false;
}


void printTextInfo(const sf::Text& text)
{
    sf::FloatRect tlocal = text.getLocalBounds();
    std::cerr << "\n[TEXT INFO]\n";
    std::cerr << "string:         " << (std::string)text.getString() << "\n";
    std::cerr << "character size: " << text.getCharacterSize() << " pixels\n";
    std::cerr << "origin       x: " << text.getOrigin().x 
            << ", y: " << text.getOrigin().y << "\n";

    std::cerr << "local bounds\n"
            << "\tposition x: " << tlocal.position.x << ", y: " 
            << tlocal.position.y << "\n";

    std::cerr << "\tsize x: " << tlocal.size.x << ", y: " 
            << tlocal.size.y << "\n";

    sf::FloatRect tglobal = text.getGlobalBounds();
    std::cerr << "global bounds\n"
            << "\tposition x: " << tglobal.position.x << ", y: "
            << tglobal.position.y << "\n";
    std::cerr << "\tsize x: " << tglobal.size.x << ", y: "
            << tglobal.size.y << "\n";
}


int main(void)
{
    static constexpr unsigned int WINDOW_WIDTH = 320;
    static constexpr unsigned int WINDOW_HEIGHT = 240;
    
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Display Text");
    window.setFramerateLimit(10);

    std::string fontFileName = "tech.ttf";
    sf::Font font;

    if(!openFont(fontFileName, font))
    {
        std::cerr << "[FATAL] failed to open font file\n";
        std::exit(-1);
    }

    // sf::Text has no default constructor, so declaring it here after we have 
    // font object.
    sf::Text text(font);
    text.setString("WoW");
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::Blue);
    text.setPosition({WINDOW_WIDTH/2, WINDOW_HEIGHT/2});

    std::cerr << "\n[WINDOW INFO] width: " << WINDOW_WIDTH << ", height: " << WINDOW_HEIGHT << "\n";
    printTextInfo(text);

    // vertical line
    std::array<sf::Vertex, 2> verticalLine = {
        sf::Vertex{sf::Vector2f{WINDOW_WIDTH/2, 0}, sf::Color::Black},
        sf::Vertex{sf::Vector2f{WINDOW_WIDTH/2, WINDOW_HEIGHT}, sf::Color::Black}
    };

    std::array<sf::Vertex, 2> horizontalLine = {
        sf::Vertex{sf::Vector2f{0, WINDOW_HEIGHT/2}, sf::Color::Black},
        sf::Vertex{sf::Vector2f{WINDOW_WIDTH, WINDOW_HEIGHT/2}, sf::Color::Black}
    };

    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(verticalLine.data(), verticalLine.size(), sf::PrimitiveType::Lines);
        window.draw(horizontalLine.data(), horizontalLine.size(), sf::PrimitiveType::Lines);
        window.draw(text);
        window.display();
    }


    return 0;
}