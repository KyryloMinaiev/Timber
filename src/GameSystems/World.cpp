#include "World.h"

#include "GameSystem.h"

World::World(EntitySystem* entitySystem, EventManager* eventManager) : m_entitySystem(entitySystem), m_eventManager(eventManager)
{
}

World::~World() = default;

void World::update(sf::Time& dt)
{
    for (const auto& system : m_gameSystems)
    {
        system->update(dt);
    }
}
