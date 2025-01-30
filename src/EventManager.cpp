#include "EventManager.h"

void EventManager::invokeEvent(EventType event) const
{
    for (auto eventListener : m_eventListeners)
    {
        eventListener->onEvent(event);
    }
}

void EventManager::addEventListener(IEventListener* eventListener)
{
    m_eventListeners.push_back(eventListener);
}

void EventManager::removeEventListener(const IEventListener* eventListener)
{
    auto it = std::find(m_eventListeners.begin(), m_eventListeners.end(), eventListener);
    m_eventListeners.erase(it);
}
