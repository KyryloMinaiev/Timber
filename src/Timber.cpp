// Timber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML\Graphics.hpp>
#include "Game.h"

int main()
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(videoMode, "Timber", sf::State::Fullscreen);
    std::unique_ptr<Game> game = std::make_unique<Game>(&window);
    game->Run();
    return 0;
}
