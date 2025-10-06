#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

bool findFileInDirectory(const fs::path& directoryPath, const std::string& fileNameToFind, fs::path& foundFilePath) {
    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath)) {
        std::cerr << "Error: Directory does not exist or is not a directory: " << directoryPath << std::endl;
        return false;
    }

    for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
        if (fs::is_regular_file(entry.path()) && entry.path().filename() == fileNameToFind) {
            foundFilePath = entry.path();
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    std::cerr << "argc: " << argc << " argv[0]: " << argv[0] << "\n";
    fs::path searchDir = "assign1/config"; // Example directory
    std::string targetFile = "config.txt"; // Example file name
    fs::path foundPath;

    if (findFileInDirectory(searchDir, targetFile, foundPath)) {
        std::cout << "File found at: " << foundPath << std::endl;
    } else {
        std::cout << "File not found." << std::endl;
    }

    return 0;
}