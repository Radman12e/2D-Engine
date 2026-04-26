#include "Rigidbody.h"
#include "CollisionEventsinterface.h"
#include "Collider.h" 
#include "Gameobject.h"

std::vector<ColliderStruct> Rigidbody::GetAllColliders(Gameobject* CurrentObject)
{
    std::vector<ColliderStruct> colliders;

    Collider* col = CurrentObject->GetComponent<Collider>();
    if (col != nullptr)
    {
        colliders.push_back({col, col->GetID()});
    }

    for (Gameobject* child : CurrentObject->GetChildren())
    {
        std::vector<ColliderStruct> childColliders = GetAllColliders(child);

        colliders.insert(
            colliders.end(),
            childColliders.begin(),
            childColliders.end()
        );
    }

    return colliders;
}

Rigidbody::Rigidbody() : Component()
{
    id = GameEssentialsGlobals::AddRigidbody(this);
}
Rigidbody::~Rigidbody() 
{
    UnbindAllEvents();
    Colliders.clear();
    GameEssentialsGlobals::RemoveRB(this->id);

}

void Rigidbody::OnPhysicsUpdate(float dt)
{
    
    //AppliedVelocity = Velocity;
    GameObject->MoveTo(GameObject->getWorldPos() + AppliedVelocity * dt);
    UpdateColliderPositions();

    sf::Vector2f correction = GameEssentialsGlobals::CollisionCheckRB(this);


    if (correction.x != 0.f || correction.y != 0.f)
    {
        GameObject->MoveTo(GameObject->getWorldPos() + correction);
        UpdateColliderPositions();
        //UpdateColliderPositions();

        if (correction.y != 0.f) AppliedVelocity.y = 0.f;
        if (correction.x != 0.f) AppliedVelocity.x = 0.f;
    }
    else
    {
        AppliedVelocity = Velocity;
    }
}


void Rigidbody::OnUpdate(float detlatime)
{

    AppliedVelocity = Velocity;
    
}

bool Rigidbody::FindCollider(size_t ID)
{
    if (Colliders.empty()) {
        return false;
    }

    return std::find_if(Colliders.begin(), Colliders.end(),
        [ID](const ColliderStruct& c) {
            return c.id == ID;
        }) != Colliders.end();
}


void Rigidbody::UpdateColliderPositions()
{
    for (ColliderStruct c : Colliders)
    {
        c.collider->UpdateColliderPos();
    }
}
std::unique_ptr<Component> Rigidbody::CloneComponent()
{
    auto c = std::make_unique<Rigidbody>(*this);
    c->id = GameEssentialsGlobals::AddRigidbody(c.get());
    c->InitRB();

    return c;
}