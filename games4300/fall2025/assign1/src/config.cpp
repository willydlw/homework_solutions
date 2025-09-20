#include "config.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::filesystem::path getWorkingDirectory(void){
    try {
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::cout << "Current working directory: " << currentPath << std::endl;
        return currentPath;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error getting current path: " << e.what() << std::endl;
        std::exit(-1);
    }
}


// Function to recursively search for a file
std::vector<std::filesystem::path> findFileRecursive(const std::filesystem::path& startPath, const std::string& filenameToFind) {
    std::vector<std::filesystem::path> foundFiles;

    std::cerr << "Entered " << __func__ << ", startPath: " << startPath << "\n";
    std::cerr << "Searching for file: " << filenameToFind << "\n\n";

    // Check if the starting path is a directory
    if (!std::filesystem::is_directory(startPath)) {
        std::cerr << "Error: " << startPath << " is not a directory." << std::endl;
        return foundFiles;
    }

    // Iterate through the directory recursively
    for (const auto& entry : std::filesystem::recursive_directory_iterator(startPath)) {
        // Check if the current entry is a regular file and its name matches the target
        if (entry.is_regular_file() && entry.path().filename() == filenameToFind) {
            foundFiles.push_back(entry.path());
        }
    }
    return foundFiles;
}


bool readConfigFile(const std::string& fileName, GameConfig *gameConfig)
{
    std::ifstream inFile(fileName);
    if(!inFile.is_open()){
        std::cerr << "WARNING: " << __func__ 
            << ", failed to open file: " << fileName
            << "\n";
        std::cerr << "current path: " << std::filesystem::current_path() << "\n";
        return false;
    }

    std::string line;
    while(std::getline(inFile, line)){
        std::istringstream iss(line);
        std::string firstWord;
        iss >> firstWord;           // extract the first word 
        if(firstWord == "Window"){
            if( !(iss >> gameConfig->window.width)){
                std::cerr << "Warning, failed to read window width configuration. " 
                    << " input: " << line << "\n";
                // continue processing next line of file input 
                continue;   
            }

            if( !(iss >> gameConfig->window.height)){
                std::cerr << "Warning, failed to read window height configuration. " 
                << " input: " << line << "\n";
                continue;
            }
        }
        else if(firstWord == "Font"){
            // 
            if( !(iss >> gameConfig->font.fileName) || 
                !(iss >> gameConfig->font.fontSize) || 
                !(iss >> gameConfig->font.color.red) ||
                !(iss >> gameConfig->font.color.green) || 
                !(iss >> gameConfig->font.color.blue) ){
                    std::cerr << "Warning: " << __func__ 
                    << ", error extracting font data from input: "
                    << line << "\n";
                    continue;
                }
        }
        else if(firstWord == "Circle"){
            CircleConfig cc;
            if(!(iss >> cc.shapeName)   || 
                !(iss >> cc.position.x) ||
                !(iss >> cc.position.y) ||
                !(iss >> cc.speed.x)    ||
                !(iss >> cc.speed.y)    ||
                !(iss >> cc.color.red)  ||
                !(iss >> cc.color.green) ||
                !(iss >> cc.color.blue) ||
                !(iss >> cc.radius)
            ){
                std::cerr << "Warning: " << __func__ 
                    << ", error extracting circle data from input: " 
                    << line << "\n";
                continue;
            }

            gameConfig->circles.push_back(cc);
        }
        else if(firstWord == "Rectangle"){
            RectangleConfig rc;
            if(!(iss >> rc.shapeName)   || 
                !(iss >> rc.position.x) ||
                !(iss >> rc.position.y) ||
                !(iss >> rc.speed.x)    ||
                !(iss >> rc.speed.y)    ||
                !(iss >> rc.color.red)  ||
                !(iss >> rc.color.green) ||
                !(iss >> rc.color.blue) ||
                !(iss >> rc.width)      ||
                !(iss >> rc.height)
            ){
                std::cerr << "Warning: " << __func__ 
                    << ", error extracting rectangle data from input: " 
                    << line << "\n";
                continue;
            }

            gameConfig->rects.push_back(rc);
        }
        else{
            std::cerr << "<Warning> " << __func__ << ", file: " << fileName 
                << " contains unrecognized first word: " << firstWord 
                << "\n";
        }
    }

    inFile.close();
    return true;
}