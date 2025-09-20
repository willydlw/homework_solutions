#include <iostream>
#include <filesystem> // Required for std::filesystem

int main() {
    try {
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::cout << "Current working directory: " << currentPath << std::endl;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error getting current path: " << e.what() << std::endl;
    }
    return 0;
}