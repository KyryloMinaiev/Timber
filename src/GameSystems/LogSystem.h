#pragma once
#include <SFML/System/Vector2.hpp>

#include "GameSystem.h"
#include "../EventManager.h"

class GameEntity;

class LogSystem : public GameSystem, IEventListener
{
public:
    LogSystem(World* world, EntitySystem* entitySystem, EventManager* eventManager);
    ~LogSystem() override;
    void onEvent(EventType event) override;
protected:
    void onUpdate(sf::Time& dt) override;
private:
    static constexpr float k_logSpeedX = 5000;
    static constexpr float k_logSpeedY = -1500;

    void onPlayerMoved();

    bool m_logMoving;
    sf::Vector2f m_startLogPosition = {810, 720};
    GameEntity* m_log;
};
