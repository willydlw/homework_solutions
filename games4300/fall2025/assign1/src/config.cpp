#include "config.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>

void readWindowConfig(std::stringstream &iss, WindowConfig *wc)
{
    std::cerr << __func__ << ", iss: " << iss.str() << std::endl; 
}

bool readConfigFile(const std::string& fileName, GameConfig *gameConfig)
{
    std::ifstream inFile(fileName);
    if(!inFile.is_open()){
        std::cerr << "WARNING: " << __func__ 
            << " failed to open file: " << fileName
            << "\n";
        std::cerr << "current path: " << std::filesystem::current_path() << "\n";
        return false;
    }

    std::cerr << "File: " << fileName << " contains the following lines\n";
    std::string line;
    while(std::getline(inFile, line)){
        std::cout << line << std::endl;
        std::istringstream iss(line);
        std::string firstWord;
        iss >> firstWord;           // extract the first word 
        if(firstWord == "Window"){
            std::cerr << "TODO: Call Window Configuration function\n";
            //readWindowConfig(iss, &(gameConfig->window));
        }
        else if(firstWord == "Font"){
            std::cerr << "TODO: Call Font Configuration function\n";
        }
        else if(firstWord == "Circle"){
            std::cerr << "TODO: Call Circle Configuration function\n";
        }
        else if(firstWord == "Rectangle"){
            std::cerr << "TODO: Call Rectangle Configuration function\n";
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