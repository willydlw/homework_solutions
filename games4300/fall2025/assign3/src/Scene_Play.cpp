#include "Scene_Play.h"

#include "Assets.h"
#include "Components.hpp"
#include "EntityManager.hpp"

//#include "Physics.hpp"
//#include "Assets.h"
//#include "Components.hpp"
//#include "Action.hpp"

#include <iostream>

Scene_Play::Scene_Play(GameEngine& gameEngine, const std::string& levelPath)
    : Scene(gameEngine), m_levelPath(levelPath)
{
    init(m_levelPath);
}

void Scene_Play::init(const std::string& levelPath)
{
    registerAction(sf::Keyboard::Scancode::P, "PAUSE");
    registerAction(sf::Keyboard::Scancode::Escape, "QUIT");
    registerAction(sf::Keyboard::Scancode::T, "TOGGLE_TEXTURE");    // Toggle drawing Textures
    registerAction(sf::Keyboard::Scancode::C, "TOGGLE_COLLISION");  // Toggle drawing Collision Boxes
    registerAction(sf::Keyboard::Scancode::G, "TOGGLE_GRID");       // Toggle drawing Grid

    // TODO: Register all other gameplay actions
    std::cerr << "TODO function: " << __func__ << " register all other game play actions\n";

    loadLevel(levelPath);
}

Vec2f Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
    // TODO: This fucntion takes in a grid (x,y) position and an Entity 
    //  Return a Vec2 indicating where the CENTER position of the Entity should be 
    //  You must use the Entity's Animation size to position it correctly 
    //      entity->get<CAnimation>().getSize() 
    //  The size of the grid width and height is stored in m_gridSize.x and m_gridSize.y 
    //  The bottom left corner of the Animation should align with the bottom left of the grid cell.
    //
    //  Remember that SFML has (0,0) in the top left, while grid coordinates are specified 
    //  You can get the size of the SFML window via m_game.window().getSize();


    // The bottom-left of the Animation should align with the bottom-left of the specified 
    // from bottom to top
    // grid cell. Animation position specified by its center point.
    //  1) Calculate grid cell bottom-left (Be sure to account for the y-flip)
    //  2) Add AnimationSize/2 

    std::cerr << "TODO function: " << __func__ << " complete the calculations\n"
        << " currently returning 0,0 by default\n";

    std::cerr << "Parameters: gridX " << gridX << ", gridY " << gridY 
        << ", entity: " << *entity << "\n";

    Vec2f answer{0.0f, 0.0f};

    return answer;
}

void Scene_Play::loadLevel(const std::string& filename)
{
    // reset the entity manager every time we load a level 
    m_entityManger = EntityManager();

    // TODO: read in the level file and add the appropriate entities 
    //  use the PlayerConfig struct m_playerConfig to store player properties 
    
    // NOTE: all of the code below is sample code which shows you how to 
    // set up and use entities it should be removed 

    std::cerr << "TODO function: " << __func__ 
        << "\n\t1) read in the level file, parameter filename: " << filename 
        << "\n\t2) add the appropriate entities\n";
    
    std::cerr << "Current output is based on sample code which will be removed\n";

    spawnPlayer();

    // some sample entities 
    auto brick = m_EntityManager.addEntity("tile");

    // IMPORTANT: always add the CAnimation component first so that gridToMidPixel 
    // can compute correctly
    brick->add<CAnimation>(Assets::Instance().getAnimation("Brick"), true);
    brick->add<CTransform>(Vec2f(96.0f, 480,=.0f));

    // NOTE: Your final code should position the entity with hte grid x,y position read from
    // brick->add<CTransform>(gridToMidPixel(gridX, gridY, brick));

    if (brick->get<CAnimation>().animation.getName() == "Brick")
    {
        // This could be a good way of identifying if a tile is a brick!
        std::cout << "This could be a good way of identifying if a tile is a brick\n";
    }

    // Try changing "Block" to "Ground" to render the ground
    auto block = m_entityManager.addEntity("tile");
    block->add<CAnimation>(Assets::Instance().getAnimation("Block"), true);
    block->add<CTransform>(Vec2f(224, 480));
    // add a bounding box, this will now show up if we press the 'C' key
    block->add<CBoundingBox>(sf::Vector2f(Assets::Instance().getAnimation("Block"),getRect().size)

    auto question = m_entityManager.addEntity("tile");
    question->add<CAnimation>(Assets::Instance().getAnimation("Question"), true);
    question->add<CTransform>(Vec2f(352,480));
    
    // NOTE: THIS IS INCREDIBLY IMPORTANT PLEASE READ THIS EXAMPLE 
    //      Components are now returned as references rather than pointers 
    //      If you do not specify a reference variable type, it will COPY the component 
    //      Here is an example:
    //
    //      This will COPY the transform into the variable 'transform1' - it is INCORRECT 
    //      Any changes you make to transform1 will not be changed inside the entity.
    //      auto transform1 = entity->get<CTransform>() 
    //
    //      This will REFERENCE the transform with the variable 'transform2' - it is CORRECT
    //      Now any changes you make to transform2 will be changed inside the entity 
    //      auto& transform2 = entity->get<CTransform>()
}

void Scene_Play::spawnPlayer()
{
    std::cerr << "TODO function: " << __func__ 
        << "\n\tHere is a sample player entity which you can use to construct other entities\n";

    // check to see if a player already exists before adding a new one 
    // if it already exists, just overwrite the values of the existing one 
    if(!m_player) {m_player = m_entityManager.addEntity("player");}

    // here is a sample player entity which you can use to construct other entities 
    m_player->add<CAnimation>(Assets::Instance().getAnimation("Stand"), true);
    m_player->add<CTransform>(Vec2f(224, 352));
    m_player->add<CBoundingBox>(Vec2f(48,48));
    m_player->add<CState>("stand");
    m_player->add<CInput>();

    // TODO: be sure to add the remaining components to the player
    // NOTE: when setting component properties, read values from m_playerConfig
    std::cerr << "TODO be sure to add the remaining components to the player\n";
}


void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity)
{
    // TODO: this should spawn a bullet at the given entity 
    // going in the direction the entity is facing 
    std::cerr << "TODO function: " << __func__ << "\n";
    std::cerr << "Parameter entity: " << entity << "\n";
    std::cerr << "Add all code for spawning bullet\n";

}

void Scene_Play::update()
{
    m_entityManger.update();

    // TODO; implement pause functionality
    std::cerr << "TODO, function: " << __func__ << ", implements pause functionality\n";

    sMovement();
    sLifeSpan();
    sCollision();
    sAnimation();
    sGUI();
    sRender();

    std::cerr << "Where does m_currentFrame get incremented?\n";
}

void Scene_Play::sMovement()
{
    // TODO: implement player movement / jumping based on its CInput component 
    // TODO: implement gravity's effect on the player 
    // TODO: implement the maximum player speed in both x and y directions 
    // NOTE: setting an entity's scale.x to -1/1 will make it face to the left/right 

    std::cerr << "TODO function: " << __func__ << "\n";
    std::cerr << "TODO: implement player movement / jumping based on its CInput component\n" 
        << "TODO: implement gravity's effect on the player\n" 
        << "TODO: implement the maximum player speed in both x and y directions\n"
        << "NOTE: setting an entity's scale.x to -1/1 will make it face to the left/right\n";
}

void Scene_Play::sLifespan()
{
    // TODO: Check lifespan of entities that have them, and destroy them if they go over
    std::cerr << "TODO function " << __func__ << 
        << "\n\tcheck lifespan of entities and destroy those that are dead\n";
}

void Scene_Play::sCollision()
{
    // REMEMBER: SFML's (0,0) position is on the TOP-LEFT corner 
    //      This means jumping will have a negative y-component 
    //      and gravity will have a positive y-component 
    //      Also, something BELOW something else will have a y value greater than it 
    //      Also, something ABOVE something else will have a y value less than it 

    // TODO:  Implement Physics::GetOverlap() function, use it inside this function 

    // TODO: Implement bullet / tile collsions 
    //  Destroy the tile if it has a Brick animation 

    // TODO: Implement player / tile collisions 
    //  Update the CState component of the player to store whether 
    //  it is currently on the ground or in the air. This will be 
    //  used by the Animation system 

    // TODO: Check to see if the player has fallen down a hole (y > height())
    // TODO: Don't let the player walk off the left side of the map
    std::cerr << "TODO function " << __func__ << "\n\ttoo many collision checks to list here\n";

}

void Scene_Play::sDoAction(const Action& action)
{
    std::cerr << "TODO function " << __func__ << " test actions and add other actions\n";
    if(action.type() == "START")
    {
        if(action.name() == "TOGGLE_TEXTURE") { m_drawTexturess = !m_drawTextures;}
        else if(action.name() == "TOGGLE_COLLISION") { m_drawCollision = !m_drawCollision;}
        else if(action.name() == "TOGGLE_GRID") { m_drawGrid = !m_drawGrid;}
        else if(action.name() == "PAUSE") { setPaused(!m_paused);}
        else if(action.name() == "QUIT") { onEnd();}
        else if(action.name() == "RIGHT") { m_player->get<CInput>().right = true;}
        // TODO add other actions such as left, shoot, jump

    }
    else if(action.type() == "END")
    {
        // TODO: code values for end of actions 
        if(action.name() == "RIGHT") {m_player->get<CINPUT>().right = false;}
    }
}

void Scene_Play::sAnimation()
{
    // TODO: Complete the Animation class code first 

    // TODO: for each entity with an animation, call entity->get<CAnimation>().animation.update() 
    //  if the animation is not repeated, and it has ended, destroy the entity 

    // TODO: set the animation of the player based on its CState component 
    // if the player's state has be set to running
    if(m_player->get<CState>().state == "run")
    {
        // change ist animation to a repeating run animation 
        // note: adding a component that already exists simply overwrites it 
        m_player->add<CAnimation>(Assets::Instance().getAnimation("Run"), true);

        // Don't forget that if player has already been running this should not be set again 
    }

}

void Scene_Play::oneEnd()
{
    // TODO: When the scene ends, change back to the MENU scene 
    // use m_game.changeScene(correct params)
}

void Scene_Play::sGui()
{
    ImGui::Begin("Scene Properties");
    if(ImGui::BeginTabBar("MyTabBar"))
    {
        if(ImGui::BeginTabItem("Actions"))
        {
            for(const auto& [key, name] : getActionMap())
            {
                std::string ss = "START##" + name;
                std::string se = "END##" + name;

                if(ImGui::Button(ss.c_str()))
                {
                    doAction(Action(name, "START"));
                }
                ImGui::SameLine();
                if(ImGui::Button(se.c_str()))
                {
                    doAction(Action(name, "END"));
                }
                ImGui::SameLine();
                ImGui::Text("%s", name.c_str());
            }
            ImGui::EndTabItem();
        }

        if(ImGui::BeginTabItem("Assets"))
        {
            if(ImGui::CollapsingHeader("Animations", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Indent();
                int count = 0;
                for(const auto& [name, anim] : Assets::Instance().getAnimations())
                {
                    count++;
                    ImGui::ImageButton(name.c_str(), anim.getSprite(), sf::Vector2f(32,32));
                    if(count % 6) != 0 && count != Assets::Instance().getAnimations().size() 
                }
                ImGui::Unindent();
            }
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}


void Scene_Play::sRender()
{
    // color the background darker so that you know the game is paused 
    if(!m_paused) {m_game.window().clear(sf::Color(100, 100, 255));}
    else { m_game.window().clear(sf::Color(50, 50, 150));}

    sf::Text gridText(Assets::Instance().getFont("Tech"), "", 12);

    // set the viewport of the window to be centered on the player if it's far enough right 
    auto& pPos = m_player->get<CTransform>().pos;

    float windowCenterX = std::max(m_game.window().getSize().x / 2.0f, pPos.x);
    sf::View view = m_game.window().getView();
    view.setCenter({windowCenterX, m_game.window().getSize().y - view.getCenter().y});
    m_game.window().setView(view);   

    // draw all Entity textures / animations 
    if(m_drawTextures)
    {
        for(auto e : m_entityManger.getEntities())
        {
            auto & transform = e->get<CTransform>();

            if(e->has<CAnimation>())
            {
                sf::Sprite sprite = e->get<CAnimation>.animation.getSprite();
                sprite.setRotation(sf::degrees(tranform.angle));
                sprite.setPosition(transform.pos);
                sprite.setScale(transform.scale);

                m_game.window().draw(sprite);
            }
        }
    }

    // draw all Entity collsion bounding boxes with a rectangle shape 
    if(m_drawCollison)
    {
        for(auto e : m_entityManager.getEntities())
        {
            auto & transform = e->get<CTransform>();
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(box.size.x-1, box.size.y-1));
            rect.setOrigin(sf::Vector2f(box.halfSize.x, box.halfSize.y));
            rect.setPosition(transform.pos);
            rect.setFillColor(sf::Color(0,0,0,0));
            rect.setOutlineColor(sf::Color(255,255,255,255,255));
            rect.setOutlineThickness(1);
            m_game.window().draw(rect);
        }
    }

    // draw the grid for easier debugging 
    if(m_drawGrid)
    {
        float leftX = m_game.window().getView().getCenter().x - width() / 2;
        float rightX = leftX + width() + m_gridSize.x;
        float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);

        for(float x = nextGridX; x < rightX; x += gridSize.x)
        {
            drawLine(Vec2f(x,0), Vec2f(x, height()));
        }

        for(float y = 0; y < height(); y += m_gridSize.y)
        {
            drawLine(Vec2f(leftX, height() - y), Vec2f(rightX, height()-y));

            for(float x = nextGridX; x < rightX; x += m_gridSize.x)
            {
                std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
                std::string yCell = std::to_string((int)y / (int)m_gridSize.y);
                gridText.setString("(" + xCell + "," + yCell + ")");
                gridText.setPosition({x + 3, height()-y - m_gridSize.y + 2});
                m_game.window().draw(gridText);   
            }
        }
    }
}

void Scene_Play::drawLine(const Vec2f& p1, const Vec2f& p2)
{
    sf::Vertex line[] = { {p1, sf::Color::White}, {p2, sf::Color::White}};
    m_game.window().draw(line, 2, sf::PrimitiveType::Lines);
}
