#pragma once


#include "../IUpdatable.h"

class EntitySystem;
class EventManager;

class GameSystem : public IUpdatable
{
public:
    GameSystem(EntitySystem* entitySystem, EventManager* eventManager) : p_entitySystem(entitySystem), p_eventManager(eventManager)
    {
    }

    ~GameSystem() override = default;

protected:
    EntitySystem* p_entitySystem;
    EventManager* p_eventManager;
};
