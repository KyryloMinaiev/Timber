#pragma once
#include "GameSystem.h"

class GameEntity;

class BeeSystem : public GameSystem
{
public:
    BeeSystem(EntitySystem* entitySystem);
    ~BeeSystem() override;

    void update(sf::Time& dt) override;

private:
    GameEntity* m_bee;
    bool m_beeOusideScreen;
    float m_beeSpeed;
};
