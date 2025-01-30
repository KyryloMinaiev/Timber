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
    void drawEntities();
    GameEntity* createEntity(const std::filesystem::path& spriteName, sf::Vector2f position, float depth = 0);
    GameEntity* createEntity(const std::filesystem::path& spriteName);
private:
    void sortEntities();
    
    std::vector<std::unique_ptr<GameEntity>> m_entities;
    sf::RenderWindow* m_renderWindow;
};
