#include "game.h"

#include <iomanip>
#include <optional>


Game::Game(){/* intentionally blank */}

void Game::init(const std::string& configFileName)
{
    if(m_gameConfig.readConfigFile(configFileName) == false)
    {
        std::cerr << "[FATAL] function: " << __PRETTY_FUNCTION__ 
            << " reading game configuration. Terminating ...\n";
        std::exit(-1);
    }

    initWindow();

    std::string fontFilePath;
    fontFilePath = initFont(m_gameConfig.m_fontConfig.fileName);
    if(fontFilePath.empty())
    {
        std::cerr << "ERROR, failed to open font: " 
                << m_gameConfig.m_fontConfig.fileName
                << "\n";
        std::exit(-1);
    }

   
    initRectangles();
    initCircles();
    std::cerr << "[INFO] exiting function: " << __PRETTY_FUNCTION__ << "\n";
    //initShapeNameList();
}

void Game::initWindow(void)
{
    m_window = sf::RenderWindow(sf::VideoMode(
        {m_gameConfig.m_windowConfig.width, m_gameConfig.m_windowConfig.height}), 
        "Assign 1");
    m_window.setFramerateLimit(FRAME_RATE);
}

void Game::initGui(void)
{
    if(!ImGui::SFML::Init(m_window))
    {
        std::cerr << "ImGui::SFML::Init failure\n";
        std::exit(-1);
    }
    

    // scale the imgui ui and text by a given factor
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;
}

#if 0
void Game::initShapeNameList(void)
{
    for(auto& shape : m_circles)
    {
        shapeNames.push_back(shape.getName());
    }
}
#endif


std::string Game::initFont(const std::string& fileName)
{
    // Get the current working directory
    std::filesystem::path workingDirPath = m_gameConfig.getWorkingDirectory();

    // Search for font file in current working directory
    std::vector<std::filesystem::path> foundFontFiles;
    foundFontFiles = m_gameConfig.findFileRecursive(workingDirPath, fileName);

    if(foundFontFiles.empty()){
        std::cerr << "[ERROR] function: " << __PRETTY_FUNCTION__
            << " failed to find file: " << fileName 
            << " in working directory: " << workingDirPath 
            << "\n";
        return "";
    }

    for(const auto &found : foundFontFiles){
    
        if(m_font.openFromFile(found)){
            return found;
        }
        else{
            std::cerr << "[WARNING] function: " << __PRETTY_FUNCTION__
                << " failed to open font file: " 
                << found << "\n";
        }
    }
    return "";
}

void Game::initRectangles(void)
{
    TextConfig textConfig = {m_gameConfig.m_fontConfig.fontSize, m_gameConfig.m_fontConfig.color};

    for(auto rc : m_gameConfig.m_rectConfig)
    {
        Rectangle rect(rc, m_font, textConfig);
        m_rectangles.push_back(rect);
    }
}

void Game::initCircles(void)
{
    TextConfig textConfig = {m_gameConfig.m_fontConfig.fontSize, m_gameConfig.m_fontConfig.color};
    for(auto cc : m_gameConfig.m_circleConfig)
    {
        Circle circle(cc, m_font, textConfig);
        m_circles.push_back(circle);
    }
}


void Game::run(void)
{
    static int count = 0;
    std::cerr << "[INFO] entering function: " << __PRETTY_FUNCTION__ << "\n";

    while(m_window.isOpen()){
        while(const std::optional event = m_window.pollEvent()){
            
            #if 0
            // pass the event to imgui to be parsed 
            ImGui::SFML::ProcessEvent(window, *event);
            #endif 

            if(event->is<sf::Event::Closed>()){
                m_window.close();
            }
        }

        #if 0
        // update imgui for this frame with the time that the last frame took
        ImGui::SFML::Update(window, deltaClock.restart());

        // Update from UI elements
        ImGui::Begin("Shapes List");
        
        for(int i = 0; i < (int)game.shapeNames.size(); i++)
        {
            if(ImGui::Selectable(game.shapeNames[i].c_str(), selectedItem == i))
            {
                selectedItem = i;
                std::cerr << "selected shape: " << game.shapeNames[i] << "\n";
            }
        }
       
        ImGui::End();
        #endif

        if(count == 0)
        { std::cerr << "Calling window.clear()\n";
        }

        update();

        m_window.clear(sf::Color::White);
        
        draw();

        #if 0
        ImGui::SFML::Render(window); // draw the UI last so its on top
        #endif 

        if(count == 0)
        {
            std::cerr << "calling window.display()\n";
            count += 1;
        }

        m_window.display();
    }
}


void Game::update(void)
{
    sf::Vector2u boundary = m_window.getSize();

    for(auto& r : m_rectangles)
    {
        r.update(boundary);
    }

    for(auto& c: m_circles)
    {
        c.update(boundary);
    }
}

void Game::draw(void)
{
    static int count = 0;

    for(const auto& r : m_rectangles)
    {
        if(count == 0)
        {
            std::cerr << "Preparing to draw rectangle:\n";
        }
        m_window.draw(r);
    }

    if(count == 0){
        count++;
    }

    for(const auto& c : m_circles)
    {
        m_window.draw(c);
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