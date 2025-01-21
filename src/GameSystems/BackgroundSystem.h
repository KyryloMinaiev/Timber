﻿#pragma once
#include <SFML/System/Vector2.hpp>

#include "GameSystem.h"

class GameEntity;

class BackgroundSystem : public GameSystem
{
public:
    BackgroundSystem(EntitySystem* entitySystem, EventManager* eventManager);
    ~BackgroundSystem() override;
    void update(sf::Time& dt) override;
private:
    static constexpr float k_defaultTreePosition = 810;
    
    void createBackground(sf::Vector2u screenSize) const;
    void createTree(sf::Vector2u screenSize) const;
};
