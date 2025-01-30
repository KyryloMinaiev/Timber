#pragma once
#include "GameSystem.h"
#include "../EventManager.h"

class PlayerSystem;
class BranchesSystem;

class PlayerCollisionSystem : public GameSystem, public IEventListener
{
public:
    PlayerCollisionSystem(PlayerSystem* playerSystem, BranchesSystem* branchesSystem, EntitySystem* entitySystem, EventManager* eventManager);

    ~PlayerCollisionSystem() override;
    void update(sf::Time& dt) override;
    void onEvent(EventType event) override;

private:
    void checkCollision() const;
    
    PlayerSystem* m_playerSystem;
    BranchesSystem* m_branchesSystem;
};
