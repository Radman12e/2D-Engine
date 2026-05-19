#include "Component.h"
#include "Component.h"
#include <iostream>
#include "EventHandler.h"
#include "GameEssentials.h"
#include <SFML/Window.hpp>
#include "Gameobject.h"
#pragma once
class MainMenuHandler : public Component
{
public:
	~MainMenuHandler() = default;
    Scene* NextScene = nullptr;
    bool Trans = false;
    std::unique_ptr<Component> CloneComponent() override
    {
        return std::make_unique<MainMenuHandler>(*this);
    }
    void OnAlive() override;
};

