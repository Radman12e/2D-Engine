#pragma once
#include "Component.h"
#include "GameEssentials.h"
class TextRenderer :
    public Component
{

public:
    sf::Text text;

    void OnUpdate(float dt) override 
    {
        text.setPosition(GameObject->getWorldPos());
        GameEssentialsGlobals::Renderwindow->draw(text);
    }

    TextRenderer(sf::Font* font, std::string str = "") : text(*font, str)
    {

    }

    std::unique_ptr<Component> CloneComponent() override
    {
        //return nullptr;
        return std::make_unique<TextRenderer>(*this);
    }


};

