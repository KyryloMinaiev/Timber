#include "UIController.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>

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
    if (event == EventType::GameStarted)
    {
        onGameStart();
    }

    if (event == EventType::TimeEnded)
    {
        onTimeEnded();
    }

    if (event == EventType::PlayerCollision)
    {
        onPlayerDead();
    }
}

UIController::UIController(sf::RenderWindow* window, EventManager* eventManager) : m_window(window),
    m_eventManager(eventManager)
{
    s_instance = this;
    m_mainFont = std::make_unique<sf::Font>("res/fonts/KOMIKAP_.ttf");
    auto screenScale = Screen::getScaleFactor();
    auto screenSize = Screen::getWindowSize();
    m_messageText = std::make_unique<sf::Text>(*m_mainFont, "", 75);
    m_scoreText = std::make_unique<sf::Text>(*m_mainFont, "Score = 0", 100);
    setupTimeBar(screenScale, screenSize);
    onGameEnd("Press Enter to start!");
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
    std::stringstream ss;
    ss << "Score = " << score;
    m_scoreText->setString(ss.str());
}

void UIController::setupTimeBar(sf::Vector2f screenScale, sf::Vector2u screenSize)
{
    m_scaledTimeBarSize = sf::Vector2f(screenScale.x * k_timeBarStartWidth, screenScale.y * k_timeBarStartHeight);
    m_timeBar = std::make_unique<sf::RectangleShape>(sf::Vector2f(m_scaledTimeBarSize));
    m_timeBar->setFillColor(sf::Color::Red);
    m_timeBar->setPosition(sf::Vector2f((static_cast<float>(screenSize.x) / 2) - m_scaledTimeBarSize.x / 2,
                                        k_timeBarYPosition * screenScale.y));
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

void UIController::onGameEnd(const std::string& messageText)
{
    m_activeUIElements.insert(m_messageText.get());
    m_activeUIElements.erase(m_scoreText.get());
    m_activeUIElements.erase(m_timeBar.get());

    changeMessageText(messageText);
}

void UIController::changeMessageText(const std::string& messageText) const
{
    m_messageText->setString(messageText);
    auto rect = m_messageText->getLocalBounds();
    auto screenSize = Screen::getWindowSize();
    m_messageText->setOrigin(sf::Vector2f
        (
            rect.position.x + rect.size.x / 2,
            rect.position.y + rect.size.y / 2
        ));
    m_messageText->setPosition(sf::Vector2f(screenSize.x / 2, screenSize.y / 2));
}
