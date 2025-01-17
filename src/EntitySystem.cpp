#include "EntitySystem.h"
#include "GameEntity.h"
#include <SFML\Graphics.hpp>

EntitySystem::EntitySystem(sf::RenderWindow* window) : m_renderWindow(window)
{
}

void EntitySystem::drawEntities()
{
    sortEntities();
    
    for (auto& entity : m_entities)
    {
        if(entity->isActive())
        {
            m_renderWindow->draw(*entity->getEntitySprite());
        }
    }
}

GameEntity* EntitySystem::createEntity(const std::filesystem::path& spriteName, sf::Vector2f position, float depth)
{
    std::unique_ptr<GameEntity> entity = std::make_unique<GameEntity>(spriteName, position, depth);
    GameEntity* ptr = entity.get();
    m_entities.push_back(std::move(entity));
    return ptr;
}

GameEntity* EntitySystem::createEntity(const std::filesystem::path& spriteName)
{
    return createEntity(spriteName, sf::Vector2f(0, 0));
}

void EntitySystem::sortEntities()
{
    std::sort(m_entities.begin(), m_entities.end(), GameEntity::compare);
}
