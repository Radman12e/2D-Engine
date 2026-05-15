#pragma once
#include "Component.h"
#include "Gameobject.h"
#include "SpriteRendererComponent.h"
#include "GameEssentials.h"
class UiCanvasComponent :
    public Component
{
public:
    size_t ID;
    void OnUpdate(float dt) override;
    
    void OnLateUpdate(float dt) override;
    void OnPhysicsUpdate(float dt) override;

    UiCanvasComponent() 
    {
        ID = std::rand() % 65535;
    }

    ~UiCanvasComponent()
    {
        
    }
    void SetupCanvas();

};

