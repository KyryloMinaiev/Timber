#pragma once
#include <SFML/System/Time.hpp>

class EntitySystem;

class GameSystem
{
public:
    GameSystem(EntitySystem* entitySystem) : entitySystem(entitySystem)
    {
    }

    virtual ~GameSystem() = default;
    virtual void update(sf::Time& dt) = 0;

protected:
    EntitySystem* entitySystem;
};
