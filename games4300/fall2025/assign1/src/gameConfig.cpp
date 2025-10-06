#include "gameConfig.h"

#include <fstream>
#include <iostream>
#include <sstream>

// use namespace alias to reduce typing and enhance readability
namespace fs = std::filesystem;

// Returns executable directory path
fs::path GameConfig::getWorkingDirectory(void){
    try {
        fs::path currentPath = fs::current_path();
        return currentPath;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "[ERROR] function: " << __PRETTY_FUNCTION__ 
                  << ", error description: " << e.what() << std::endl;
        std::exit(-1);
    }
}


// Searches target directory path and its subdirectories for target file
std::vector<fs::path> GameConfig::findFileRecursive(
    const fs::path& targetPath, 
    const std::string& targetFile )
{
    std::vector<fs::path> foundFiles;

    // Verify targetPath is a directory
    if (!fs::exists(targetPath) || !fs::is_directory(targetPath)) {
        std::cerr << "[ERROR]: function: " << __PRETTY_FUNCTION__ 
                << " targetPath: " << targetPath 
                << " does not exist or is not a directory\n";
        return foundFiles;
    }

    // Iterate through the directory recursively
    for (const auto& entry : fs::recursive_directory_iterator(targetPath)) {
        // Check if the current entry is a regular file and its name matches the target
        if (entry.is_regular_file() && entry.path().filename() == targetFile) {
            foundFiles.push_back(entry.path());
        }
    }

    return foundFiles;
}

// Searches working directory and its subdirectories for the target file
void GameConfig::fileOnlySearch(const std::string& targetFile)
{
    fs::path workingDirectory = getWorkingDirectory();
    
    std::cout << "\n[INFO] Executing function " << __PRETTY_FUNCTION__ << "\n";
    std::cout << "[INFO] Working Search Directory: " << workingDirectory << "\n";
   
    
    std::vector<fs::path> foundFiles = findFileRecursive(workingDirectory, targetFile);

    if (foundFiles.empty()) {
        std::cout << "\n[RESULTS] File " << targetFile << " not found\n\n";
    } else {
        std::cout << "\n[RESULTS] Found " << targetFile << " at the following locations:\n";
        
        printPaths(foundFiles);
    }

}


void GameConfig::directoryAndFileSearch(const std::string& searchDirectory, const std::string& targetFile)
{
    std::vector<fs::path> foundFiles;
   

    std::cout << "\n[INFO] Executing function " << __PRETTY_FUNCTION__ << "\n";
    std::cout << "[INFO] Search Directory: " << searchDirectory << "\n";
    std::cout << "[INFO] Target File:      " << targetFile << "\n";
    
    foundFiles = findFileRecursive(searchDirectory, targetFile);

    if(!foundFiles.empty())
    {
        std::cout << "\n[RESULTS] Found " << targetFile 
            << " in search directory: " << searchDirectory 
            << " at following locations: \n";

        printPaths(foundFiles);
    }
    else 
    {
        fs::path workingDirectory = getWorkingDirectory();
        workingDirectory += "/" + searchDirectory;

        std::cout << "\n[RESULTS] targetFile: " << targetFile 
                << " not found in directory: " << searchDirectory << "\n";
        std::cout << "[SECOND ATTEMPT] adding search directory to working directory\n"
                << "Searching directory path: " << workingDirectory << "\n";
        foundFiles = findFileRecursive(workingDirectory, targetFile);
        if(foundFiles.size() == 0)
        {
            std::cout << "\n[RESULTS] targetFile: " << targetFile 
                << " not found in directory: " << workingDirectory << "\n";
        }
        else
        {
            std::cout << "\n[RESULTS] Found " << targetFile 
            << " in search directory: " << workingDirectory 
            << " at following locations: \n";
            
            printPaths(foundFiles);
        }
    }
    
}


void GameConfig::printPaths(const std::vector<fs::path>& paths)
{
    for(const auto& path : paths)
    {
        std::cout << path << "\n";
    }
    std::cout << std::endl;
}


bool GameConfig::readConfigFile(const std::string& fileName)
{
    std::ifstream inFile;
    std::filesystem::path workDir = getWorkingDirectory();

    std::cerr << "[INFO] function: " << __PRETTY_FUNCTION__ 
                << ", working directory path: " << workDir << "\n";
    
    std::cerr << "[INFO] searching working directory for file name: "
                << fileName << "\n";

    std::vector<std::filesystem::path> foundFiles = findFileRecursive(workDir, fileName);

    if(foundFiles.empty())
    {
        std::cerr << "ERROR, function: " << __PRETTY_FUNCTION__ 
            << ", file: " << fileName << "not found\n";
        return false;
    }

    std::cerr << "[INFO] files found\n";
    for(auto f : foundFiles)
    {
        std::cerr << "\t" << f << "\n";
    }

    for(auto f : foundFiles)
    {
        inFile.open(f);
        if(inFile.is_open())
        {
            std::cerr << "[INFO] opened file: " << f << "\n";
            break;
        }
        else{
            std::cerr   << "[WARNING] function: " << __PRETTY_FUNCTION__ 
                        << " could not open file: " << f << "\n";
        }
    }

    if(!inFile.is_open())
    {
        // possible that no files were opened 
        std::cerr   << "[ERROR] function: " << __PRETTY_FUNCTION__ 
                    << ", failed to open any of the found configuration files\n";
        return false;
    }


    std::string line;
    while(std::getline(inFile, line)){
        std::istringstream iss(line);
        std::string firstWord;
        iss >> firstWord;           // extract the first word 
        if(firstWord == "Window"){
            if( !(iss >> m_windowConfig.width)){
                std::cerr << "[WARNING], function: " << __PRETTY_FUNCTION__ 
                        << ", failed to read window width.\n"; 
                // continue processing next line of file input 
                continue;   
            }

            if( !(iss >> m_windowConfig.height)){
                std::cerr << "[WARNING], function: " << __PRETTY_FUNCTION__ 
                        << ", failed to read window height\n"; 
                
                continue;
            }
        }
        else if(firstWord == "Font"){
            // 
            if( !(iss >> m_fontConfig.fileName) || 
                !(iss >> m_fontConfig.fontSize) || 
                !(iss >> m_fontConfig.color.r) ||
                !(iss >> m_fontConfig.color.g) || 
                !(iss >> m_fontConfig.color.b) ){
                    std::cerr << "[WARNING], function: " << __PRETTY_FUNCTION__  
                        << ", failure reading font data\n";
                    continue;
                }
        }
        else if(firstWord == "Circle"){
            CircleConfig cc;
            if( !(iss >> cc.shapeConfig.name)            || 
                !(readVector2f(iss, cc.shapeConfig.position)) ||
                !(readVector2f(iss, cc.shapeConfig.velocity)) ||
                !(readColor(iss, cc.shapeConfig.color))       ||
                !(iss >> cc.radius)
            )
            {
                std::cerr << "[WARNING], function: " << __PRETTY_FUNCTION__  
                    << ", error extracting circle data\n"; 
                continue;
            }
           
            m_circleConfig.push_back(cc);
        }
        else if(firstWord == "Rectangle"){
            RectangleConfig rc;
            if( !(iss >> rc.shapeConfig.name)              || 
                !(readVector2f(iss, rc.shapeConfig.position))   ||
                !(readVector2f(iss, rc.shapeConfig.velocity))   ||
                !(readColor(iss, rc.shapeConfig.color))         ||
                !(iss >> rc.width)                  ||
                !(iss >> rc.height)
            )
            {
                std::cerr << "[WARNING], function: " << __PRETTY_FUNCTION__  
                    << ", error extracting rectangle data\n"; 
                continue;
            }

            m_rectConfig.push_back(rc);
        }
        else
        {
            std::cerr << "[WARNING], function: " << __PRETTY_FUNCTION__   
                << ", file: " << fileName 
                << " contains unrecognized first word: " << firstWord 
                << "\n";
        }
    }

    inFile.close();
    return true;
}


bool GameConfig::readVector2f(std::istringstream& iss, sf::Vector2f& v2)
{
    if(!(iss >> v2.x) || !(iss >> v2.y))
    {
        std::cerr << "[ERROR] function " << __PRETTY_FUNCTION__ 
            << ", failed to read x or y values\n";
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
            
bool GameConfig::readColor(std::istringstream& iss, sf::Color& color)
{
    unsigned red, green, blue;
    if( !(iss >> red)   ||
        !(iss >> green) ||
        !(iss >> blue))
    {
        std::cerr << "[ERROR] function " << __PRETTY_FUNCTION__ 
            << ", failed to read r,g, or b values\n";
        return false;
    }
    
    color.r = static_cast<uint8_t>(red);
    color.g = static_cast<uint8_t>(green);
    color.b = static_cast<uint8_t>(blue);
       
    return true;
}

