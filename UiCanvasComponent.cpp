#include "UiCanvasComponent.h"
void UiCanvasComponent::SetupCanvas()
{
    for (auto& C : GameObject->GetDescendants())
    {
        SpriteRendererComponent* sr = C->GetComponent<SpriteRendererComponent>();
        if (sr == nullptr) continue;

        sr->BindToCanvas(this);
    }
}

void UiCanvasComponent::OnUpdate(float dt){
    if (!Enabled) return;
    if (GameEssentialsGlobals::Renderwindow != nullptr)
    {
        //std::cout << "Rendered!!";

        GameObject->MoveTo(sf::Vector2f(GameEssentialsGlobals::Renderwindow->getPosition()));

    }

}
void UiCanvasComponent ::OnLateUpdate(float dt)
{
    GameEssentialsGlobals::EventH.FireEvent("CanvasUpdate" + std::to_string(this->ID));
}