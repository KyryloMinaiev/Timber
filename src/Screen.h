#pragma once
#include <SFML/System/Vector2.hpp>

namespace sf
{
    class RenderWindow;
}

class Screen
{
public:
    Screen(sf::RenderWindow* window);
    static sf::Vector2u getWindowSize();
    
private:
    static Screen* s_instance;
    sf::RenderWindow* m_window;
};


