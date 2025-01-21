#include "InputSystem.h"

#include <optional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

InputSystem* InputSystem::s_instance;

InputSystem::InputSystem(sf::RenderWindow* renderWindow) : m_window(renderWindow)
{
    s_instance = this;
}

InputSystem::~InputSystem() = default;

void InputSystem::updateInput()
{
    m_buttonsUp.clear();
    
    while (const std::optional event = m_window->pollEvent())
    {
        if (event->is<sf::Event::KeyPressed>())
        {
            const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>();
            checkPressedButton(keyPressed->code);
            continue;
        }

        if (event->is<sf::Event::KeyReleased>())
        {
            const sf::Event::KeyReleased* keyReleased = event->getIf<sf::Event::KeyReleased>();
            checkReleasedButton(keyReleased->code);
        }
    }
}

bool InputSystem::isKeyDown(sf::Keyboard::Key key)
{
    return checkInSet(key, s_instance->m_buttonsDown);
}

bool InputSystem::isKeyPressed(sf::Keyboard::Key key)
{
    return checkInSet(key, s_instance->m_buttonsPressed);
}

bool InputSystem::isKeyUp(sf::Keyboard::Key key)
{
    return checkInSet(key, s_instance->m_buttonsUp);
}

bool InputSystem::checkInSet(sf::Keyboard::Key key, std::set<sf::Keyboard::Key> set)
{
    return set.find(key) != set.cend();
}

void InputSystem::checkPressedButton(sf::Keyboard::Key key)
{
    bool isAlreadyDown = checkInSet(key, m_buttonsDown);      
    bool isAlreadyPressed = checkInSet(key, m_buttonsPressed);
    if(isAlreadyDown && !isAlreadyPressed)                                 
    {                                                                      
        m_buttonsDown.erase(key);                             
        m_buttonsPressed.insert(key);                         
    }                                                                      
                                                                       
    if(!isAlreadyPressed && !isAlreadyDown)                                
    {                                                                      
        m_buttonsDown.insert(key);                            
    }                                                                      
}

void InputSystem::checkReleasedButton(sf::Keyboard::Key key)
{
    if(checkInSet(key, m_buttonsPressed))
    {
        m_buttonsPressed.erase(key);
    }

    if(checkInSet(key, m_buttonsDown))
    {
        m_buttonsDown.erase(key);
    }

    m_buttonsUp.insert(key);
}
