#include "Screen.h"

#include <SFML/Graphics/RenderWindow.hpp>

Screen* Screen::s_instance;

Screen::Screen(sf::RenderWindow* window) : m_window(window)
{
    s_instance = this;
}

sf::Vector2u Screen::getWindowSize()
{
    return s_instance->m_window->getSize();
}
