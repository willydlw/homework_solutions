#include "Scene_Menu.h"
#include "Scene_Play.h"
#include <iostream>
#include <memory>


/* SFML 3.0.x class sf::Text has no default constructor which is 
   why we must initialize the data member with a font reference 
   in the constructor
*/
Scene_Menu::Scene_Menu(GameEngine* gameEngine) 
    : Scene(gameEngine)  // call base class constructor
    , m_title("Menu")    // initialize derived class members
    , m_menuText(Assets::Instance().getFont("Mario"))
{
    init();
}

void Scene_Menu::init()
{
    registerAction(static_cast<int>(sf::Keyboard::Key::W),  "UP");
    registerAction(static_cast<int>(sf::Keyboard::Key::S),  "DOWN");
    registerAction(static_cast<int>(sf::Keyboard::Key::D),  "PLAY");
    registerAction(static_cast<int>(sf::Keyboard::Key::Escape), "QUIT");

    // defining local variables for readability and to avoid multiple function calls
    int titleSize = 30;
    int centerX = m_game->window().getSize().x / 2;

    // initialize menu data
    m_title = "TODO: Scene Menu Title";
    m_menuStrings.push_back("LEVEL 1");
    m_menuStrings.push_back("LEVEL 2");
    m_menuStrings.push_back("LEVEL 3");
    m_levelPaths.push_back("config/level1.txt");
    m_levelPaths.push_back("config/level2.txt");
    m_levelPaths.push_back("config/level3.txt");

    // set up text attributes
    m_menuText.setString(m_title);
    m_menuText.setCharacterSize(titleSize);
    m_menuText.setFillColor(sf::Color::Red);

    // position title
    m_menuText.setPosition(
        { static_cast<float>(centerX - titleSize * (m_title.length() + 1) / 2),
          static_cast<float>(titleSize * 3)
        }
    );

    /* Returned rectangle is in global coordinates, which means it takes into 
       account any transformations, rotations, scaling, ... that are applied 
       to the entity;

       Returns global bounding rectangle of the entity
    */
    sf::FloatRect gBounds = m_menuText.getGlobalBounds();
    auto gPosition = gBounds.position;
   
    // set up menu items
    for(size_t i = 0; i < m_menuStrings.size(); i++)
    {
        sf::Text text(
            Assets::Instance().getFont("Mario"),
            m_menuStrings[i], 26);

        if(i != m_selectedMenuIndex)
        {
            text.setFillColor(sf::Color::Black);
        }
        
        text.setPosition( 
            { static_cast<float>(centerX - 26 * (m_menuStrings[i].length() + 1) / 2),
              static_cast<float>(gPosition.y + 10 + titleSize * (i + 1))
            }
        );

        m_menuItems.push_back(text);
    }
}

void Scene_Menu::update()
{
    sRender();
}

void Scene_Menu::onEnd()
{
    std::cerr << "Entering function " << __PRETTY_FUNCTION__ << "\n";
    m_game->quit();
}


/* Doing Scene Actions 

    GameEngine sends the constructed Action object to the Scene to have its logic performed 
    This is done in the derived Scene class's sDoAction(const Action& action) function 

*/

void Scene_Menu::sDoAction(const Action& action)
{
    if(action.type() == "START")
    {
        if(action.name() == "UP")
        {
            if(m_selectedMenuIndex > 0) { 
                m_selectedMenuIndex--;
            }
            else { 
                m_selectedMenuIndex = m_menuStrings.size() - 1; 
            }
        }
        else if(action.name() == "DOWN"){
            m_selectedMenuIndex = (m_selectedMenuIndex + 1) % m_menuStrings.size();
        }
        else if(action.name() == "PLAY"){
            m_game->changeScene("PLAY", 
                std::make_shared<Scene_Play>(m_game, m_levelPaths[m_selectedMenuIndex]));
        }
        else if(action.name() == "QUIT"){
            onEnd();
        }
    }
}

void Scene_Menu::sRender()
{
    // set menu background 
    m_game->window().clear(sf::Color::Blue);
 
    // draw title 
    m_game->window().draw(m_menuText);
    
    // draw menu items 
    for(size_t i = 0; i < m_menuStrings.size(); i++)
    {
        if(i != m_selectedMenuIndex)
        {
            m_menuItems[i].setFillColor(sf::Color::Black);
        }
        else
        {
            m_menuItems[i].setFillColor(sf::Color::White);
        }
        
        auto gbounds = m_menuText.getGlobalBounds();
        auto top = gbounds.position.y;

        m_menuItems[i].setPosition( 
            { m_game->window().getSize().x / 2.0f 
            - 26 * (m_menuStrings[i].length() + 1) / 2.0f,
            top + 10 + 30 * (i+1)}
        );

        m_game->window().draw(m_menuItems[i]);
    }

    // draw help instructions 
    sf::Text help(Assets::Instance().getFont("Mario"),
        "W:UP  S:DOWN  D:PLAY  ESC:BACK/QUIT", 26);

    help.setFillColor(sf::Color::Black);
    help.setPosition(
        {m_game->window().getSize().x / 2.0f 
        - 26 * (help.getString().getSize() + 1) / 2.0f,
        m_game->window().getSize().y - 30 * 2.0f}
    );

    m_game->window().draw(help);
}