#include "PlayerCollisionSystem.h"

#include "BranchesSystem.h"
#include "PlayerSystem.h"

PlayerCollisionSystem::PlayerCollisionSystem(World* world, EntitySystem* entitySystem,
                                             EventManager* eventManager) : GameSystem(world, entitySystem, eventManager),
                                                                          m_playerSystem(nullptr),
                                                                          m_branchesSystem(nullptr)
{
    eventManager->addEventListener(this);
}

PlayerCollisionSystem::~PlayerCollisionSystem()
{
    p_eventManager->removeEventListener(this);
}

void PlayerCollisionSystem::onUpdate(sf::Time& dt)
{
}

void PlayerCollisionSystem::onStartRunning()
{
    m_playerSystem = p_world->getExistingSystem<PlayerSystem>();
    m_branchesSystem = p_world->getExistingSystem<BranchesSystem>();
}

void PlayerCollisionSystem::onEvent(EventType event)
{
    if (event == EventType::PlayerMoved)
    {
        checkCollision();
    }
}

void PlayerCollisionSystem::checkCollision() const
{
    side playerSide = m_playerSystem->getPlayerSide();
    side lastBranchSide = m_branchesSystem->getLastBranchSide();
    if (playerSide == lastBranchSide)
    {
        p_eventManager->invokeEvent(EventType::PlayerCollision);
    }
}
