#pragma once
#include "GameSystem.h"
#include <vector>

class GameEntity;

class CloudsSystem : public GameSystem
{
public:
    CloudsSystem(EntitySystem* entitySystem, EventManager* eventManager);
    ~CloudsSystem() override;
    
    void update(sf::Time& dt) override;
private:
    struct CloudData
    {
        GameEntity* cloudEntity;
        float cloudSpeed;
    };

    static void updateCloud(CloudData& cloudData, int index, sf::Time& dt);

    static constexpr int k_cloudsCount = 3;
    std::vector<CloudData> m_clouds;
};
