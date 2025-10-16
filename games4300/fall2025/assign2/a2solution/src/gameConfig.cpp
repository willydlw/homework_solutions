#include <fstream>
#include <iostream>
#include <sstream>

#include "gameConfig.h"
#include "logError.hpp"

 std::filesystem::path GameConfig::getWorkingDirectory()
 {
    try
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        return currentPath;
    } 
    catch (const std::filesystem::filesystem_error& e)
    {
        LOG_ERROR("\n\terror description: ", e.what());
        return {};
    }
 }


std::vector<std::filesystem::path> GameConfig::searchDirectory(
        const std::string& targetDirectory, const std::string& targetFile)
{
    std::vector<std::filesystem::path> foundFiles = findFileRecursive(targetDirectory, targetFile);

    if(foundFiles.empty())
    {
        std::filesystem::path workingDirectory = getWorkingDirectory();

        LOG_WARNING("\n\ttargetFile: ", targetFile, " not found in directory: ", targetDirectory);
        LOG_INFO("\n\tRecovery attempt, searching directory path: " , workingDirectory);

        foundFiles = findFileRecursive(workingDirectory, targetFile);
        if(foundFiles.empty())
        {
            LOG_WARNING("\n\ttargetFile: ", targetFile, " not found in directory: ", targetDirectory);
        }
        else 
        {
            std::ostringstream oss;
            for(const auto& file : foundFiles)
            {
                oss << "\t" << file << "\n";
            }

            LOG_INFO("\n\tRecovery results, found ", targetFile, " in directory: ", workingDirectory,"\n", oss.str());
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
        LOG_ERROR("targetPath: ", targetPath, "does not exist or is not a directory");
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
        LOG_ERROR(fileName, " not found in directory: ", CONFIG_DIR_NAME);
        return false;
    }

    for(const auto& f : foundFiles)
    {
        inFile.open(f);
        if(inFile.is_open())
        {
            LOG_INFO("opened file: ", f);
            break;
        }
        else
        {
            LOG_WARNING("failed to open file: ", f);
        }

        if(!inFile.is_open())
        {
            LOG_ERROR("failed to open any of the found configuration files");
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
    return true;
}