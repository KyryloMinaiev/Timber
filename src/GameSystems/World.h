#pragma once
#include "../IUpdatable.h"
#include <map>
#include <memory>
#include <vector>
#include <typeindex>

class GameSystem;
class EventManager;
class EntitySystem;

class World : public IUpdatable
{
public:
    World(EntitySystem* entitySystem, EventManager* eventManager);
    ~World() override;
    void update(sf::Time& dt) override;

    template<class T>
    void addSystemOfType();
    template<class T>
    T* getExistingSystem();
private:
    EntitySystem* m_entitySystem;
    EventManager* m_eventManager;
    
    std::map<std::type_index, GameSystem*> m_gameSystemsTypeMap;
    std::vector<std::unique_ptr<GameSystem>> m_gameSystems;
};

template <class T>
void World::addSystemOfType()
{
    std::unique_ptr<T> ptr = std::make_unique<T>(this, m_entitySystem, m_eventManager);
    const std::type_info& type = typeid(T);
    m_gameSystemsTypeMap[type] = ptr.get();
    m_gameSystems.push_back(std::move(ptr));
}

template <class T>
T* World::getExistingSystem()
{
    const std::type_info& type = typeid(T);
    if(m_gameSystemsTypeMap.find(type) != m_gameSystemsTypeMap.cend())
    {
        return dynamic_cast<T*>(m_gameSystemsTypeMap[type]);
    }

    return nullptr;
}
