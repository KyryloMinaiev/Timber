#pragma once
#include <SFML/System/Time.hpp>

class EntitySystem;
class EventManager;

class GameSystem
{
public:
    GameSystem(EntitySystem* entitySystem, EventManager* eventManager) : p_entitySystem(entitySystem), p_eventManager(eventManager)
    {
    }

    virtual ~GameSystem() = default;
    virtual void update(sf::Time& dt) = 0;

protected:
    EntitySystem* p_entitySystem;
    EventManager* p_eventManager;
};
