#ifndef A3_ENTITY_H
#define A3_ENTITY_H

#include "Components.hpp"
#include <string>
#include <tuple>

class EntityManager;

using ComponentTuple = std::tuple< 
    CTransform,
    CLifespan,
    CInput,
    CBoundingBox,
    CAnimation,
    CGravity,
    CState
>;

class Entity
{
    friend class EntityManager;

public:
    Entity() = default;
    Entity(std::size_t id, const std::string& tag)
        : m_id(id), m_tag(tag)
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

    friend std::ostream& operator << (std::ostream& os, const Entity& obj )
    {
        os << "tag: " << obj.m_tag 
            << "id: " << obj.m_id << "\n";
        return os;
    }

private:
   
    bool                m_alive = true;     // if false, will delete entity
    std::size_t         m_id = 0;           // unique id 
    std::string         m_tag = "default";
    ComponentTuple      m_components;
};

#endif