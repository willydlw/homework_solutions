#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include "Action.hpp"
#include "GameEngine.h"
#include "Scene.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>


class Scene_Menu : public Scene 
{

protected:

    std::string                 m_title;
    sf::Text                    m_menuText; 
    std::vector<std::string>    m_menuStrings;
    std::vector<std::string>    m_levelPaths;
    std::vector<sf::Text>       m_menuItems;
    size_t                      m_selectedMenuIndex = 0;

    void init();
    void update() override;
    void onEnd()  override;
    void sDoAction(const Action& action) override;

public:

    explicit Scene_Menu(GameEngine* gameEngine = nullptr);
    void sRender() override;
};

#endif  // SCENE_MENU_H