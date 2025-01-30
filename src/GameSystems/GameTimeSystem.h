#pragma once
#include "GameSystem.h"

#include "../EventManager.h"

class GameTimeSystem : public GameSystem, public IEventListener
{
public:
    GameTimeSystem(EntitySystem* entitySystem, EventManager* eventManager);
    ~GameTimeSystem() override;
    void update(sf::Time& dt) override;
    void onEvent(EventType event) override;
private:
    void onGameStart();
    void onPlayerMoved();
    void checkGameTime() const;
    
    static constexpr float k_startTime = 6.0f;
    float m_currentTime;
    float m_currentScore;
};
