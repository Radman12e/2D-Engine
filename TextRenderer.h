#pragma once
#include "Component.h"
#include "GameEssentials.h"
class TextRenderer :
    public Component, public Renderable
{
    
public:
    sf::Text text;
    bool Setup = false;

    void OnUpdate(float dt) override 
    {
        if (Setup == false)
        {
            Setup = true;
            GameEssentialsGlobals::AddSpriteToRenderLayer(this, this->GetLayer());
            std::cout << "textSetup!";
        }
        text.setPosition(GameObject->getWorldPos());
        
    }

    TextRenderer(sf::Font* font, std::string str = "", int Layer = 10) : text(*font, str)
    {
        this->Layer = Layer;
        //Setup = true;
    }
    void Render() override 
    {
        if (!Enabled) return;
        if (GameEssentialsGlobals::Renderwindow != nullptr)
        {
            //std::cout << "\nRendered!!\n Layer: " << Layer;
            GameEssentialsGlobals::Renderwindow->draw(text);
        }
    }


    std::unique_ptr<Component> CloneComponent() override
    {
        //return nullptr;

        std::unique_ptr<TextRenderer> temp = std::make_unique<TextRenderer>(*this);
        temp.get()->Setup = false;
        return temp;
    }


};

