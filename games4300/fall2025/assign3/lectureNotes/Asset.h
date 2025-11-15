/*  Asset Management 
    - Assets are external files that are loaded into memory to be used in the game 
    - For our games, assets will be 
        - Textures (image files: .png, .jpg)
            png files are compressed, lossless and can support transparency
        - Animations (textures + bookeeping)
        - Sounds (sound files: .wav, .ogg)
        - Fonts (filetype: ttf)
    - Load once, use often
*/

/*  Assets Class

    - Want to load assets that are defined in an external configuration file 
        - Texture MegaMan textures/MMS.png 
        - Sound MegaDeath sounds/death.wav 
    - We can reference that asset via name:
        - m_assets->getTexture("Megaman");
        - m_assets->getSound("MegaDeath");
    - To implement this, the Asset class will use a std::map<std::string, AssetType>
*/

/*  Lives inside the GameEngine class 
    Initialized inside GameEngine init()
    Accessed via Scene's pointer to GameEngine
        - m_game->getAssets()

    Assets loaded once at beginning of program
*/

class Assets
{
    // data
    std::map<std::string, sf::Texture>
    std::map<std::string, Animation>
    std::map<std::string, sf::Sound>
    std::map<std::string, sf::Font>

    // functions 
    void addTexture(name, path)
    void addSound(name, path);
    void addFont(name, path);
    void addAnimation(name, Animation);

    sf::Texture& getTexture(name);
    sf::Sound& getSound(name);
    sf::Font& getFont(name);
    Animation& getAnimation(name);
}