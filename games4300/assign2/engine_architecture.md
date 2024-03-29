# Engine Architecture - Assignment 2

- Separation of functionality into classes 
- Write our own Vect2 class for 2D game math
- Appearance of ECS classes (Entity Component System)
- EntityManager handles all Entity data
- ECS Systems functionality in Game.h functions

</br></br>
![Architecture](/images/architecture.png)
</br></br>

## Components
- pure data
- stored in Entity
- each component has its own class
   - Examples: CTransform, CScore,

- Each implements intuitive Entity 'feature'
</br></br>

## Entity
- Entity = Game Object 
- Stores Component Pointers
   - Shared_ptr
- Tag = Entity 'type'
- Active = Alive or Dead
- ID = integer identifier
- Note: In the architecture image, * means shared_ptr for assign 2
</br></br>

## Entity Manager
- Entity 'Factory' Class
- Delayed Entity Add()
   - Iterator Invalidation
- Secondary map from tag -> entity
   - Trade storage for convenience / run time
- Can do other bookkeeping like memory management


## Game

- Top-level Game Object
- Holds all game data
- All game system functions
- All gameplay code


## What can this engine do?

- Create game objects as Entity instances
- Add Component data to Entities
- Implement game play via Systems
   - also, handle user input
- Pause game play / exit game
- Can init / load configuration from file

## What are the game engine limitations?

- Can only display one 'scene'
- Can not load texture / sounds assets
- Can not display textured animations
- Does not have any menu / interface
