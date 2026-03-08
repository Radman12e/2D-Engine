#pragma once
#include "Component.h"
class TestComponent :
    public Component
{
    void OnUpdate(float deltaTime) override;
};

