#include "game.hpp"

#include <iomanip>


Game::Game(){/* intentionally blank */}

void Game::init(const GameConfig *gc)
{
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
    
        if(m_font.openFromFile(found)){
            return true;
        }
        else{
            std::cerr << "ERROR  function: " << __func__ 
                << " failed to open font file: " 
                << found << "\n";
            return false;
        }
    }
    return false;
}

void Game::initRectangles(const std::vector<RectangleConfig>& rConfig)
{
    for(const auto& rc : rConfig)
    {
        sf::Vector2f rectSize{rc.width, rc.height};
        Rectangle rect(rectSize, rc.position, rc.velocity, rc.color, rc.shapeName);
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



void Game::update(void)
{
    static int count = 0;
    if(count == 0){
         std::cerr << "TODO: complete function: " << __func__ << std::endl;
         count++;
    }
    
   
}

void Game::draw(sf::RenderWindow& window)
{
    for(const auto& r : m_rectangles)
    {
        window.draw(r);
    }

    for(const auto& c : m_circles)
    {
        window.draw(c);
    }
}


std::ostream& operator << (std::ostream& os, const Game& obj)
{
    std::ios_base::fmtflags oldFlags = os.flags();

    os << "**** Rectangle Data ***\n\n";
    for(const auto& r : obj.m_rectangles){
        os << r << "\n";
    }
    os << "**** End Rectangle Data\n\n";

    os << "**** Circle Data ***\n\n";
    for(const auto& c : obj.m_circles){
        os << c << "\n";
    }
    os << "**** End Circle Data\n\n";

    os.flags(oldFlags);
    return os;
}