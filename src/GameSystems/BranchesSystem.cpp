#include "BranchesSystem.h"

#include "../EntitySystem.h"
#include "../GameEntity.h"

BranchesSystem::BranchesSystem(EntitySystem* entitySystem, EventManager* eventManager) : GameSystem(entitySystem, eventManager), m_seedCounter(0)
{
    for (int i = 0; i < NUM_BRANCHES; ++i)
    {
        m_branches.push_back(entitySystem->createEntity("res/graphics/branch.png", sf::Vector2f(), 8));
        m_branches[i]->setOrigin(sf::Vector2f(220, 20));
        m_branchPositions.push_back(side::NONE);
    }
    
    disableBranches();
    eventManager->addEventListener(this);
}

BranchesSystem::~BranchesSystem()
{
    p_eventManager->removeEventListener(this);
};

void BranchesSystem::update(sf::Time& dt)
{
}

void BranchesSystem::onEvent(EventType event)
{
    if(event == EventType::GameStarted)
    {
        onGameStart();
    }

    if(event == EventType::GameEnded)
    {
        onGameEnd();
    }

    if(event == EventType::PlayerMoved)
    {
        updateBranches();
    }
}

void BranchesSystem::onGameStart()
{
    updateBranches();
}

void BranchesSystem::onGameEnd() const
{
    disableBranches();
}

void BranchesSystem::updateBranches()
{
    m_seedCounter++;
    
    for (int i = NUM_BRANCHES - 1; i > 0; i--)
    {
        m_branchPositions[i] = m_branchPositions[i - 1];
    }

    srand((int)time(0) + m_seedCounter);
    int r = (rand() % 5);
    switch (r)
    {
    case 0:
        m_branchPositions[0] = side::LEFT;
        break;
    case 1:
        m_branchPositions[0] = side::RIGHT;
        break;
    default:
        m_branchPositions[0] = side::NONE;
        break;
    }

    placeBranches();
}

void BranchesSystem::placeBranches() const
{
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        auto branch = m_branches[i];
        branch->setActive(true);
        
        float height = i * 150;
        if (m_branchPositions[i] == side::LEFT)
        {
            branch->setPosition(sf::Vector2f(610, height));
            branch->setRotation(sf::degrees(180));
        }
        else if (m_branchPositions[i] == side::RIGHT)
        {
            branch->setPosition(sf::Vector2f(1330, height));
            branch->setRotation(sf::Angle::Zero);
        }
        else
        {
            branch->setActive(false);
        }
    }
}

void BranchesSystem::disableBranches() const
{
    for (auto branch : m_branches)
    {
        branch->setActive(false);
    }
}
