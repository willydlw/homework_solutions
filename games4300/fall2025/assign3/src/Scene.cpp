#include "Scene.h"
#include "GameEngine.h"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

#include <array>


Scene::Scene() = default;

Scene::Scene(GameEngine* gameEngine) 
    : m_game(gameEngine) {}

Scene::~Scene() = default;

// TODO: understand why we have this function
// is it because sDoAction is a pure virtual function?
// and we want an abstract base class pointer to call the 
// appropriate action?
void Scene::doAction(const Action& action)
{
    sDoAction(action);
}

void Scene::simulate(const size_t frames) 
{
    std::cerr << "TODO: function " << __PRETTY_FUNCTION__ << 
        " what does frames do? frames value: "
    << frames << "\n";
}

void Scene::registerAction(int inputKey, const std::string& actionName)
{
    // if aName is already in the map (rebinding keys), we may 
    // want to remove that. Example: have already stored W as Jump action 
    // and now user wants to use space bar as Jump. It is a game design 
    // decision whether we want one or multiple keys performing the same action
    m_actionMap[inputKey] = actionName;
}

size_t Scene::width() const
{
    return m_game->window().getSize().x;
}

size_t Scene::height()const 
{
    return m_game->window().getSize().y;
}

size_t Scene::currentFrame() const 
{
    return m_currentFrame;
}

bool Scene::hasEnded() const 
{
    return m_hasEnded;
}

const ActionMap& Scene::getActionMap() const
{
    return m_actionMap;
}

void Scene::drawLine(const Vec2f& p1, const Vec2f& p2)
{
    std::array vertices = {
        sf::Vertex{sf::Vector2f{p1.x, p1.y}},
        sf::Vertex{sf::Vector2f{p2.x, p2.y}}
    };
    
    m_game->window().draw(vertices.data(), vertices.size(), sf::PrimitiveType::Lines);
}