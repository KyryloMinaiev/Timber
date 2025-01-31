#include "CloudsSystem.h"

#include "../EntitySystem.h"
#include "../Screen.h"

CloudsSystem::CloudsSystem(World* world, EntitySystem* entitySystem, EventManager* eventManager): GameSystem(world, entitySystem, eventManager)
{
    for (int i = 0; i < k_cloudsCount; ++i)
    {
        m_clouds.push_back({entitySystem->createEntity("res/graphics/cloud.png", sf::Vector2f(0, 0), -50), 0});
        m_clouds[i].cloudEntity->setActive(false);
    }
}

CloudsSystem::~CloudsSystem() = default;

void CloudsSystem::onUpdate(sf::Time& dt)
{
    for (int i = 0; i < k_cloudsCount; ++i)
    {
        updateCloud(m_clouds[i], i, dt);
    }
}

void CloudsSystem::updateCloud(CloudData& cloudData, int index, sf::Time& dt)
{
    auto screenWidth = Screen::getWindowSize().x;
    
    if (!cloudData.cloudEntity->isActive())
    {
        srand((int)time(0) * index);
        cloudData.cloudSpeed = (rand() % 200);
        srand((int)time(0) * index);
        float height = (rand() % 150);
        cloudData.cloudEntity->setPosition(sf::Vector2f(-200, height));
        cloudData.cloudEntity->setActive(true);

        return;
    }
    
    cloudData.cloudEntity->move(sf::Vector2f(cloudData.cloudSpeed * dt.asSeconds(), 0));
    if (cloudData.cloudEntity->getPosition().x > screenWidth)
    {
        cloudData.cloudEntity->setActive(false);
    }
}