#include "Scene.h"

void Scene::registerAction(int inputKey, const std::string& aName)
{
    // if aName is already in the map (rebinding keys), we may 
    // want to remove that. Example: have already stored W as Jump action 
    // and now user wants to use space bar as Jump. It is a game design 
    // decision whether we want one or multiple keys performing the same action
    m_actionMap[inputKey] = aName;
}