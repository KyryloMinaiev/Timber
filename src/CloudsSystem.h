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
        bool cloudActive;
        float cloudSpeed;
    };

    static void updateCloud(CloudData& cloudData, int index, sf::Time& dt);

    const int k_cloudsCount = 3;
    std::vector<CloudData> m_clouds;
};
