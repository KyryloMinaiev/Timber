#include "GameTimeSystem.h"

#include "../UIController.h"

GameTimeSystem::GameTimeSystem(EntitySystem* entitySystem, EventManager* eventManager) :
    GameSystem(entitySystem, eventManager), m_currentTime(0), m_currentScore(0)
{
}

GameTimeSystem::~GameTimeSystem() = default;

void GameTimeSystem::update(sf::Time& dt)
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
}

void GameTimeSystem::checkGameTime() const
{
    if (m_currentTime <= 0)
    {
        p_eventManager->invokeEvent(EventType::TimeEnded);
    }

    UIController::getInstance()->updateTimeBar(m_currentTime / k_startTime);
}
