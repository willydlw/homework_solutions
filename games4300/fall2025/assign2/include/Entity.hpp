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
    Entity() = default;
    Entity(std::size_t id, const std::string& tag)
        : m_tag(tag), m_id(id)
    {

    }

    template <typename T, typename... TArgs>
    T& add(TArgs&&... margs)
    {
        auto & component = get<T>();    // default construct sets exists to false 
        component = T(std::forward<TArgs>(margs)...);
        component.exists = true;
        return component;
    }

    template <typename T>
    T & get()
    {
        return std::get<T>(m_components);
    }

    // const version to keep const correctness
    template <typename T>
    const T & get() const 
    {
        return std::get<T>(m_components);
    }

    template <typename T>
    bool has() const
    {
        return get<T>().exists;
    }


    template <typename T>
    void remove()
    {
        // default construct it so exists is false
        // then when has checks exists, it will be false
        get<T>() = T();
    }
    
    std::size_t         id() const { return m_id; }
    bool                isAlive() const { return m_alive;};
    void                destroy() { m_alive = false; };   
    const std::string&  tag() const { return m_tag; }

private:
    ComponentTuple      m_components;
    bool                m_alive = true;     // if false, will delete entity
    std::string         m_tag = "default";
    std::size_t         m_id = 0;           // unique id 
};