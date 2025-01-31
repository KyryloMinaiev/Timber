#pragma once
#include "World.h"

class GameplayWorld : public World
{
public:
    GameplayWorld(EntitySystem* entitySystem, EventManager* eventManager);
};
