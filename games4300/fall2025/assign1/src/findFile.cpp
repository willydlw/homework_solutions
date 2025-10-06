#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

// use namespace alias to reduce typing and enhance readability
namespace fs = std::filesystem;


// Function Prototypes
fs::path getWorkingDirectory(void);

void fileOnlySearch(const std::string& targetFile);

void directoryAndFileSearch(
        const std::string& searchDirectory, 
        const std::string& targetFile);

void printPaths(const std::vector<fs::path>& paths);

std::vector<fs::path> findFileRecursive(
        const fs::path& targetPath, 
        const std::string& targetFile );


// Function Definitions

// Returns the executable directory path
fs::path getWorkingDirectory(void){
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
std::vector<fs::path> findFileRecursive(
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
// Displays 
void fileOnlySearch(const std::string& targetFile)
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


void directoryAndFileSearch(const std::string& searchDirectory, const std::string& targetFile)
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


void printPaths(const std::vector<fs::path>& paths)
{
    for(const auto& path : paths)
    {
        std::cout << path << "\n";
    }
    std::cout << std::endl;
}



int main(int argc, char* argv[]) 
{
    std::string targetFile {"default"};
    std::string targetDirectory {"default"};

    if(argc == 2)
    {
        targetFile = argv[1];
        fileOnlySearch(targetFile);
    }
    else if(argc == 3)
    {
        targetDirectory = argv[1];
        targetFile = argv[2];
        directoryAndFileSearch(targetDirectory, targetFile);
    }
    else
    {
        std::cerr << "\n[INFO] Program searches for targetFile\n";
        std::cerr << "usage 1: " << argv[0] << " targetDirectory targetFile\n";
        std::cerr << "usage 2: " << argv[0] << " targetFile\n";
        return 1;
    }

       
    return 0;
}