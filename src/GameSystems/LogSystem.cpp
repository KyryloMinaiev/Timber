#include "LogSystem.h"

#include "../EntitySystem.h"
#include "../Screen.h"

LogSystem::LogSystem(World* world, EntitySystem* entitySystem, EventManager* eventManager): GameSystem(world, entitySystem, eventManager), m_logMoving(false)
{
    m_log = entitySystem->createEntity("res/graphics/log.png", sf::Vector2f(), 10);
    m_log->setActive(false);

    auto screenScale = Screen::getScaleFactor();
    m_startLogPosition.x *= screenScale.x;
    m_startLogPosition.y *= screenScale.y;
    m_log->setScale(screenScale);
    
    eventManager->addEventListener(this);
}

LogSystem::~LogSystem()
{
    p_eventManager->removeEventListener(this);
}

void LogSystem::onUpdate(sf::Time& dt)
{
    if(!m_logMoving)
    {
        return;
    }

    m_log->setPosition(
            sf::Vector2f(m_log->getPosition().x +
                     (k_logSpeedX * dt.asSeconds()),
        
                     m_log->getPosition().y +
                     (k_logSpeedY * dt.asSeconds())));

        auto screenWidth =  Screen::getWindowSize().x;
        if (m_log->getPosition().x < -100 ||
            m_log->getPosition().x > screenWidth)
        {
            m_logMoving = false;
            m_log->setPosition(m_startLogPosition);
        }
}

void LogSystem::onEvent(EventType event)
{
    if(event == EventType::GameStarted)
    {
        m_log->setActive(true);
        m_log->setPosition(m_startLogPosition);
    }
    
    if(event == EventType::PlayerMoved)
    {
        onPlayerMoved();
    }

    if(event == EventType::GameEnded)
    {
        m_log->setActive(false);
        m_logMoving = false;
    }
}

void LogSystem::onPlayerMoved()
{
    m_logMoving = true;
    m_log->setPosition(m_startLogPosition);
}
