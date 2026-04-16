#include "Collider.h"
Collider::Collider(ColliderType CT, bool isTrigger)
{
    IsTrigger = true;
    SpriteRendererComponent* Temp = GameObject->GetComponent<SpriteRendererComponent>();
    if (Temp != nullptr)
    {
        BoxRect = (sf::FloatRect)Temp->getRect();
        RectOffset = sf::Vector2f((Temp->getRect().size) / 2);
        Radius = (Temp->getRect().size / 2).x;
    }
    id = GameEssentialsGlobals::AddCollider(this);

    
}
Collider::~Collider()
{
    GameEssentialsGlobals::RemoveCollider(id);
}

void Collider::OnUpdate(float dt)
{
    BoxRect.position = GameObject->getWorldPos() + RectOffset;
}