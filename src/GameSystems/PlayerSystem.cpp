#include "PlayerSystem.h"

#include "../EntitySystem.h"
#include "../InputSystem.h"
#include "../Screen.h"

PlayerSystem::PlayerSystem(EntitySystem* entitySystem, EventManager* eventManager) : GameSystem(entitySystem, eventManager), m_playerSide(side::NONE)
{
    m_playerAlive = entitySystem->createEntity("res/graphics/player.png", getPlayerPosition(m_playerSide), 10);
    m_playerAlive->setActive(false);

    m_deadPlayer = entitySystem->createEntity("res/graphics/rip.png", getPlayerPosition(m_playerSide), 10);
    m_deadPlayer->setActive(false);

    m_axe = entitySystem->createEntity("res/graphics/axe.png", getAxePosition(m_playerSide), 9);
    m_axe->setActive(false);

    recalculatePlayerPositions();
    
    eventManager->addEventListener(this);
}

PlayerSystem::~PlayerSystem()
{
    p_eventManager->removeEventListener(this);
};

void PlayerSystem::update(sf::Time& dt)
{
    if(InputSystem::isKeyDown(sf::Keyboard::Key::Left))
    {
        movePlayer(side::LEFT);
    }
    else if(InputSystem::isKeyDown(sf::Keyboard::Key::Right))
    {
        movePlayer(side::RIGHT);
    }
}

void PlayerSystem::onEvent(EventType event)
{
    if(event == EventType::GameStarted)
    {
        onGameStart();
    }

    if(event == EventType::PlayerCollision)
    {
        onPlayerCollision();
    }
}

side PlayerSystem::getPlayerSide() const
{
    return m_playerSide;
}

void PlayerSystem::onGameStart()
{
    m_playerAlive->setActive(true);
    m_deadPlayer->setActive(false);
    m_axe->setActive(true);
    movePlayer(side::LEFT, false);
}

void PlayerSystem::onPlayerCollision() const
{
    m_playerAlive->setActive(false);
    m_deadPlayer->setActive(true);
    m_axe->setActive(false);
    m_deadPlayer->setPosition(getPlayerPosition(m_playerSide));
}

void PlayerSystem::onTimeEnded() const
{
    m_playerAlive->setActive(false);
    m_axe->setActive(false);
}

void PlayerSystem::movePlayer(side side, bool pushEvent)
{
    m_playerSide = side;
    m_playerAlive->setPosition(getPlayerPosition(side));
    m_axe->setPosition(getAxePosition(side));
    
    if(pushEvent)
    {
        p_eventManager->invokeEvent(EventType::PlayerMoved);
    }
}

sf::Vector2f PlayerSystem::getPlayerPosition(side side) const
{
    if(side == side::NONE)
    {
        return {0, 0};
    }

    return m_playerPositions[static_cast<int>(side)];
}

sf::Vector2f PlayerSystem::getAxePosition(side side) const
{
    if(side == side::NONE)
    {
        return {0, 0};
    }

    return m_axePositions[static_cast<int>(side)];
}

void PlayerSystem::recalculatePlayerPositions()
{
    auto scale = Screen::getScaleFactor();
    
    for (auto& playerPosition : m_playerPositions)
    {
        auto referencePosition = playerPosition;
        referencePosition.x *= scale.x;
        referencePosition.y *= scale.y;
        playerPosition = referencePosition;
    }

    for (auto& axePosition : m_axePositions)
    {
        auto referencePosition = axePosition;
        referencePosition.x *= scale.x;
        referencePosition.y *= scale.y;
        axePosition = referencePosition;
    }

    m_playerAlive->setScale(scale);
    m_deadPlayer->setScale(scale);
    m_axe->setScale(scale);
}
