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

    if(event == EventType::GameEnded)
    {
        onGameEnd();
    }
}

void PlayerSystem::onGameStart()
{
    m_playerAlive->setActive(true);
    m_deadPlayer->setActive(false);
    movePlayer(side::LEFT);
}

void PlayerSystem::onGameEnd() const
{
    m_playerAlive->setActive(false);
    m_deadPlayer->setActive(true);
    m_deadPlayer->setPosition(getPlayerPosition(m_playerSide));
}

void PlayerSystem::movePlayer(side side, bool pushEvent)
{
    m_playerSide = side;
    m_playerAlive->setPosition(getPlayerPosition(side));
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

void PlayerSystem::recalculatePlayerPositions()
{
    auto screenSize = static_cast<sf::Vector2f>(Screen::getWindowSize());
    auto scale = sf::Vector2f(screenSize.x / 1920.0f, screenSize.y / 1080.0f);
    
    for (auto& playerPosition : m_playerPositions)
    {
        auto referencePosition = playerPosition;

        referencePosition.x *= scale.x;
        referencePosition.y *= scale.y;

        playerPosition = referencePosition;
    }

    m_playerAlive->setScale(scale);
    m_deadPlayer->setScale(scale);
}
