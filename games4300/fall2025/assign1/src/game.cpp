#include "game.h"

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

    TextConfig textConfig(m_font, gc->font.fontSize, gc->font.color);

    initRectangles(gc->rects, &textConfig);
    initCircles(gc->circles, &textConfig);
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

void Game::initRectangles(  const std::vector<RectangleConfig>& rConfig,
                            const TextConfig* textConfig)
{
    for(const auto& rc : rConfig)
    {
        Rectangle rect(&rc, textConfig);
        m_rectangles.push_back(rect);
    }
}

void Game::initCircles( const std::vector<CircleConfig>& circleConfig, const TextConfig* textConfig)
{
    for(const auto& c : circleConfig)
    {
        Circle circle(&c, textConfig);
        m_circles.push_back(circle);
    }
}



void Game::update(const sf::Vector2u& boundary)
{
    static int count = 0;
    if(count == 0){
         std::cerr << "TODO: complete function: " << __func__ << std::endl;
         std::cerr << "display text on objects\n";
         count++;
    }

    for(auto& r : m_rectangles)
    {
        r.update(boundary);
    }

    for(auto& c: m_circles)
    {
        c.update(boundary);
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