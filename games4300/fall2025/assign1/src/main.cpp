#include <iostream>
#include <string>

#include <filesystem>

#include "config.h"

void doesItExist(std::filesystem::path& path)
{
    if(std::filesystem::exists(path)){
        std::cout << "path: " << path << " exists\n";
    }
    else{
        std::cout << "path: " << path << " does not exist\n";
    }
}

int main(void)
{
    GameConfig gameConfig;

    std::string configFileName("assign1/config/config.txt");
    
    #if 0
    std::filesystem::path config_file_path = "assign1/config/config.txt";
    std::filesystem::path fonts_file_path = "assign1/fonts/tech.ttf";
    doesItExist(config_file_path);
    doesItExist(fonts_file_path);
    #endif

    readConfigFile(configFileName, &gameConfig);
    return 0;
}