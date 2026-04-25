#pragma once
#include "Component.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "GameEssentials.h"

enum CameraType
{
    mainCamera,
    Overlay
};

class CameraComponent :
    public Component
{

public:
    sf::View CameraView;
    CameraType Camera_Type;

  

    void SetupCameraComp(sf::View CamView, CameraType Ctype = CameraType::mainCamera)
    {
        CameraView = CamView;
        Camera_Type = Ctype;

    }

    void OnLateUpdate(float DeltaT) override
    {
        CameraView.setCenter(GameObject->getWorldPos());
        if (Camera_Type == CameraType::mainCamera) 
        {
            GameEssentialsGlobals::Renderwindow->setView(CameraView);
        
        }
       
    }

    std::unique_ptr<Component> CloneComponent() override
    {
        return std::make_unique<CameraComponent>(*this);
    }
    

};

