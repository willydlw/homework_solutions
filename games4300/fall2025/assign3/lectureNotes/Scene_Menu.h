class Scene_Menu : public Scene 
{
    std::vector<std::string> menuStrings;
    sf::Text menuText;
    std::vector<std::string> levelPaths;
    int menuIndex;

    void init();
    void update();

    // systems
    void sRender();
    void sDoAction(action);
};