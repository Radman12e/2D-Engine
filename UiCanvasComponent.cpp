#include "UiCanvasComponent.h"
#include "Renderable.h";
void UiCanvasComponent::SetupCanvas()
{
    for (auto& C : GameObject->GetDescendants())
    {
        Renderable* sr = C->GetComponent<Renderable>();
        
        
        if (sr == nullptr) continue;
        std::cout << "RenderableFound";
        sr->UpdateLayer(2000 + sr->GetLayer());
        //sr->BindToCanvas(this);
    }
}

void UiCanvasComponent::OnUpdate(float dt){
    if (!Enabled) return;
    if (GameEssentialsGlobals::Renderwindow != nullptr)
    {
        //std::cout << "Rendered!!" << GameEssentialsGlobals::Renderwindow->getView().getCenter().x << "\n";

        GameObject->MoveTo(sf::Vector2f(GameEssentialsGlobals::Renderwindow->getView().getCenter()));

    }

}

void UiCanvasComponent::OnPhysicsUpdate(float dt) {
    if (!Enabled) return;
    if (GameEssentialsGlobals::Renderwindow != nullptr)
    {
        //std::cout << "Rendered!!" << GameEssentialsGlobals::Renderwindow->getView().getCenter().x << "\n";

        GameObject->MoveTo(sf::Vector2f(GameEssentialsGlobals::Renderwindow->getView().getCenter()));

    }

}
void UiCanvasComponent ::OnLateUpdate(float dt)
{
    if (GameEssentialsGlobals::Renderwindow != nullptr)
    {
        //std::cout << "Rendered!!" << GameEssentialsGlobals::Renderwindow->getView().getCenter().x << "\n";

        GameObject->MoveTo(sf::Vector2f(GameEssentialsGlobals::Renderwindow->getView().getCenter()));

    }
    //GameEssentialsGlobals::EventH.FireEvent("CanvasUpdate" + std::to_string(this->ID));
    
}