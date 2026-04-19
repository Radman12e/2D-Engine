#include "Collider.h"

void Collider::SetupCollider(ColliderType CT, bool isTrigger)
{
    std::cout << "Collider madep1!";
    IsTrigger = isTrigger;
    SpriteRendererComponent* Temp = GameObject->GetComponent<SpriteRendererComponent>();
    if (Temp != nullptr)
    {
        BoxRect = (sf::FloatRect)Temp->getRect();
        RectOffset = sf::Vector2f((Temp->getRect().size) / 2);
        Radius = (Temp->getRect().size / 2).x;
    }
    std::cout << "Collider madep2!";
    id = GameEssentialsGlobals::AddCollider(this);
    std::cout << "Collider made!";


    
}

void Collider::OnAlive() 
{

}

Collider::~Collider()
{
    GameEssentialsGlobals::RemoveCollider(id);
}

void Collider::OnUpdate(float dt)
{
    UpdateColliderPos();
}

void Collider::UpdateColliderPos()
{
    BoxRect.position = GameObject->getWorldPos() + RectOffset;
}