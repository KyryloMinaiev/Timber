#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
using namespace sf;

class GameEntity {
public:
    GameEntity(const std::filesystem::path& spriteName);
    GameEntity(const std::filesystem::path& spriteName, const Vector2f& position);
    ~GameEntity();

    void setPosition(Vector2f position);
    void draw(RenderWindow& window) const;
    void move(Vector2f translate);
    Vector2f getPosition() const;
    void setActive(bool active);
    bool isActive() const;
        
private:
    void updateSpritePosition() const;
    void initializePointers(const std::filesystem::path& spriteName);

    std::unique_ptr<Texture> m_spriteTexture;
    std::unique_ptr<Sprite> m_entitySprite;
    Vector2f m_position;
    bool m_enabled;
};
