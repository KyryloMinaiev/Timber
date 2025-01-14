#include "GameEntity.h"

GameEntity::GameEntity(const std::filesystem::path& spriteName): m_position(0, 0), m_enabled(true)
{
    initializePointers(spriteName);
    updateSpritePosition();
}

GameEntity::GameEntity(const std::filesystem::path& spriteName, const Vector2f& position): m_position(position), m_enabled(true)
{
    initializePointers(spriteName);
    updateSpritePosition();
}

GameEntity::~GameEntity() = default;

void GameEntity::setPosition(Vector2f position)
{
    m_position = position;
    updateSpritePosition();
}

void GameEntity::draw(RenderWindow& window) const
{
    window.draw(*m_entitySprite);
}

void GameEntity::move(Vector2f translate)
{
    setPosition(m_position + translate);
}

Vector2f GameEntity::getPosition() const
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

void GameEntity::updateSpritePosition() const
{
    m_entitySprite->setPosition(m_position);
}

void GameEntity::initializePointers(const std::filesystem::path& spriteName)
{
    m_spriteTexture = std::make_unique<Texture>(spriteName);
    m_entitySprite = std::make_unique<Sprite>(*m_spriteTexture);
}
