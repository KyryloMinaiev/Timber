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
    static sf::Vector2f getScaleFactor();
    
private:
    const float k_referencedWidth = 1920;
    const float k_referenceHeight = 1080;
    
    static Screen* s_instance;
    sf::RenderWindow* m_window;
    sf::Vector2f m_scaleFactor;
};


