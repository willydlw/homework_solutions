class EntityManager 
{
    std::vector<Entity*>      entities;
    std::map<string, Entity*> entityMap;
    std::vector<Entity*> toAdd; 

    void init();
    void update();
    Entity* addEntity(args);
    std::vector<Entity*>& getEntities();
    std::vector<Entity*>& getEntities(string entityTypeName);
};