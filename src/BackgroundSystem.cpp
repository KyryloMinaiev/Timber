#include "BackgroundSystem.h"

#include <iostream>
#include <SFML/Graphics/Sprite.hpp>

#include "EntitySystem.h"
#include "Screen.h"

BackgroundSystem::BackgroundSystem(EntitySystem* entitySystem): GameSystem(entitySystem)
{
    auto screenSize = Screen::getWindowSize();
    createBackground(screenSize);
    createTree(screenSize);
}

BackgroundSystem::~BackgroundSystem() = default;

void BackgroundSystem::update(sf::Time& dt)
{
}

void BackgroundSystem::createBackground(sf::Vector2u screenSize) const
{
    auto background = entitySystem->createEntity("res/graphics/background.png", sf::Vector2f(0, 0), -100);
    auto backgroundSprite = background->getEntitySprite();
    auto backgroundSpriteSize = backgroundSprite->getTextureRect().size;
    float backgroundScale = static_cast<float>(screenSize.y) / static_cast<float>(backgroundSpriteSize.y);
    background->setScale(sf::Vector2f(backgroundScale, backgroundScale));
}

void BackgroundSystem::createTree(sf::Vector2u screenSize) const
{
    auto tree = entitySystem->createEntity("res/graphics/tree.png");
    float treeScale = static_cast<float>(screenSize.x) / 1920;
    tree->setScale(sf::Vector2f(treeScale, treeScale));
    float treePosition = k_defaultTreePosition * treeScale;
    tree->setPosition(sf::Vector2f(treePosition, 0));
}
