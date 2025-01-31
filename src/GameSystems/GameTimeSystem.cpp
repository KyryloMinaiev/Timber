#include "GameTimeSystem.h"

#include "../UIController.h"

GameTimeSystem::GameTimeSystem(World* world, EntitySystem* entitySystem, EventManager* eventManager) :
    GameSystem(world, entitySystem, eventManager), m_currentTime(0), m_currentScore(0)
{
    eventManager->addEventListener(this);
}

GameTimeSystem::~GameTimeSystem() 
{
    p_eventManager->removeEventListener(this);
}

void GameTimeSystem::onUpdate(sf::Time& dt)
{
    m_currentTime -= dt.asSeconds();
    checkGameTime();
}

void GameTimeSystem::onEvent(EventType event)
{
    if (event == EventType::PlayerMoved)
    {
        onPlayerMoved();
    }

    if (event == EventType::GameStarted)
    {
        onGameStart();
    }
}


void GameTimeSystem::onGameStart()
{
    m_currentTime = k_startTime;
    m_currentScore = 0;
}

void GameTimeSystem::onPlayerMoved()
{
    m_currentScore++;
    m_currentTime += (2 / m_currentScore) + 0.15f;
    m_currentTime = std::min(m_currentTime, k_startTime);
    UIController::getInstance()->updateScore(static_cast<int>(m_currentScore));
}

void GameTimeSystem::checkGameTime() const
{
    UIController::getInstance()->updateTimeBar(m_currentTime / k_startTime);

    if (m_currentTime <= 0)
    {
        p_eventManager->invokeEvent(EventType::TimeEnded);
    }
}
