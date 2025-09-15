/* Code from lecture 4 */

#include <iostream>
#include <memory>  // std::shared_ptr
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>



//int main(int argc, char* argv[])
int main(void)
{
    // Create a new window of size w*h pixels
    // top-left of the window is (0,0) and bottom right is (w,h)
    // you will have to read these from the config file
    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "SFML works!");
    window.setFramerateLimit(60);

    // initialize imgui and create a clock used for its internal timing
    if(!ImGui::SFML::Init(window))
    {
        std::cerr << "ImGui::SFML::Init failure\n";
        std::exit(-1);
    }
    sf::Clock deltaClock;

    // scale the imgui ui and text by a given factor
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

    // the imgui color (r,g,b) wheel requires floats from 0-1 
    // sfml will require uint8_t from 0-255
    // this is the only really annoying conversion between sfml and imgui
    float c[3] = {0.0f, 1.0f, 1.0f};

    // let's make a shape that we will draw to the screen
    float circleRadius = 50;    // radius to draw the circle
    int circleSegments = 32;    // number of segments to draw the circle with
    float circleSpeedX = 1.0f;  // used to move circle
    float circleSpeedY = 0.5f;  // you will read speed from file 
    bool drawCircle = true;     // whether or not to draw the circle
    bool drawText = true;       // whether of not to draw the text 

    // create the sfml circle shape based on our parameters
    sf::CircleShape circle(circleRadius, circleSegments);
    circle.setPosition({10.0f, 10.0f});   // set top-left position
    
    // let's load a font so we can display some text
    sf::Font myFont;

    // attempt to load the font from a file
    if(myFont.openFromFile("/fonts/tech.ttf"))
    {
        std::cerr << "Failed to load font\n";
        //std::exit(-1);
    }

    // set up the text object that will be drawn to the screen
    sf::Text text(myFont);
    text.setString("Sample Text");
    text.setCharacterSize(24);
    
    // position the top-left corner of the text so that the text aligns on the bottom
    // text character size is in pixels, so move the text up from
    // the bottom by its height
    text.setPosition({0, wHeight - (float)text.getCharacterSize()}); 

    // set up a character array to set the text
    // Any text typed in UI text box should be stored here
    char displayString[255] = "Sample Text";

    // main loop - continues for each frame while window is open
    while(window.isOpen())
    {
        // event handling
        while(auto event = window.pollEvent())
        {
            // pass the event to imgui to be parsed 
            ImGui::SFML::ProcessEvent(window, *event);

            // this event triggers when window is closed
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // this event triggers when a key is pressed
            if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                std::cout << "Key pressed with scancode = " << static_cast<int>(keyPressed->scancode) << "\n";

                // example, what happens whe x is pressed
                if(keyPressed->scancode == sf::Keyboard::Scan::X)
                {
                    circleSpeedX *= -1.0f;
                }   
            }
        }

            // update imgui for this frame with the time that the last frame took
            ImGui::SFML::Update(window, deltaClock.restart());

            // draw the UI
            ImGui::Begin("Window title");
            ImGui::Text("Window text!");
            ImGui::Checkbox("Draw Circle", &drawCircle);
            ImGui::SameLine();
            ImGui::Checkbox("Draw Text", &drawText);
            ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
            ImGui::SliderInt("Sides", &circleSegments, 3, 64);
            ImGui::ColorEdit3("Color Circle", c);
            ImGui::InputText("Text", displayString, 255);
            if(ImGui::Button("Set Text"))
            {
                text.setString(displayString);
            }
            ImGui::SameLine();
            if(ImGui::Button("Reset Circle"))
            {
                circle.setPosition({0,0});
            }
            ImGui::End();

            // set the circle properties, because they have been updated with the ui
            circle.setFillColor(sf::Color(c[0]*255,c[1]*255, c[2]*255));
            circle.setPointCount(circleSegments);
            circle.setRadius(circleRadius);

            // basic animation - move the each frame if it's still in frame
            circle.setPosition({circle.getPosition().x + circleSpeedX, 
                circle.getPosition().y + circleSpeedY});

            // basic rendering function calls
            window.clear();     
            if(drawCircle)
            {
                window.draw(circle);
            }
            if(drawText)
            {
                window.draw(text);
            }

            ImGui::SFML::Render(window); // draw the UI last so its on top

            window.display();
    }
    return 0;
}
