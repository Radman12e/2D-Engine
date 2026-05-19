#pragma once
#include "Component.h"
#include <iostream>
#include "EventHandler.h"
#include "GameEssentials.h"
#include <SFML/Window.hpp>
#include "Gameobject.h"
#include "HealthComponent.h"

class WeaponComponent;

class PlayerShipController :
    public Component
{
public:

    float SpeedMulti = 1;

    bool WHeld = false;
    bool AHeld = false;
    bool SHeld = false;
    bool DHeld = false;
    bool Setup1 = false;
    float BeamHeldTime = 0;
    bool SpaceHeld = false;

    BasicGunComponent* PeaShooter = nullptr;

    PlayerShipController() 
    {
    
    }
    void Setup() 
    {
        for (auto a : GameObject->GetDescendants()) 
        {
            if (a->GetComponent<BasicGunComponent>()) 
            {
                PeaShooter = a->GetComponent<BasicGunComponent>();
            }
        }
    }
    void OnUpdate(float deltaTime) override;
    void OnPhysicsUpdate(float deltaTime) override;
    void OnAlive() override;

    std::unique_ptr<Component> CloneComponent() override
    {
        auto a = std::make_unique<PlayerShipController>(*this);
        a.get()->Setup1 = false;
        return a;
    }

    ~PlayerShipController() = default;

private:
    void OnWPressed(InputArgs args);
    void OnAPressed(InputArgs args);
    void OnSPressed(InputArgs args);
    void OnDPressed(InputArgs args);
    void OnSpacePressed(InputArgs args);
};

