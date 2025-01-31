#pragma once
#include "GameSystem.h"
#include "../EventManager.h"

class PlayerSystem;
class BranchesSystem;

class PlayerCollisionSystem : public GameSystem, public IEventListener
{
public:
    PlayerCollisionSystem(World* world, EntitySystem* entitySystem, EventManager* eventManager);

    ~PlayerCollisionSystem() override;
    void onEvent(EventType event) override;
    
protected:
    void onUpdate(sf::Time& dt) override;
    void onStartRunning() override;
private:
    void checkCollision() const;
    
    PlayerSystem* m_playerSystem;
    BranchesSystem* m_branchesSystem;
};
