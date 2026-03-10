#pragma once
#include "Component.h"
class TestComponent :
    public Component
{
    void OnUpdate(float deltaTime) override;
    void OnPhysicsUpdate(float deltaTime) override;
};

