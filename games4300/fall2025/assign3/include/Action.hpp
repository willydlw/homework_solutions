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

#ifndef A3_ACTION_H
#define A3_ACTION_H

#include <string>


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

#endif // ACTION_H