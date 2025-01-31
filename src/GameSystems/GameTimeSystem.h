#pragma once
#include "GameSystem.h"

#include "../EventManager.h"

class GameTimeSystem : public GameSystem, public IEventListener
{
public:
    GameTimeSystem(World* world, EntitySystem* entitySystem, EventManager* eventManager);
    ~GameTimeSystem() override;
    void onEvent(EventType event) override;
protected:
    void onUpdate(sf::Time& dt) override;
private:
    void onGameStart();
    void onPlayerMoved();
    void checkGameTime() const;
    
    static constexpr float k_startTime = 6.0f;
    float m_currentTime;
    float m_currentScore;
};
