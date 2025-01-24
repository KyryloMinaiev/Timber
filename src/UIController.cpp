#include "UIController.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Screen.h"

UIController* UIController::s_instance;

UIController::~UIController()
{
    m_eventManager->removeEventListener(this);
}

UIController* UIController::getInstance()
{
    return s_instance;
};

void UIController::onEvent(EventType event)
{
    if(event == EventType::GameStarted)
    {
        onGameStart();
    }

    if(event == EventType::TimeEnded)
    {
        onTimeEnded();
    }

    if(event == EventType::PlayerCollision)
    {
        onPlayerDead();
    }
}

UIController::UIController(sf::RenderWindow* window, EventManager* eventManager) : m_window(window), m_eventManager(eventManager)
{
    s_instance = this;
    sf::Font font("res/fonts/KOMIKAP_.ttf");
    auto screenScale = Screen::getScaleFactor();
    auto screenSize = Screen::getWindowSize();
    m_messageText = std::make_unique<sf::Text>(font, "Press Enter to start!", 75);
    m_scoreText = std::make_unique<sf::Text>(font, "Score = 0", 100);
    setupTimeBar(screenScale, screenSize);

    m_activeUIElements.insert(m_messageText.get());
    eventManager->addEventListener(this);
}

void UIController::drawUI() const
{
    for (auto element : m_activeUIElements)
    {
        m_window->draw(*element);
    }
}

void UIController::updateTimeBar(float secondsLeft) const
{
    m_timeBar->setSize(sf::Vector2f(secondsLeft * m_scaledTimeBarSize.x, m_scaledTimeBarSize.y));
}

void UIController::updateScore(int score)
{
}

void UIController::setupTimeBar(sf::Vector2f screenScale, sf::Vector2u screenSize)
{
    m_scaledTimeBarSize = sf::Vector2f(screenScale.x * k_timeBarStartWidth, screenScale.y * k_timeBarStartHeight);
    m_timeBar = std::make_unique<sf::RectangleShape>(sf::Vector2f(m_scaledTimeBarSize));
    m_timeBar->setFillColor(sf::Color::Red);
    m_timeBar->setPosition(sf::Vector2f((static_cast<float>(screenSize.x) / 2) - m_scaledTimeBarSize.x / 2, k_timeBarYPosition * screenScale.y));
}

void UIController::onGameStart()
{
    m_activeUIElements.erase(m_messageText.get());
    m_activeUIElements.insert(m_scoreText.get());
    m_activeUIElements.insert(m_timeBar.get());
}

void UIController::onTimeEnded()
{
    onGameEnd("Time Ended!");
}

void UIController::onPlayerDead()
{
    onGameEnd("Player Died!");
}

void UIController::onGameEnd(std::string messageText)
{
    m_activeUIElements.insert(m_messageText.get());
    m_messageText->setString(messageText);
    m_activeUIElements.erase(m_scoreText.get());
    m_activeUIElements.erase(m_timeBar.get());
}
