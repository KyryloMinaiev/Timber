#pragma once
#include "GameSystem.h"

class GameEntity;

class BeeSystem : public GameSystem
{
public:
    BeeSystem(World* world, EntitySystem* entitySystem, EventManager* eventManager);
    ~BeeSystem() override;

protected:
    void onUpdate(sf::Time& dt) override;

private:
    GameEntity* m_bee;
    bool m_beeOutsideScreen;
    float m_beeSpeed;
};
