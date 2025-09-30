#include "gameConfig.h"

#include <fstream>
#include <iostream>
#include <sstream>

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
std::vector<std::filesystem::path> findFileRecursive(const std::filesystem::path& startPath, const std::string& filenameToFind) {
    std::vector<std::filesystem::path> foundFiles;

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
    std::ifstream inFile;
    std::filesystem::path workDir = getWorkingDirectory();
    std::cerr << "workDir: " << workDir << "\n";

    std::vector<std::filesystem::path> foundFiles = findFileRecursive(workDir, fileName);

    if(foundFiles.empty())
    {
        std::cerr << "ERROR, function: " << __PRETTY_FUNCTION__ 
            << ", file: " << fileName << "not found\n";
        return false;
    }

    for(auto f : foundFiles)
    {
        std::cerr << f << "\n";
        inFile.open(f);
        if(inFile.is_open())
        {
            break;
        }
        else{
            std::cerr << "Could not open " << f << "\n";
        }
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
                !(iss >> gameConfig->font.color.r) ||
                !(iss >> gameConfig->font.color.g) || 
                !(iss >> gameConfig->font.color.b) ){
                    std::cerr << "Warning: " << __func__ 
                    << ", error extracting font data from input: "
                    << line << "\n";
                    continue;
                }
        }
        else if(firstWord == "Circle"){
            CircleConfig cc;
            if( !(iss >> cc.shapeName)            || 
                !(readVector2f(iss, cc.position)) ||
                !(readVector2f(iss, cc.velocity)) ||
                !(readColor(iss, cc.color))       ||
                !(iss >> cc.radius)
            )
            {
                std::cerr << "Warning: " << __func__ 
                    << ", error extracting circle data from input: " 
                    << line << "\n";
                continue;
            }
           
            gameConfig->circles.push_back(cc);
        }
        else if(firstWord == "Rectangle"){
            RectangleConfig rc;
            if( !(iss >> rc.shapeName)              || 
                !(readVector2f(iss, rc.position))   ||
                !(readVector2f(iss, rc.velocity))   ||
                !(readColor(iss, rc.color))         ||
                !(iss >> rc.width)                  ||
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


bool readVector2f(std::istringstream& iss, sf::Vector2f& v2)
{
    if(!(iss >> v2.x) || !(iss >> v2.y))
    {
        std::cerr << "ERROR function " << __func__ << "\n";
        return false;
    }

    return true;
}

/* sf::color type uint8_t 
   istringstream operator >> interprets uint8_t as unsigned char
   
   If we try iss >> color.r, only the character 2 will be extracted
   from the input 255. 
   
   To read the entire value of 255, we declare local unsigned int 
   variables to extract the entire value and then cast unsigned int 
   to uint8_t when assigning to color fields

*/ 
            
bool readColor(std::istringstream& iss, sf::Color& color)
{
    unsigned red, green, blue;
    if( !(iss >> red)   ||
        !(iss >> green) ||
        !(iss >> blue))
    {
        return false;
    }
    
    color.r = static_cast<uint8_t>(red);
    color.g = static_cast<uint8_t>(green);
    color.b = static_cast<uint8_t>(blue);
       
    return true;
}

