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

    sf::Vector2f totalCorrection = { 0, 0 };

    for (auto& colStruct : Colliders)
    {
        Collider* myCol = colStruct.collider;

        auto it = GameEssentialsGlobals::BroadPhasePairs.find(myCol);
        if (it == GameEssentialsGlobals::BroadPhasePairs.end())
            continue;

        for (Collider* other : it->second)
        {
            sf::Vector2f offset = myCol->CheckCollision(other);

            if (offset.x == 0.f && offset.y == 0.f)
                continue;

            collision c = { other, myCol, this };

            if (myCol->IsTrigger || other->IsTrigger)
            {
                other->GetGameObject()->OnTriggerEnter(c);
            }
            else
            {
                totalCorrection += offset;
                other->GetGameObject()->OnCollisionEntered(c);
            }
        }
    }

    if (totalCorrection.x != 0.f || totalCorrection.y != 0.f)
    {
        GameObject->MoveTo(GameObject->getWorldPos() + totalCorrection);
        UpdateColliderPositions();

        if (totalCorrection.y != 0.f) AppliedVelocity.y = 0.f;
        if (totalCorrection.x != 0.f) AppliedVelocity.x = 0.f;
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