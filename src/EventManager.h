#pragma once
#include <vector>

enum class EventType
{
    GameStarted,
    PlayerCollision,
    PlayerMoved,
    GameEnded,
    TimeEnded
};

class IEventListener
{
public:
    virtual ~IEventListener() = default;
    virtual void onEvent(EventType event) = 0;
};

class EventManager
{
public:
    void invokeEvent(EventType event) const;
    void addEventListener(IEventListener* eventListener);
    void removeEventListener(const IEventListener* eventListener);
private:
    std::vector<IEventListener*> m_eventListeners;
};
