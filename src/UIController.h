#pragma once
#include <memory>
#include <set>
#include <string>
#include <SFML/System/Vector2.hpp>

#include "EventManager.h"

namespace sf
{
    class RenderWindow;
    class Text;
    class RectangleShape;
    class Drawable;
    class Font;
}

class UIController : public IEventListener
{
public:
    UIController(sf::RenderWindow* window, EventManager* eventManager);
    ~UIController() override;

    static UIController* getInstance();
    
    void onEvent(EventType event) override;
    void drawUI() const;
    void updateTimeBar(float secondsLeft) const;
    void updateScore(int score);
    
private:
    void setupTimeBar(sf::Vector2f screenScale, sf::Vector2u screenSize);

    void onGameStart();
    void onTimeEnded();
    void onPlayerDead();
    void onGameEnd(const std::string& messageText);
    void changeMessageText(const std::string& messageText) const;

    static constexpr int k_timeBarStartWidth = 400;
    static constexpr int k_timeBarStartHeight = 80;
    static constexpr int k_timeBarYPosition = 980;

    sf::Vector2f m_scaledTimeBarSize;
    
    sf::RenderWindow* m_window;
    EventManager* m_eventManager;
    std::unique_ptr<sf::Font> m_mainFont;
    std::unique_ptr<sf::Text> m_messageText;
    std::unique_ptr<sf::Text> m_scoreText;
    std::unique_ptr<sf::RectangleShape> m_timeBar;

    std::set<sf::Drawable*> m_activeUIElements;

    static UIController* s_instance;
};
