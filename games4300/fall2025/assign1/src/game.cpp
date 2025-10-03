#include "game.h"

#include <iomanip>

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
    initGui();
    initShapeList();
    initShapeNames();
    std::cerr << "[INFO] exiting function: " << __PRETTY_FUNCTION__ << "\n";
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


void Game::initShapeList(void)
{
    for(size_t i = 0; i < m_circles.size(); i++)
    {
        Shape* shapePtr = (Shape*)&(m_circles[i]);
        m_guiShapeList.push_back(shapePtr);
    }

    for(size_t i = 0; i < m_rectangles.size(); i++)
    {
        Shape* shapePtr = (Shape*)&(m_rectangles[i]);
        m_guiShapeList.push_back(shapePtr);
    }
}

void Game::initShapeNames(void)
{
    for(const auto& shape : m_circles)
    {
        m_shapeNames.push_back(shape.name.c_str());
    }

    for(const auto& shape : m_rectangles)
    {
        m_shapeNames.push_back(shape.name.c_str());
    }
}


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
    std::cerr << "[INFO] entering function: " << __PRETTY_FUNCTION__ << "\n";

    while(m_window.isOpen()){
        while(auto event = m_window.pollEvent()){
            
            #if 1
            // pass the event to imgui to be parsed 
            ImGui::SFML::ProcessEvent(m_window, *event);
            #endif 

            if(event->is<sf::Event::Closed>()){
                m_window.close();
            }
        }

        #if 1
        // update imgui for this frame with the time that the last frame took
        ImGui::SFML::Update(m_window, m_deltaClock.restart());

    
        static const char* current_item_preview = "Select an item";
        static int selected_item_index = -1;
        static int combo_item_width = (int)(strlen(current_item_preview) + 5) * m_gameConfig.m_fontConfig.fontSize;

        static int printCount = 0;
        if(printCount == 0)
        {
            std::cerr << "\ncombo box item width: " << combo_item_width << "\n";
            printCount++;
        }
        

        ImGui::Begin("Shapes");
        ImGui::PushItemWidth(combo_item_width);
        // ## causes the widget label to be hidden and have a unique id
        if(ImGui::BeginCombo("##ShapesList", current_item_preview))
        {
            for(int i = 0; i < (int)m_shapeNames.size(); i++)
            {
                bool is_selected = (selected_item_index == i);
                if(ImGui::Selectable(m_shapeNames[i], is_selected))
                {
                    selected_item_index = i;
                    current_item_preview = m_shapeNames[i];
                }

                // Set the initial focus for keyboard navigation 
                if(is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        ImGui::PopItemWidth();

        ImGui::End();
        #endif

        update();

        m_window.clear(sf::Color::White);
        draw(); 
        ImGui::SFML::Render(m_window); // draw the UI last so its on top
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
    for(const auto& r : m_rectangles)
    {
        m_window.draw(r);
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