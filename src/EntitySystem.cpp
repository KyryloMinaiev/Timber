#include "EntitySystem.h"
#include "GameEntity.h"
#include <SFML\Graphics.hpp>

EntitySystem::EntitySystem(sf::RenderWindow* window) : m_renderWindow(window)
{
}

void EntitySystem::drawEntities() const
{
    for (auto& entity : m_entities)
    {
        if(entity->isActive())
        {
            m_renderWindow->draw(*entity->getEntitySprite());
        }
    }
}

GameEntity* EntitySystem::createEntity(const std::filesystem::path& spriteName, sf::Vector2f position)
{
    std::unique_ptr<GameEntity> entity = std::make_unique<GameEntity>(spriteName, position);
    GameEntity* ptr = entity.get();
    m_entities.push_back(std::move(entity));
    return ptr;
}

GameEntity* EntitySystem::createEntity(const std::filesystem::path& spriteName)
{
    return createEntity(spriteName, sf::Vector2f(0, 0));
}
