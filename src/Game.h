#pragma once

#include <vector>
#include <memory>
#include "GameSystem.h"

namespace sf
{
    class RenderWindow;
}

class EntitySystem;
class Screen;
class EventManager;

class Game
{
public:
    Game(sf::RenderWindow* window);
    ~Game();
    
    void Run();
private:
    // const float TREE_HORIZONTAL_POSITION = 810;
    // const float TREE_VERTICAL_POSITION = 0;
    //
    //
    // void updateBranches(int seed);
    //
    // const int NUM_BRANCHES = 6;
    // //std::vector<Sprite> branches;
    // enum class side {LEFT, RIGHT, NONE};
    // std::vector<side> branchPositions;

    std::unique_ptr<EntitySystem> m_entitySystem;
    std::unique_ptr<EventManager> m_eventManager;
    std::vector<std::unique_ptr<GameSystem>> m_gameSystems;
    sf::RenderWindow* m_window;
    std::unique_ptr<Screen> m_screen;
};
