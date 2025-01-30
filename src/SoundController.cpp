#include "SoundController.h"
#include "SFML/Audio.hpp"

SoundController::SoundController(EventManager* eventManager) : m_eventManager(eventManager)
{
    m_chopSound = std::make_unique<sf::SoundBuffer>("res/sound/chop.wav");
    m_deathSound = std::make_unique<sf::SoundBuffer>("res/sound/death.wav");
    m_ootSound = std::make_unique<sf::SoundBuffer>("res/sound/out_of_time.wav");
    m_soundPlayer = std::make_unique<sf::Sound>(*m_chopSound);

    eventManager->addEventListener(this);
    m_eventSoundsMap = {
        {EventType::PlayerMoved, m_chopSound.get()},
        {EventType::PlayerCollision, m_deathSound.get()},
        {EventType::TimeEnded, m_ootSound.get()}
    };
}

SoundController::~SoundController()
{
    m_eventManager->removeEventListener(this);
}

void SoundController::onEvent(EventType event)
{
    if (m_eventSoundsMap.find(event) != m_eventSoundsMap.cend())
    {
        playSoundBuffer(m_eventSoundsMap[event]);
    }
}

void SoundController::playSoundBuffer(const sf::SoundBuffer* soundBuffer) const
{
    m_soundPlayer->setBuffer(*soundBuffer);
    m_soundPlayer->play();
}
