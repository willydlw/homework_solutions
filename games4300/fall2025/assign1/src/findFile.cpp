#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

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

int main() {
    // Get the current working directory
    fs::path currentPath = fs::current_path();
    std::string targetFilename = "tech.ttf"; // Replace with the file you want to find

    std::cout << "Searching for '" << targetFilename << "' in '" << currentPath << "' and its subdirectories..." << std::endl;

    std::vector<fs::path> results = findFileRecursive(currentPath, targetFilename);

    if (results.empty()) {
        std::cout << "File '" << targetFilename << "' not found." << std::endl;
    } else {
        std::cout << "Found '" << targetFilename << "' at the following locations:" << std::endl;
        for (const auto& path : results) {
            std::cout << path << std::endl;
        }
    }

    return 0;
}