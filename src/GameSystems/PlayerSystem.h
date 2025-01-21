#pragma once
#include <SFML/System/Vector2.hpp>
#include "Sides.h"

#include "../EventManager.h"
#include "GameSystem.h"

class GameEntity;

class PlayerSystem : public GameSystem, public IEventListener
{
public:
    PlayerSystem(EntitySystem* entitySystem, EventManager* eventManager);
    ~PlayerSystem() override;
    void update(sf::Time& dt) override;
    void onEvent(EventType event) override;
private:
    void onGameStart();
    void onGameEnd() const;

    void movePlayer(side side, bool pushEvent = true);
    sf::Vector2f getPlayerPosition(side side) const;

    void recalculatePlayerPositions();

    sf::Vector2f m_playerPositions[static_cast<int>(side::NONE)] = {sf::Vector2f(580, 720), sf::Vector2f(1200, 720)};
    side m_playerSide;
    GameEntity* m_playerAlive;
    GameEntity* m_deadPlayer;
};
