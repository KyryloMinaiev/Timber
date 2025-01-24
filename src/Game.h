#pragma once

#include <vector>
#include <memory>
#include "GameSystems/GameSystem.h"

namespace sf
{
    class RenderWindow;
}

class EntitySystem;
class Screen;
class EventManager;
class InputSystem;
class UIController;

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
    std::unique_ptr<InputSystem> m_inputSystem;
    std::unique_ptr<UIController> m_uiController;
    std::vector<std::unique_ptr<GameSystem>> m_alwaysEnabledSystems;
    std::vector<std::unique_ptr<GameSystem>> m_gameplaySystems;
    sf::RenderWindow* m_window;
    std::unique_ptr<Screen> m_screen;

    bool m_gameStarted;
};
