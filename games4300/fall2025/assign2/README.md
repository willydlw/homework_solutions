# Assign 2 - Geometry Wars 

## Lecture 4 Notes - Entity Component System (ECS) Game Programming

ECS uses composition-based design 
Entity: Any object in the game 
    Examples: player, platform, tile, bullet
Component: Properties attached to entities (pure data-no functions)
    Ex: position, texture, animation, health, gravity 
Systems: Coding logic that drives behavior 
    Ex: movement, rendering, sound, physics


Entities are composed of components 

Ex: 
    Player has position, velocity bounding box, sprite, health, gravity, input 
    Bullet has position, velocity, angle, bounding box, sprite, damage, lifespan 
    Tile has position, bounding box, sprite

ECS Example Systems 

```cpp
// movement system
for( auto e : entities) { e.pos += e.velocity;}

// collision system
for( auto b: bullets)
{
    for(auto e : enemies)
    {
        if(Physics::IsCollision(b,e))
        {
            e.health -= b.damage
            b.destroy();
        }
    }
}

// rendering system 
for(auto e : entities) { window.draw(e.sprite, e.pos); }

```

Engine Architecture 

Game Engine 
    > Scene 
        > Systems 
        > Entity Manager 
            > Entity 
                > Component


## Notes

Notes are from Lecture 5 

### Iterator Invalidation 

- Caused by modifying the contents of a collection as we are iterating through it
    - Adding: While iterating through all entities to check for collisions, and explosion happens and we spawan an explosion entity. 
    - Removing: Iterate throug entities to check collisions, one dies, so we remove it

C++ Iterator Invalidation 
- Vector functions may cause reallocation 
    - Adding to vector: push_back, insert 
    - Vector may resize, recreating internal array 
    - Invalidates all pointers and iterators as vector uses contiguous heap memory
- Erasing elements may invalidate too 
    - Remove from vector: erase, pop_back 
    - Invalidates iterators and references at or after the point of erasing in the internal array

Iterator Invalidation Example 

```cpp
void sCollision()
{
    EntityVec bullets;
    EntityVec tiles;
    for(auto& b : bullets)
        for(auto& t : tiles)
            if(Physics::IsCollsion(b,t)){
                // destroy function only sets alive flag to false
                bullets.destroy(b);
            }
}
// all iterators / values of b after erase may be invalid
```

How to solve this issue?

- One way ot avoid iterator invalidation is to delay the effects of actions that modify collections until it is safe to do so
- With the EntityManager handling Entity creation and destruction, this becomes easy (Factory Pattern)
- Idea: Only add or remove entities at the beginning of a frame when it is safe


### Entity Private Constructor 

We can ensure the safe creation of Entity objects by only allowing them to be created by the EntityManger class. We can make the Entity constructor private and add EntityManager as friend class. This way we cannot create Entity objects outside of the EntityManager.

Unfortunately, having a private constructor means that we can no longer use 

```cpp
auto e = std::make_shared<Entity>(args);
``` 

because make_shared does not have access to private constructor. May be different in newer C++ standard.

Instead we use an older method:

```cpp
auto e = std::shared_ptr<Entity>(new Entity(args));
```

This is not the preferred way of creating shared pointer objects, but we have to make this exception for our design.

