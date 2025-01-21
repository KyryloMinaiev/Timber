#pragma once

#include <filesystem>
#include <memory>
#include <SFML/System/Vector2.hpp>

namespace sf
{
    class Sprite;
    class Texture;
}

class GameEntity {
public:
    GameEntity();
    GameEntity(const std::filesystem::path& spriteName);
    GameEntity(const std::filesystem::path& spriteName, const sf::Vector2f& position, float depth = 0);
    ~GameEntity();

    void setPosition(sf::Vector2f position);
    void move(sf::Vector2f translate);
    sf::Vector2f getPosition() const;
    void setActive(bool active);
    bool isActive() const;
    sf::Sprite* getEntitySprite() const;
    void setScale(sf::Vector2f scale) const;
    void setDepth(float depth);
    void setOrigin(sf::Vector2f origin) const;
    void setRotation(sf::Angle angle) const;

    static bool compare(const std::unique_ptr<GameEntity>& first, const std::unique_ptr<GameEntity>& second);
private:
    void updateSpritePosition() const;
    void initializePointers(const std::filesystem::path& spriteName);

    std::unique_ptr<sf::Texture> m_spriteTexture;
    std::unique_ptr<sf::Sprite> m_entitySprite;
    sf::Vector2f m_position;
    bool m_enabled;
    float m_depth;
};
