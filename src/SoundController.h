#pragma once
#include "EventManager.h"
#include <memory>
#include <map>

namespace sf
{
    class SoundBuffer;
    class Sound;
}

class SoundController : public IEventListener
{
public:
    explicit SoundController(EventManager* eventManager);
    ~SoundController() override;
    void onEvent(EventType event) override;
private:
    void playSoundBuffer(const sf::SoundBuffer* soundBuffer) const;
    
    EventManager* m_eventManager;
    std::unique_ptr<sf::SoundBuffer> m_chopSound;
    std::unique_ptr<sf::SoundBuffer> m_deathSound;
    std::unique_ptr<sf::SoundBuffer> m_ootSound;
    std::unique_ptr<sf::Sound> m_soundPlayer;
    std::map<EventType, sf::SoundBuffer*> m_eventSoundsMap;

};
