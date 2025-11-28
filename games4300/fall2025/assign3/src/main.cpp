#include <iostream>

#include "GameEngine.h"

int main()
{
    GameEngine ge("resources/config/assets.txt");
    ge.run();
    return 0;
}

#if 0
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


#endif 