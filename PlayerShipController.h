#pragma once
#include "Component.h"
#include <iostream>
#include "EventHandler.h"
#include "GameEssentials.h"
#include <SFML/Window.hpp>
#include "Gameobject.h"

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

    PlayerShipController() 
    {
    
    }

    void OnUpdate(float deltaTime) override;
    void OnPhysicsUpdate(float deltaTime) override;
    void OnAlive() override;

    std::unique_ptr<Component> CloneComponent() override
    {
        return std::make_unique<PlayerShipController>(*this);
    }

    ~PlayerShipController() = default;

private:
    void OnWPressed(InputArgs args);
    void OnAPressed(InputArgs args);
    void OnSPressed(InputArgs args);
    void OnDPressed(InputArgs args);
};

