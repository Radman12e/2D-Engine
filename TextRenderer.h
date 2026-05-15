#pragma once
#include "Component.h"
#include "GameEssentials.h"
class TextRenderer :
    public Component, Renderable
{

public:
    sf::Text text;

    void OnUpdate(float dt) override 
    {
        text.setPosition(GameObject->getWorldPos());
        
    }

    TextRenderer(sf::Font* font, std::string str = "") : text(*font, str)
    {

    }
    void Render() override 
    {
        GameEssentialsGlobals::Renderwindow->draw(text);
    }


    std::unique_ptr<Component> CloneComponent() override
    {
        //return nullptr;
        return std::make_unique<TextRenderer>(*this);
    }


};

