/* Action Class

    Store the type of action the the player wants the scene to perform 

    All user input will be handled within the GameEngine class, where 
    Actions will be created and sent to the Scenes to have their logic 
    carried out

    The Scene will then have a doAction function which performs logic 
    based on a specific Action object

    Actions will be given a name (jump, left, etc)
    Actions input via keyboard or controller will have two phases: press 
    and release, which will typically denote the start and end of action
    Action will then have two main variables:
        Name: name of the action (jump, shoot, etc)
        Type: START or END

    Action Start = Press button
    Action End = Release button 

    Example: Press button, action RIGHT, player starts running right 
    and keeps moving right until the button is released
    
    Mapping Keys to Actions 
    Specify which user input (ex: keyboard key) maps to a specific Action object 
    In SFML, all keyboard keys have corresponding integer values 
    We'll use a std::map<int, std::string>
        int : SFML key code 
        string: name of action to be performed

    Mapping Keys to Actions 
        Scene base class will store this map: std::map<int, string> m_actionMap;
        To register (map) a key to an Action, we create a function 
        registerAction(int string) which will insert the action name into the map 
            m_actionMap[inputKey] = actionName
*/

#pragma once 

#include "Entity.hpp"
#include <string>
#include <sstream>

class Action
{
    private:
    
    std::string m_name = "NONE";
    std::string m_type = "NONE";

    public:

    Action() = default;
    Action(const std::string& name, const std::string& type) 
        : m_name(name), m_type(type) {}

    const std::string& name() const { return m_name; }
    const std::string& type() const { return m_type; }

};

// Action Registration 
void Scene_Menu::init()
{
    registerAction(sf::Keyboard::W,  "UP");
    registerAction(sf::Keyboard::S,  "DOWN");
    registerAction(sf::Keyboard::D,  "PLAY");
    registerAction(sf::Keyboad::Escape, "QUIT");
}

void Scene::registerAction(int inputKey, const std::string& aName)
{
    // if aName is already in the map (rebinding keys), we may 
    // want to remove that. Example: have already stored W as Jump action 
    // and now user wants to use space bar as Jump. It is a game design 
    // decision whether we want one or multiple keys performing the same action
    m_actionMap[inputKey] = aName;
}

/* Create Action Objects 

    GameEngine class will handle the actual user input key presses and 
    construct the Action to send to the current Scene

    When a key is pressed, the GameEngine will ask the Scene if it has 
    an action name associated wiht the key's integer value

    If the Scene has an associated Action, we create an Action object 
    wiht the correct Name and Type.
*/

if(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
{
    // SFML 3 will require this to be split into two if statements: one for press, 
    // another for release 
    if(currentScene()->getActionMap().find(event.key.code)) == 
        currentScene()->getActionMap().end())
        {
            continue; // Scene doe not have anything associated
        }

        // determine start or endo action by whether it was key press or release 
        const std::string actionType = (event.type == sf::Event::KeyPressd): "START" : "END";

        // look up the action  and send the action to the scene 
        Action action(currentScene()->getActionMap().at(event.key.code), actionType);
        currentScene()->doAction(action);
}

/* Doing Scene Actions 

    GameEngine sends the constructed Action object to the Scene to have its logic performed 
    This is done in the derived Scene class's sDoAction(const Action& action) function 

*/

void Scene_Menu::sDoAction(const Action& action)
{
    if(action.type() == "START")
    {
        if(action.name() = "UP")
        {
            if(m_selecteMenuIndex > 0) { m_selectedMenuIndex--;}
            else { m_selectedMenuIndex = m_menuStrings.size() - 1; }
        }
        else if(action.name() == "DOWN")
        {
            m_selectedMenuIndex = (m_selectedMenuIndex + 1) % m_menuStrings.size();
        }
        else if(action.name() == "PLAY")
        {
            m_game.changeScene("PLAY", std::make_shared<Scene_Play>(
                    m_game, m_levelPaths[m_selectedMenuIndex]));
        }
        else if(action.name() == "QUIT")
        {
            onEnd();
        }
    }
}