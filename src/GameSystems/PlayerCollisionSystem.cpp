#include "PlayerCollisionSystem.h"

#include "BranchesSystem.h"
#include "PlayerSystem.h"

PlayerCollisionSystem::PlayerCollisionSystem(PlayerSystem* playerSystem, BranchesSystem* branchesSystem,
                                             EntitySystem* entitySystem,
                                             EventManager* eventManager): GameSystem(entitySystem, eventManager),
                                                                          m_playerSystem(playerSystem),
                                                                          m_branchesSystem(branchesSystem)
{
    eventManager->addEventListener(this);
}

PlayerCollisionSystem::~PlayerCollisionSystem()
{
    p_eventManager->removeEventListener(this);
}

void PlayerCollisionSystem::update(sf::Time& dt)
{
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
