#include "gameConfig.h"

#include <fstream>
#include <iostream>
#include <sstream>

 std::filesystem::path GameConfig::getWorkingDirectory()
 {
    try
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        return currentPath;
    } 
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "[ERROR] function: " << __PRETTY_FUNCTION__ 
            << ", error description: " << e.what() << std::endl;
        return {};
    }
 }


std::vector<std::filesystem::path> GameConfig::searchDirectory(
        const std::string& targetDirectory, const std::string&& targetFile)
{
    std::vector<std::filesystem::path> foundFiles = findFileRecursive(targetDirectory, targetFile);

    if(foundFiles.empty())
    {
        std::filesystem::path workingDirectory = getWorkingDirectory();

        std::cerr << "\n[WARNING] function: " << __PRETTY_FUNCTION__ 
            << ", targetFile: " << targetFile 
            << " not found in directory: " << targetDirectory << "\n";
        std::cerr << "[RECOVERY ATTEMPT] searching directory path: " 
            << workingDirectory << "\n";

        foundFiles = findFileRecursive(workingDirectory, targetFile);

        if(foundFiles.empty())
        {
            std::cerr << "\n[WARNING] targetFile: " << targetFile 
                << " not found in directory: " << workingDirectory << "\n";
        }
        else 
        {
            std::cerr << "\n[RECOVERY RESULTS] found " << targetFile 
                << " in search directory: " << workingDirectory 
                << " at following locations:\n";
            printPaths(foundFiles);
        }
    }

    return foundFiles;
}


std::vector<std::filesystem::path> GameConfig::findFileRecursive( 
        const std::filesystem::path& targetPath, 
        const std::string& targetFile)
{
    std::vector<std::filesystem::path> foundFiles; 

    if(!std::filesystem::exists(targetPath) || !std::filesystem::is_directory(targetPath))
    {
        std::cerr << "[ERROR] function: " << __PRETTY_FUNCTION__ 
            << " targetPath: " << targetPath 
            << " does not exist or is not a directory\n";
        return foundFiles;
    }

    // iterate through the directory recursively 
    for(const auto& entry : std::filesystem::recursive_directory_iterator(targetPath))
    {
        if(entry.is_regular_file() && entry.path().filename() == targetFile)
        {
            foundFiles.push_back(entry.path());
        }
    }

    return foundFiles;
}


void GameConfig::printPaths(const std::vector<std::filesystem::path>& paths)
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
    std::vector<std::filesystem::path> foundFiles = searchDirectory(CONFIG_DIR_NAME, fileName);

    if(foundFiles.empty())
    {
        std::cerr << "[ERROR] function: " << __PRETTY_FUNCTION__ 
            << ", file: " << fileName << " not found in directory : "
            << CONFIG_DIR_NAME << "\n";
        return false;
    }

    for(const auto& f : foundFiles)
    {
        inFile.open(f);
        if(inFile.is_open())
        {
            std::cerr << "[INFO] opened file: " << f << "\n";
            break;
        }
        else
        {
            std::cerr << "[WARNING] function: " << __PRETTY_FUNCTION__ 
                << " could not open file: " << f << "\n";
        }

        if(!inFile.is_open())
        {
            std::cerr << "[ERROR] function: " << __PRETTY_FUNCTION__ 
                << ", failed to open any of the found configuration files\n";
            return false;
        }

        std::string line;
        while(std::getline(inFile, line))
        {
            std::istringstream iss(line);
            std::string firstWord;
            iss >> firstWord;
            if(firstWord == "Window")
            {
                if( !(iss >> m_windowConfig.width) ||
                    !(iss >> m_windowConfig.height) || 
                    !(iss >> m_windowConfig.frameLimit) || 
                    !(iss >> m_windowConfig.fullScreenMode))
                {
                    std::cerr << "[WARNING] function: " << __PRETTY_FUNCTION__ 
                        << ", failed to read window configuration\n";
                }
                continue;
            }
        }
    }


    inFile.close();
}