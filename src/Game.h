#pragma once

#include <vector>
#include <memory>

#include "EventManager.h"
#include "GameSystems/GameSystem.h"

namespace sf
{
    class RenderWindow;
}

class EntitySystem;
class Screen;
class EventManager;
class InputSystem;
class UIController;
class SoundController;
class DefaultWorld;
class GameplayWorld;

class Game : public IEventListener
{
public:
    Game(sf::RenderWindow* window);
    ~Game() override;

    void onEvent(EventType event) override;
    void Run();
private:
    std::unique_ptr<EntitySystem> m_entitySystem;
    std::unique_ptr<EventManager> m_eventManager;
    std::unique_ptr<InputSystem> m_inputSystem;
    std::unique_ptr<UIController> m_uiController;
    std::unique_ptr<SoundController> m_soundController;
    std::unique_ptr<DefaultWorld> m_defaultWorld;
    std::unique_ptr<GameplayWorld> m_gameplayWorld;
    
    sf::RenderWindow* m_window;
    std::unique_ptr<Screen> m_screen;

    bool m_gameStarted;
};
