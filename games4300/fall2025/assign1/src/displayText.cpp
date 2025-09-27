#include <iostream>
#include <string>
#include <filesystem>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

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

// Function to recursively search for a file
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



int main(void)
{
    std::string fontFileName = "tech.ttf";

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Display Text");
    sf::Font font;


       // Get the current working directory
    std::filesystem::path workingDirPath = getWorkingDirectory();

    // Search for font file in current working directory
    std::vector<std::filesystem::path> foundFontFiles;
    foundFontFiles = findFileRecursive(workingDirPath, fontFileName);

    if(foundFontFiles.empty()){
        std::cerr << "ERROR, failed to find file: " << fontFileName
            << " in working directory: " << workingDirPath 
            << "\n";
        std::exit(-1);
    }

    for(const auto &found : foundFontFiles){
    
        if(font.openFromFile(found)){
            std::cerr << "Success font.openFromFile(" << found << ")\n";
            break;
        }
        else{
            std::cerr << "WARNING function: " << __func__ 
                << " failed to open font file: " 
                << found << "\n";
        }
    }

    sf::Text text(font);
    text.setString("WoW");
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::Blue);
    text.setPosition({400, 300});

    sf::FloatRect tlocal = text.getLocalBounds();
    std::cerr << "local bounds\n"
            << "position x: " << tlocal.position.x << ", y: " 
            << tlocal.position.y << "\n";

    std::cerr << "size x: " << tlocal.size.x << ", y: " 
            << tlocal.size.y << "\n";

    sf::FloatRect tglobal = text.getGlobalBounds();
    std::cerr << "global bounds\n"
            << "position x: " << tglobal.position.x << ", y: "
            << tglobal.position.y << "\n";
    std::cerr << "size x: " << tglobal.size.x << ", y: "
            << tglobal.size.y << "\n";
 
    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }


    return 0;
}