#include "config.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>


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