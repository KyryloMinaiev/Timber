﻿#include "BeeSystem.h"

#include "../Screen.h"
#include "../EntitySystem.h"

BeeSystem::BeeSystem(World* world, EntitySystem* entitySystem, EventManager* eventManager): GameSystem(world, entitySystem, eventManager),
                                                                              m_beeOutsideScreen(true),
                                                                              m_beeSpeed(0)
{
    m_bee = entitySystem->createEntity("res/graphics/bee.png",
                                       sf::Vector2f(0, 0), 5);
}

BeeSystem::~BeeSystem() = default;

void BeeSystem::onUpdate(sf::Time& dt)
{
    auto screenSize = Screen::getWindowSize();
    auto edgeOffset = screenSize.x * 0.1f;
    
    if (m_beeOutsideScreen)
    {
        srand((int)time(0));
        m_beeSpeed = (rand() % 200) + 500;
        srand((int)time(0) * 10);
        float height = (rand() % 500) + 500;
        m_bee->setPosition(sf::Vector2f(edgeOffset + screenSize.x, height));
        m_beeOutsideScreen = false;
    }
    else
    {
        m_bee->move(sf::Vector2f(-m_beeSpeed * dt.asSeconds(), 0));

        if (m_bee->getPosition().x < -100)
        {
            m_beeOutsideScreen = true;
        }
    }
}
