#pragma once

#include <SFML\Graphics.hpp>
#include "GameEntity.h"
#include <sstream>
#include <vector>

using namespace sf;

class Game
{
public:
    void Run(RenderWindow& window);
private:
    const float TREE_HORIZONTAL_POSITION = 810;
    const float TREE_VERTICAL_POSITION = 0;

    const float START_BEE_HORIZONTAL_POSITION = 0;
    const float START_BEE_VERTICAL_POSITION = 800;

    void updateBranches(int seed);

    const int NUM_BRANCHES = 6;
    std::vector<Sprite> branches;
    enum class side {LEFT, RIGHT, NONE};
    std::vector<side> branchPositions;
};
