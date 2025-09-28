#pragma once 

#include "Components.hpp"
#include <string>
#include <tuple>

class EntityManager;

using ComponentTuple = std::tuple< 
    CTransform,
    CShape,
    CCollision,
    CInput,
    CScore,
    CLifeSpan
>;

class Entity
{
    friend class EntityManager;

public:
    Entity();

    void                add<T>(args);
    T&                  get<T>();
    bool                has<T>();
    
    std::size_t         id() const; 
    bool                isAlive() const;
    void                destroy();          // set alive to false
    const std::string&  tag() const;

private:
    ComponentTuple      m_components;
    bool                m_alive = true;     // if false, will delete entity
    std::string         m_tag = "default";
    std::size_t         m_id = 0;           // unique id 
};