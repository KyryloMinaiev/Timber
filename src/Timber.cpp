// Timber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML\Graphics.hpp>

using namespace sf;

int main()
{
    VideoMode videoMode(Vector2u(1920, 1080));
    RenderWindow window(videoMode, "Timber", State::Fullscreen);

    while (window.isOpen()) {
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
            window.close();
        }
    }

    return 0;
}
