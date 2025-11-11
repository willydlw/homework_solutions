#include <sstream>

#include "../include/fileUtility.h"
#include "../include/logError.hpp"

 std::filesystem::path getWorkingDirectory()
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


std::vector<std::filesystem::path> searchDirectory(
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


std::vector<std::filesystem::path> findFileRecursive( 
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


void printPaths(const std::vector<std::filesystem::path>& paths)
{
    for(const auto& path : paths)
    {
        std::cout << path << "\n";
    }

    std::cout << std::endl;
}
