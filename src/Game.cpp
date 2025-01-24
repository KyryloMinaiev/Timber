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
    // GameEntity axe("res/graphics/axe.png");
    // axe.setPosition(Vector2f(700, 830));
    //
    // const float AXE_POSITION_LEFT = 700;
    // const float AXE_POSITION_RIGHT = 1075;
    //
    // GameEntity log("res/graphics/log.png");
    // log.setPosition(Vector2f(810, 720));
    //
    // bool logActive = false;
    // float logSpeedX = 1000;
    // float logSpeedY = -1500;
    //
    // Font font("res/fonts/KOMIKAP_.ttf");
    // Text messageText(font, "Press Enter to start!", 75);
    // Text scoreText(font, "Score = 0", 100);
    //
    // messageText.setFillColor(Color::White);
    // scoreText.setFillColor(Color::White);
    //
    // FloatRect textRect = messageText.getLocalBounds();
    // messageText.setOrigin(Vector2f(textRect.position.x +
    //                                textRect.size.x / 2.0f,
    //                                textRect.position.y +
    //                                textRect.size.y / 2.0f));
    // messageText.setPosition(Vector2f(1920 / 2.0f, 1080 / 2.0f));
    // scoreText.setPosition(Vector2f(20, 20));
    //
    Clock clock;
    //
    // float timeBarStartWidth = 400;
    // float timeBarHeight = 80;
    // RectangleShape timeBar(Vector2f(400, 80));
    // timeBar.setFillColor(Color::Red);
    // timeBar.setPosition(Vector2f((1920 / 2) - timeBarStartWidth / 2, 980));
    //
    // Time gameTimeTotal;
    // float timeRemaining = 6.0f;
    // float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
    //
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
        //         axe.setPosition(Vector2f(AXE_POSITION_RIGHT, axe.getPosition().y));
        //
        //         log.setPosition(Vector2f(810, 720));
        //         logSpeedX = -5000;
        //         logActive = true;
        //     }
        //
        //     if (Keyboard::isKeyPressed(Keyboard::Key::Left))
        //     {
        //         axe.setPosition(Vector2f(AXE_POSITION_LEFT, axe.getPosition().y));
        //
        //         log.setPosition(Vector2f(810, 720));
        //         logSpeedX = 5000;
        //         logActive = true;
        //     }
        // }
        //
        Time dt = clock.restart();
        //
        //     timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
        //     if (timeRemaining <= 0.0f)
        //     {
        //         paused = true;
        //         messageText.setString("Out of time!");
        //
        //         FloatRect textRect = messageText.getLocalBounds();
        //         messageText.setOrigin(Vector2f(textRect.position.x +
        //                                        textRect.size.x / 2.0f,
        //                                        textRect.position.y +
        //                                        textRect.size.y / 2.0f));
        //         messageText.setPosition(Vector2f(1920 / 2.0f, 1080 / 2.0f));
        //     }
        //
        //
        //     std::stringstream ss;
        //     ss << "Score = " << score;
        //     scoreText.setString(ss.str());
        //
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

        // m_window->draw(scoreText);
        // m_window->draw(timeBar);

        // if (paused)
        // {
        //     window.draw(messageText);
        // }

        m_window->display();
    }
}