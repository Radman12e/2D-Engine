#pragma once
#include "Component.h"
#include "Gameobject.h"
class SideScrollerHandler : public Component
{
public:
    float Speed;

    std::unique_ptr<Component> CloneComponent() override
    {
        return std::make_unique<SideScrollerHandler>(*this);
    }

    void OnUpdate(float dt) 
    {
        GameObject->MoveTo({ GameObject->getWorldPos().x + Speed * dt, GameObject->getWorldPos().y });
    }
};

