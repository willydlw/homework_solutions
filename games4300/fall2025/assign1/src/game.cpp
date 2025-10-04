#include "game.h"

#include <cmath>        // floor
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
    initShapeMap();
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


void Game::initShapeMap(void)
{
    for(size_t i = 0; i < m_circles.size(); i++)
    {
        std::string key = m_circles[i].m_name; 
        ShapeObject val;
        val.circptr = &m_circles[i];
        m_shapeMap[key] = val;
    }

    for(size_t i = 0; i < m_rectangles.size(); i++)
    {
        std::string key = m_rectangles[i].m_name; 
        ShapeObject val;
        val.rectptr = &m_rectangles[i];
        m_shapeMap[key] = val;
    }
}

void Game::initShapeNames(void)
{
    for(const auto& shape : m_circles)
    {
        m_shapeNames.push_back(shape.m_name.c_str());
    }

    for(const auto& shape : m_rectangles)
    {
        m_shapeNames.push_back(shape.m_name.c_str());
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

    
        //static const char* current_item_preview = "Select an item";
        //static int selected_item_index = -1;

        #if 0
        //static int combo_item_width = (int)(strlen(current_item_preview) + 5) * m_gameConfig.m_fontConfig.fontSize;

        static int printCount = 0;
        if(printCount == 0)
        {
            std::cerr << "\ncombo box item width: " << combo_item_width << "\n";
            printCount++;
        }
        #endif
        

        static int selectedItem = -1;

        ImGui::Begin("Shape Properties");
        for(int i = 0; i < (int)m_shapeNames.size(); ++i)
        {
            bool isSelected = (selectedItem == i);
            if(ImGui::Selectable(m_shapeNames[i], &isSelected))
            {
                selectedItem= i;
            }
        }

        #if 0
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
        #endif 

        #if 0
        if(selected_item_index != -1)
        {
            const char* name = m_shapeNames[selected_item_index];
            ShapeObject so = m_shapeMap[name];

            ImGui::Text("Properties for %s", so.circptr->m_name);
            uint8_t sfmlColors[4] = {temp->color.r, temp->color.g, temp->color.b, temp->color.a};
            float guiColors[4] = {temp->color.r/255.0f, temp->color.g/255.0f, temp->color.b/255.0f, temp->color.a/255.0f};
            
            static int printCount = 0;
            if(printCount == 0)
            {
                std::cerr << "SFML Colors for Shape " << name << "\n";
                for(int i = 0; i < 4; i++)
                {
                    std::cerr << (int) sfmlColors[i] << " ";
                }
                std::cerr << "\n";
                printCount++;
            }
            ImGui::ColorEdit4("Color", guiColors);
            sf::Color updatedColor = floatColorToUint(guiColors);
            temp->color = updatedColor;
            //ImGui::Checkbox("Draw", &temp->drawable);
            //ImGui::SliderFloat("Velocity x", &temp->velocity.x, 0.0f, 10.0f);
        }

        #endif

        //ImGui::PopItemWidth();

        ImGui::End();
        #endif

        update();

        m_window.clear(sf::Color::White);
        draw(); 
        ImGui::SFML::Render(m_window); // draw the UI last so its on top
        m_window.display();
    }
}

sf::Color Game::floatColorToUint(float fcolors[4])
{
    uint8_t converted[4];

    for(int i = 0; i < 4; i++)
    {
        converted[i] = (uint8_t)floor(fcolors[i] * 255.0f);
    }

    return sf::Color{converted[0], converted[1], converted[2], converted[3]};
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