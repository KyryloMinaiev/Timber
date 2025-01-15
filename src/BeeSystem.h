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
    const float START_BEE_HORIZONTAL_POSITION = 0;
    const float START_BEE_VERTICAL_POSITION = 800;

    GameEntity* m_bee;
    bool m_beeOusideScreen;
    float m_beeSpeed;
};
