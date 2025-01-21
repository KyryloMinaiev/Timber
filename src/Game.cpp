#include "Game.h"
#include <SFML\Graphics.hpp>

#include "BackgroundSystem.h"
#include "EntitySystem.h"
#include "Screen.h"

#include "BeeSystem.h"
#include "CloudsSystem.h"
#include "EventManager.h"
#include "InputSystem.h"
#include "PlayerSystem.h"

using namespace sf;

Game::Game(RenderWindow* window): m_window(window)
{
    m_screen = std::make_unique<Screen>(window);
    m_entitySystem = std::make_unique<EntitySystem>(window);
    m_eventManager = std::make_unique<EventManager>();
    m_inputSystem = std::make_unique<InputSystem>(window);
    m_gameSystems.push_back(std::make_unique<BackgroundSystem>(m_entitySystem.get(), m_eventManager.get()));
    m_gameSystems.push_back(std::make_unique<CloudsSystem>(m_entitySystem.get(), m_eventManager.get()));
    m_gameSystems.push_back(std::make_unique<BeeSystem>(m_entitySystem.get(), m_eventManager.get()));
    m_gameSystems.push_back(std::make_unique<PlayerSystem>(m_entitySystem.get(), m_eventManager.get()));
}

Game::~Game() = default;

void Game::Run()
{
    //
    // GameEntity player("res/graphics/player.png");
    // player.setPosition(Vector2f(580, 720));
    //
    // side playerSide = side::LEFT;
    //
    // GameEntity deadPlayer("res/graphics/rip.png");
    // deadPlayer.setPosition(Vector2f(600, 860));
    //
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
    //
    // int score = 0;
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
    // bool paused = true;
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
    // Texture textureBranch("res/graphics/branch.png");
    // for (int i = 0; i < NUM_BRANCHES; i++)
    // {
    //     branches.push_back(Sprite(textureBranch));
    //     branches[i].setPosition(Vector2f(-2000, -2000));
    //     branches[i].setOrigin(Vector2f(220, 20));
    //     branchPositions.push_back(side::NONE);
    // }

    bool acceptInput = false;

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

        if (InputSystem::isKeyDown(Keyboard::Key::Enter))
        {
            m_eventManager->invokeEvent(EventType::GameStarted);
            
        //     paused = false;
        //     timeRemaining = 6.0f;
        //     score = 0;
        //
        //     for (int i = 0; i < NUM_BRANCHES; i++)
        //     {
        //         branchPositions[i] = side::NONE;
        //     }
        //
        //     deadPlayer.setPosition(Vector2f(675, 2000));
        //     player.setPosition(Vector2f(580, 720));
        //
        //     acceptInput = true;
        }

        // if (acceptInput)
        // {
        //     if (Keyboard::isKeyPressed(Keyboard::Key::Right))
        //     {
        //         playerSide = side::RIGHT;
        //         score++;
        //
        //         timeRemaining += (2 / score) + 0.15f;
        //         axe.setPosition(Vector2f(AXE_POSITION_RIGHT, axe.getPosition().y));
        //         player.setPosition(Vector2f(1200, 720));
        //
        //         updateBranches(score);
        //
        //         log.setPosition(Vector2f(810, 720));
        //         logSpeedX = -5000;
        //         logActive = true;
        //
        //         acceptInput = false;
        //     }
        //
        //     if (Keyboard::isKeyPressed(Keyboard::Key::Left))
        //     {
        //         playerSide = side::LEFT;
        //         score++;
        //
        //         timeRemaining += (2 / score) + 0.15f;
        //         axe.setPosition(Vector2f(AXE_POSITION_LEFT, axe.getPosition().y));
        //         player.setPosition(Vector2f(580, 720));
        //
        //         updateBranches(score);
        //
        //         log.setPosition(Vector2f(810, 720));
        //         logSpeedX = 5000;
        //         logActive = true;
        //
        //         acceptInput = false;
        //     }
        // }
        //
        // if (!paused)
        // {
        Time dt = clock.restart();
        //
        //     timeRemaining -= dt.asSeconds();
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
        //     for (int i = 0; i < NUM_BRANCHES; i++)
        //     {
        //         float height = i * 150;
        //         if (branchPositions[i] == side::LEFT)
        //         {
        //             branches[i].setPosition(Vector2f(610, height));
        //             branches[i].setRotation(degrees(180));
        //         }
        //         else if (branchPositions[i] == side::RIGHT)
        //         {
        //             branches[i].setPosition(Vector2f(1330, height));
        //             branches[i].setRotation(Angle::Zero);
        //         }
        //         else
        //         {
        //             branches[i].setPosition(Vector2f(3000, height));
        //         }
        //     }
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

        for (auto& gameSystem : m_gameSystems)
        {
            gameSystem->update(dt);
        }

        m_window->clear();
        m_entitySystem->drawEntities();
        //
        // for (int i = 0; i < NUM_BRANCHES; i++)
        // {
        //     window.draw(branches[i]);
        // }
        //
        // player.draw(window);
        // axe.draw(window);
        // log.draw(window);
        // deadPlayer.draw(window);

        // m_window->draw(scoreText);
        // m_window->draw(timeBar);

        // if (paused)
        // {
        //     window.draw(messageText);
        // }

        m_window->display();
    }
}

// void Game::updateBranches(int seed)
// {
//     for (int i = NUM_BRANCHES - 1; i > 0; i--)
//     {
//         branchPositions[i] = branchPositions[i - 1];
//     }
//
//     srand((int)time(0) + seed);
//     int r = (rand() % 5);
//     switch (r)
//     {
//     case 0:
//         branchPositions[0] = side::LEFT;
//         break;
//     case 1:
//         branchPositions[0] = side::RIGHT;
//         break;
//     default:
//         branchPositions[0] = side::NONE;
//         break;
//     }
// }
