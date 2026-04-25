#pragma once
#include "Component.h"
#include "EventHandler.h"
class PlayerController :
    public Component
{
public:
    virtual void OnUpInput(InputArgs IA) 
    {
        
    }
    virtual void OnDownInput(InputArgs IA)
    {

    }
    virtual void OnLeftInput(InputArgs IA)
    {

    }
    virtual void OnRightInput(InputArgs IA)
    {

    }
    virtual void OnButton1(InputArgs IA)
    {

    }
    virtual void OnButton2(InputArgs IA)
    {

    }
    virtual std::unique_ptr<Component> CloneComponent()
    {
        return std::make_unique<PlayerController>(*this);
    }


};

