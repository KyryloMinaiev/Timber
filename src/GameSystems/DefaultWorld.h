#pragma once
#include "World.h"

class DefaultWorld : public World
{
public:
    DefaultWorld(EntitySystem* entitySystem, EventManager* eventManager);
};
