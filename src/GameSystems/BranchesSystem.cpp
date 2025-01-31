#include "BranchesSystem.h"

#include "../EntitySystem.h"
#include "../GameEntity.h"
#include "../Screen.h"

BranchesSystem::BranchesSystem(World* world, EntitySystem* entitySystem, EventManager* eventManager) : GameSystem(world, entitySystem, eventManager), m_seedCounter(0)
{
    auto screenScale = Screen::getScaleFactor();
    
    for (int i = 0; i < k_branchesCount; ++i)
    {
        m_branches.push_back(entitySystem->createEntity("res/graphics/branch.png", sf::Vector2f(), 8));
        m_branches[i]->setOrigin(sf::Vector2f(220, 20));
        m_branches[i]->setScale(screenScale);
        m_branchPositions.push_back(side::NONE);
    }
    
    disableBranches();
    eventManager->addEventListener(this);
}

BranchesSystem::~BranchesSystem()
{
    p_eventManager->removeEventListener(this);
};

void BranchesSystem::onUpdate(sf::Time& dt)
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

side BranchesSystem::getLastBranchSide() const
{
    return m_branchPositions[k_branchesCount - 1];
}

void BranchesSystem::onGameStart()
{
    clearBranchesPositions();
    updateBranches();
}

void BranchesSystem::onGameEnd() const
{
    disableBranches();
}

void BranchesSystem::updateBranches()
{
    m_seedCounter++;
    
    for (int i = k_branchesCount - 1; i > 0; i--)
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
    auto scale = Screen::getScaleFactor();
    
    for (int i = 0; i < k_branchesCount; i++)
    {
        auto branch = m_branches[i];
        branch->setActive(true);
        
        float height = static_cast<float>(i) * k_distanceBetweenBranches * scale.y;
        if (m_branchPositions[i] == side::LEFT)
        {
            branch->setPosition(sf::Vector2f(scale.x * k_leftSidePosition, height));
            branch->setRotation(sf::degrees(180));
        }
        else if (m_branchPositions[i] == side::RIGHT)
        {
            branch->setPosition(sf::Vector2f(scale.x * 1330, height));
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

void BranchesSystem::clearBranchesPositions()
{
    for (auto& branchPosition : m_branchPositions)
    {
        branchPosition = side::NONE;
    }
}
