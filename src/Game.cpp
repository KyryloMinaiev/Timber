#include "Game.h"

#include <SFML\Graphics.hpp>

#include "GameSystems/BackgroundSystem.h"
#include "EntitySystem.h"
#include "Screen.h"

#include "GameSystems/BeeSystem.h"
#include "GameSystems/CloudsSystem.h"
#include "EventManager.h"
#include "InputSystem.h"
#include "UIController.h"
#include "GameSystems/BranchesSystem.h"
#include "GameSystems/GameTimeSystem.h"
#include "GameSystems/LogSystem.h"
#include "GameSystems/PlayerSystem.h"

using namespace sf;

Game::Game(RenderWindow* window): m_window(window), m_gameStarted(false)
{
    m_screen = std::make_unique<Screen>(window);
    m_entitySystem = std::make_unique<EntitySystem>(window);
    m_eventManager = std::make_unique<EventManager>();
    m_inputSystem = std::make_unique<InputSystem>(window);
    m_uiController = std::make_unique<UIController>(window, m_eventManager.get());
    m_alwaysEnabledSystems.push_back(std::make_unique<BackgroundSystem>(m_entitySystem.get(), m_eventManager.get()));
    m_alwaysEnabledSystems.push_back(std::make_unique<CloudsSystem>(m_entitySystem.get(), m_eventManager.get()));
    m_alwaysEnabledSystems.push_back(std::make_unique<BeeSystem>(m_entitySystem.get(), m_eventManager.get()));
    m_gameplaySystems.push_back(std::make_unique<PlayerSystem>(m_entitySystem.get(), m_eventManager.get()));
    m_gameplaySystems.push_back(std::make_unique<BranchesSystem>(m_entitySystem.get(), m_eventManager.get()));
    m_gameplaySystems.push_back(std::make_unique<GameTimeSystem>(m_entitySystem.get(), m_eventManager.get()));
    m_gameplaySystems.push_back(std::make_unique<LogSystem>(m_entitySystem.get(), m_eventManager.get()));

    m_eventManager->addEventListener(this);
}

Game::~Game()
{
    m_eventManager->removeEventListener(this);
}

void Game::onEvent(EventType event)
{
    if(event == EventType::PlayerCollision || event == EventType::TimeEnded)
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
        for (auto& gameSystem : m_alwaysEnabledSystems)
        {
            gameSystem->update(dt);
        }

        if(m_gameStarted)
        {
            for (auto& gameSystem : m_gameplaySystems)
            {
                gameSystem->update(dt);
            }
        }

        m_window->clear();
        m_entitySystem->drawEntities();
        m_uiController->drawUI();
        m_window->display();
    }
}
