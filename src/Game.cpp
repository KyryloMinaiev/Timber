#include "Game.h"

#include <SFML\Graphics.hpp>

#include "EntitySystem.h"
#include "Screen.h"

#include "EventManager.h"
#include "InputSystem.h"
#include "SoundController.h"
#include "UIController.h"
#include "GameSystems/DefaultWorld.h"
#include "GameSystems/GameplayWorld.h"

using namespace sf;

Game::Game(RenderWindow* window): m_window(window), m_gameStarted(false)
{
    m_screen = std::make_unique<Screen>(window);
    m_entitySystem = std::make_unique<EntitySystem>(window);
    m_eventManager = std::make_unique<EventManager>();
    m_inputSystem = std::make_unique<InputSystem>(window);
    m_uiController = std::make_unique<UIController>(window, m_eventManager.get());
    m_soundController = std::make_unique<SoundController>(m_eventManager.get());
    m_defaultWorld = std::make_unique<DefaultWorld>(m_entitySystem.get(), m_eventManager.get());
    m_gameplayWorld = std::make_unique<GameplayWorld>(m_entitySystem.get(), m_eventManager.get());

    m_eventManager->addEventListener(this);
}

Game::~Game()
{
    m_eventManager->removeEventListener(this);
}

void Game::onEvent(EventType event)
{
    if (event == EventType::PlayerCollision || event == EventType::TimeEnded)
    {
        m_gameStarted = false;
        m_eventManager->invokeEvent(EventType::GameEnded);
    }
}

void Game::Run()
{
    Clock clock;
    while (m_window->isOpen())
    {
        m_inputSystem->updateInput();
        if (InputSystem::isKeyDown(Keyboard::Key::Escape))
        {
            m_window->close();
        }

        if (InputSystem::isKeyDown(Keyboard::Key::Enter) && !m_gameStarted)
        {
            m_eventManager->invokeEvent(EventType::GameStarted);
            m_gameStarted = true;
        }

        Time dt = clock.restart();
        m_defaultWorld->update(dt);

        if (m_gameStarted)
        {
            m_gameplayWorld->update(dt);
        }

        m_window->clear();
        m_entitySystem->drawEntities();
        m_uiController->drawUI();
        m_window->display();
    }
}
