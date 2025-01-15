#pragma once
#include <filesystem>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include "GameEntity.h"

namespace sf
{
    class RenderWindow;
}

class EntitySystem
{
public:
    EntitySystem(sf::RenderWindow* window);
    void drawEntities() const;
    GameEntity* createEntity(const std::filesystem::path& spriteName, sf::Vector2f position);
    GameEntity* createEntity(const std::filesystem::path& spriteName);
private:
    std::vector<std::unique_ptr<GameEntity>> m_entities;
    sf::RenderWindow* m_renderWindow;
};
