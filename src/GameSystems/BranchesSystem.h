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

    const int NUM_BRANCHES = 6;
    int m_seedCounter;
    std::vector<GameEntity*> m_branches;
    std::vector<side> m_branchPositions;
};
