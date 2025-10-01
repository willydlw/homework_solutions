#include "game.h"

#include <iomanip>


Game::Game(){/* intentionally blank */}

void Game::init(const GameConfig *gc)
{
    std::string fontFilePath;
    fontFilePath = initFont(gc->font.fileName);
    if(fontFilePath.empty())
    {
        std::cerr << "ERROR, failed to open font: " << gc->font.fileName
                << "\n";
        std::exit(-1);
    }

    TextConfig textConfig{gc->font.fontSize, gc->font.color};

    initRectangles(gc->rects, textConfig);
    initCircles(gc->circles, textConfig);
    initShapeNameList();
}

void Game::initShapeNameList(void)
{
    for(auto& shape : m_circles)
    {
        shapeNames.push_back(shape.getName());
    }
}


std::string Game::initFont(const std::string& fileName)
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
        return "";
    }

    for(const auto &found : foundFontFiles){
    
        if(m_font.openFromFile(found)){
            return found;
        }
        else{
            std::cerr << "WARNING function: " << __func__ 
                << " failed to open font file: " 
                << found << "\n";
        }
    }
    return "";
}

void Game::initRectangles(  const std::vector<RectangleConfig>& rectConfig,
                            const TextConfig& textConfig)
{
    for(auto rc : rectConfig)
    {
        Rectangle rect(rc, rc.shapeConfig, m_font, textConfig);
        m_rectangles.push_back(rect);
    }
}

void Game::initCircles( const std::vector<CircleConfig>& circleConfig, const TextConfig& textConfig)
{
    for(auto cc : circleConfig)
    {
        Circle circle(cc, cc.shapeConfig, m_font, textConfig);
        m_circles.push_back(circle);
    }
}



void Game::update(const sf::Vector2u& boundary)
{
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