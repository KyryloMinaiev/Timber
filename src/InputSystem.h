#pragma once

#include <set>
#include <SFML/Window/Keyboard.hpp>

namespace sf
{
    class RenderWindow;
}


class InputSystem
{
public:
    InputSystem(sf::RenderWindow* renderWindow);
    ~InputSystem();
    void updateInput();

    static bool isKeyDown(sf::Keyboard::Key key);
    static bool isKeyPressed(sf::Keyboard::Key key);
    static bool isKeyUp(sf::Keyboard::Key key);
private:
    static bool checkInSet(sf::Keyboard::Key key, std::set<sf::Keyboard::Key> set);
    
    void checkPressedButton(sf::Keyboard::Key key);
    void checkReleasedButton(sf::Keyboard::Key key);

    static InputSystem* s_instance;
    sf::RenderWindow* m_window;
    std::set<sf::Keyboard::Key> m_buttonsDown;
    std::set<sf::Keyboard::Key> m_buttonsPressed;
    std::set<sf::Keyboard::Key> m_buttonsUp;
};
