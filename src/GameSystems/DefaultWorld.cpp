#include "DefaultWorld.h"

#include "BackgroundSystem.h"
#include "BeeSystem.h"
#include "CloudsSystem.h"

DefaultWorld::DefaultWorld(EntitySystem* entitySystem, EventManager* eventManager): World(entitySystem, eventManager)
{
    addSystemOfType<BackgroundSystem>();
    addSystemOfType<CloudsSystem>();
    addSystemOfType<BeeSystem>();
}
