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
    initShapeIds();
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
        std::string key = m_circles[i].m_id; 
        ShapeObject val;
        val.circptr = &m_circles[i];
        m_shapeMap[key] = val;
    }

    for(size_t i = 0; i < m_rectangles.size(); i++)
    {
        std::string key = m_rectangles[i].m_id; 
        ShapeObject val;
        val.rectptr = &m_rectangles[i];
        m_shapeMap[key] = val;
    }
}

void Game::initShapeIds(void)
{
    for(const auto& shape : m_circles)
    {
        m_shapeIds.push_back(shape.m_id.c_str());
    }

    for(const auto& shape : m_rectangles)
    {
        m_shapeIds.push_back(shape.m_id.c_str());
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

        // update imgui for this frame with the time that the last frame took
        ImGui::SFML::Update(m_window, m_deltaClock.restart());

        updateGui();
        updateShapes();

        m_window.clear(sf::Color::White);
        drawShapes(); 
        ImGui::SFML::Render(m_window); // draw the UI last so its on top
        m_window.display();
    }
}


void Game::updateGui()
{
        static constexpr size_t NAME_BUFFER_SIZE = 255;

        if(ImGui::Begin("Shape Properties"))
        {
            static int selectedItem= 0;
            static bool selectedDrawShape = true;
            
            static std::string selectedId = m_shapeIds[selectedItem];
            static ShapeObject selectedObject = m_shapeMap[selectedId];
            static sf::Color selectedColor = selectedObject.circptr->getColor();
            static float guiColors[3] = { 
                (float)selectedColor.r/255.0f, 
                (float)selectedColor.g/255.0f, 
                (float)selectedColor.b/255.0f};
            static sf::Vector2f selectedVelocity = selectedObject.circptr->m_velocity;
            static sf::Vector2f selectedScale = selectedObject.circptr->getScale();
            static std::string selectedDisplayName = selectedObject.circptr->getDisplayName();
            static char objectName[NAME_BUFFER_SIZE+1];
            strcpy(objectName, selectedDisplayName.c_str());


            // Combo box provides drop down list of selectable shape names
            // Shape names argument must be of type: const char* items[] 
            // get a pointer to underlying array 
            const char* const* c_style_shape_names_ptr = m_shapeIds.data();

            // Because object velocities can change when they reach the window 
            // boundaries, we need to update the selected object velocity 
            selectedVelocity = selectedObject.circptr->m_velocity;
        
            if(ImGui::Combo("Id", &selectedItem, c_style_shape_names_ptr, (int)m_shapeIds.size()))
            {
                // executes when an item is selected
                selectedId = m_shapeIds[selectedItem];
                selectedObject = m_shapeMap[selectedId];
                selectedColor = selectedObject.circptr->getColor();
                selectedDrawShape = selectedObject.circptr->m_drawState;
                selectedVelocity = selectedObject.circptr->m_velocity;
                selectedScale = selectedObject.circptr->getScale();
                selectedDisplayName = selectedObject.circptr->m_displayName;
                strcpy(objectName, selectedDisplayName.c_str());
                
                sfColorToFloat(selectedColor, guiColors);   // convert sfml uint to imgui float
            }


            // returns true only when user has interacted with color editor
            if(ImGui::ColorEdit3("Color", guiColors))
            {
                // Scale the color picker float values to SFML uint8_t color values
                sf::Color updatedColor = floatColorToUint(guiColors);
                
                // Update the shape object's fill color
                selectedObject.circptr->setColor(updatedColor);
                
                // update gui variable with color selected
                selectedColor.r = guiColors[0];
                selectedColor.g = guiColors[1];
                selectedColor.b = guiColors[2];

                //printColor(guiColors, 3);
                //printColor(updatedColor);   
            }

            if(ImGui::Checkbox("Draw Shape", &selectedDrawShape))
            {
                if(selectedDrawShape)
                {
                    selectedObject.circptr->m_drawState = true;
                }
                else{
                    selectedObject.circptr->m_drawState = false;
                }
            }

            // SliderFloat2 creates two sliders for two dimensions (x,y)
            if(ImGui::SliderFloat2("Velocity", &selectedVelocity.x, MIN_VELOCITY, MAX_VELOCITY, "%.2f"))
            {
                selectedObject.circptr->m_velocity = selectedVelocity;
            }

            if(ImGui::SliderFloat("Scale", &selectedScale.x, MIN_SCALE, MAX_SCALE, "%.2f"))
            {
                selectedObject.circptr->setScale({selectedScale.x, selectedScale.x});
            }

            if(ImGui::InputText("Text", objectName, NAME_BUFFER_SIZE))
            {
                selectedObject.circptr->setDisplayName(objectName);
                selectedDisplayName = objectName;
            }        

            ImGui::End();
        }
}

sf::Color Game::floatColorToUint(float fcolors[3])
{
    uint8_t converted[3];

    for(int i = 0; i < 3; i++)
    {
        converted[i] = (uint8_t)floor(fcolors[i] * 255.0f);
    }

    return sf::Color{converted[0], converted[1], converted[2]};
}

void Game::sfColorToFloat(sf::Color color, float fcolors[3])
{
    fcolors[0] = (float)color.r/255.0f;
    fcolors[1] = (float)color.g/255.0f;
    fcolors[2] = (float)color.b/255.0f;
}


void Game::updateShapes()
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

void Game::drawShapes()
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


void Game::printColor(const sf::Color& color)
{
    std::cerr << "r: " << (int)color.r 
            << ", g: " << (int)color.g
            << ", b: " << (int)color.b
            << ", a: " << (int)color.a
            << "\n";
}

void Game::printColor(const float* color, int n)
{
    std::ios_base::fmtflags oldFlags = std::cerr.flags();
    std::cerr << std::fixed << std::setprecision(4);

    std::cerr << "Floating point colors\n";
    for(int i = 0; i < n; i++)
    {
        std::cerr << "\ti: " << color[i] << "\n";
    }

    std::cerr.flags(oldFlags);
}