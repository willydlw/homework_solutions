#pragma once 

#include <filesystem>
#include <vector>

// Searches the target directory and its subdirectories for the target file 
// Returns all directory paths found
std::vector<std::filesystem::path> searchDirectory(
    const std::string& targetDirectory, const std::string& targetFile);

// Returns program's current working directory (CWD). This is the directory 
// in the file system where the program is currently operating. 
// It is the default location for reading and writing files unless a program 
// is given an absolute file path
std::filesystem::path getWorkingDirectory();

// Searches for the target file starting int the start path.
// Recursively searches all sub-directories of the start path.
// Returns array of paths where target file was found.
// Return vector will be empty if target file was not found.
std::vector<std::filesystem::path> findFileRecursive( 
    const std::filesystem::path& startPath, 
    const std::string& targetFile);

// 
void printPaths(const std::vector<std::filesystem::path>& paths);