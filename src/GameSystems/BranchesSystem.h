#pragma once
#include <SFML/System/Vector2.hpp>

#include "GameSystem.h"
#include "Sides.h"
#include "../EventManager.h"

class GameEntity;

class BranchesSystem : public GameSystem, public IEventListener
{
public:
    BranchesSystem(EntitySystem* entitySystem, EventManager* eventManager);
    ~BranchesSystem() override;
    void update(sf::Time& dt) override;
    void onEvent(EventType event) override;
private:
    void onGameStart();
    void onGameEnd() const;

    void updateBranches();
    void placeBranches() const;
    void disableBranches() const;

    static constexpr int k_branchesCount = 6;
    static constexpr float k_distanceBetweenBranches = 150;
    static constexpr float k_leftSidePosition = 590;
    static constexpr float k_rightSidePosition = 1330;
    
    int m_seedCounter;
    std::vector<GameEntity*> m_branches;
    std::vector<side> m_branchPositions;
};
