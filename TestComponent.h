#pragma once
#include "Component.h"
#include <iostream>
#include "EventHandler.h"
#include "GameEssentials.h"
#include <SFML/Window.hpp>
#include "Gameobject.h"
class TestComponent :
    public Component
{
public:
    TestComponent();

    void OnUpdate(float deltaTime) override;
    void OnPhysicsUpdate(float deltaTime) override;
    void OnAlive() override;

    

private:
    void OnWPressed(InputArgs args);
    void OnAPressed(InputArgs args);
    void OnSPressed(InputArgs args);
    void OnDPressed(InputArgs args);
};

