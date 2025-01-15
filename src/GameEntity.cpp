#include "GameEntity.h"
#include <SFML\Graphics.hpp>

GameEntity::GameEntity() : m_spriteTexture(nullptr), m_entitySprite(nullptr), m_position(0, 0), m_enabled(false)
{
}

GameEntity::GameEntity(const std::filesystem::path& spriteName): m_position(0, 0), m_enabled(true)
{
    initializePointers(spriteName);
    updateSpritePosition();
}

GameEntity::GameEntity(const std::filesystem::path& spriteName, const sf::Vector2f& position): m_position(position), m_enabled(true)
{
    initializePointers(spriteName);
    updateSpritePosition();
}

GameEntity::~GameEntity() = default;

void GameEntity::setPosition(sf::Vector2f position)
{
    m_position = position;
    updateSpritePosition();
}

void GameEntity::move(sf::Vector2f translate)
{
    setPosition(m_position + translate);
}

sf::Vector2f GameEntity::getPosition() const
{
    return m_position;
}

void GameEntity::setActive(bool active)
{
    m_enabled = active;
}

bool GameEntity::isActive() const
{
    return m_enabled;
}

sf::Sprite* GameEntity::getEntitySprite() const
{
    return m_entitySprite.get();
}

void GameEntity::updateSpritePosition() const
{
    m_entitySprite->setPosition(m_position);
}

void GameEntity::initializePointers(const std::filesystem::path& spriteName)
{
    m_spriteTexture = std::make_unique<sf::Texture>(spriteName);
    m_entitySprite = std::make_unique<sf::Sprite>(*m_spriteTexture);
}
