#include "Screen.h"

#include <SFML/Graphics/RenderWindow.hpp>

Screen* Screen::s_instance;

Screen::Screen(sf::RenderWindow* window) : m_window(window)
{
    s_instance = this;

    auto size = getWindowSize();
    m_scaleFactor.x = static_cast<float>(size.x) / k_referencedWidth;
    m_scaleFactor.y = static_cast<float>(size.y) / k_referenceHeight;
}

sf::Vector2u Screen::getWindowSize()
{
    return s_instance->m_window->getSize();
}

sf::Vector2f Screen::getScaleFactor()
{
    return s_instance->m_scaleFactor;
}
