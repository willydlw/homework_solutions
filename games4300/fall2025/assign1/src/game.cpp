#include "game.hpp"


Game::Game(){/* intentionally blank */}

void Game::init(const GameConfig *gc)
{
    std::cerr << "TODO: complete function: " << __func__ << std::endl;

    if(!initFont(gc->font.fileName))
    {
        std::cerr << "ERROR, failed to open font: " << gc->font.fileName
                << "\n";
        std::exit(-1);
    }

    initRectangles(gc->rects);
    initCircles(gc->circles);
}


bool Game::initFont(const std::string& fileName)
{
    // Get the current working directory
    std::filesystem::path workingDirPath = getWorkingDirectory();

    // Search for font file in current working directory
    std::vector<std::filesystem::path> foundFontFiles;
    foundFontFiles = findFileRecursive(workingDirPath, fileName);

    if(foundFontFiles.empty()){
        std::cerr << "ERROR, failed to find file: " << fileName 
            << " in working directory: " << workingDirPath 
            << "\n";
        return false;
    }

    for(const auto &found : foundFontFiles){
        std::cerr << found << "\n";

        if(m_font.openFromFile(found)){
            std::cerr << "Opened Font\n";
            return true;
        }
       
    }
    return false;
}

void Game::initRectangles(const std::vector<RectangleConfig>& rConfig)
{
    for(const auto& rc : rConfig)
    {
        sf::Vector2f rectSize{rc.width, rc.height};
        Rectangle rect(rectSize, rc.shapeName, rc.position, rc.velocity, rc.color);
        m_rectangles.push_back(rect);
    }
}

void Game::initCircles(const std::vector<CircleConfig>& cConfig)
{
    for(const auto& c : cConfig)
    {
        Circle circle(c.radius, c.color, c.position, c.velocity, c.shapeName);
        m_circles.push_back(circle);
    }
}