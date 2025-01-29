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
}

Game::~Game() = default;

void Game::Run()
{
    // GameEntity log("res/graphics/log.png");
    // log.setPosition(Vector2f(810, 720));
    //
    // bool logActive = false;
    // float logSpeedX = 1000;
    // float logSpeedY = -1500;
    //
    Clock clock;
    while (m_window->isOpen())
    {
        m_inputSystem->updateInput();
        // while (const std::optional event = m_window->pollEvent())
        // {
        //     if (event->is<Event::KeyPressed>() && !paused)
        //     {
        //         acceptInput = true;
        //
        //         axe.setPosition(Vector2f(2000, axe.getPosition().y));
        //     }
        // }

        if (InputSystem::isKeyDown(Keyboard::Key::Escape))
        {
            m_window->close();
        }

        if (InputSystem::isKeyDown(Keyboard::Key::Enter) && !m_gameStarted)
        {
            m_eventManager->invokeEvent(EventType::GameStarted);
            m_gameStarted = true;
        }
        // if (acceptInput)
        // {
        //     if (Keyboard::isKeyPressed(Keyboard::Key::Right))
        //     {
        //
        //         log.setPosition(Vector2f(810, 720));
        //         logSpeedX = -5000;
        //         logActive = true;
        //     }
        //
        //     if (Keyboard::isKeyPressed(Keyboard::Key::Left))
        //     {
        //
        //         log.setPosition(Vector2f(810, 720));
        //         logSpeedX = 5000;
        //         logActive = true;
        //     }
        // }
        //
        Time dt = clock.restart();
        //     if (logActive)
        //     {
        //         log.setPosition(
        //             Vector2f(log.getPosition().x +
        //                      (logSpeedX * dt.asSeconds()),
        //
        //                      log.getPosition().y +
        //                      (logSpeedY * dt.asSeconds())));
        //
        //         // Has the log reached the right hand edge?
        //         if (log.getPosition().x < -100 ||
        //             log.getPosition().x > 2000)
        //         {
        //             // Set it up ready to be a whole new log next frame
        //             logActive = false;
        //             log.setPosition(Vector2f(810, 720));
        //         }
        //     }
        // }

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