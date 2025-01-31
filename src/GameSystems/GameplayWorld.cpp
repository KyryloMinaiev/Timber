#include "GameplayWorld.h"

#include "BranchesSystem.h"
#include "GameTimeSystem.h"
#include "LogSystem.h"
#include "PlayerCollisionSystem.h"
#include "PlayerSystem.h"

GameplayWorld::GameplayWorld(EntitySystem* entitySystem, EventManager* eventManager): World(entitySystem, eventManager)
{
    addSystemOfType<PlayerSystem>();
    addSystemOfType<BranchesSystem>();
    addSystemOfType<GameTimeSystem>();
    addSystemOfType<LogSystem>();
    addSystemOfType<PlayerCollisionSystem>();
}
