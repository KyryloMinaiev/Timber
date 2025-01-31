#pragma once


#include "World.h"
#include "../IUpdatable.h"

class EntitySystem;
class EventManager;

class GameSystem : public IUpdatable
{
public:
    GameSystem(World* world, EntitySystem* entitySystem, EventManager* eventManager) : p_entitySystem(entitySystem),
        p_eventManager(eventManager), p_world(world), m_initialized(false)
    {
    }

    ~GameSystem() override = default;

    void update(sf::Time& dt) final
    {
        if (!m_initialized)
        {
            onStartRunning();
            m_initialized = true;
        }

        onUpdate(dt);
    }

protected:
    virtual void onStartRunning()
    {
    }

    virtual void onUpdate(sf::Time& dt) = 0;

    EntitySystem* p_entitySystem;
    EventManager* p_eventManager;
    World* p_world;

private:
    bool m_initialized;
};
