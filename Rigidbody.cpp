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
    GameEssentialsGlobals::RemoveRB(this->id);

}

void Rigidbody::OnPhysicsUpdate(float dt)
{
    AppliedVelocity = Velocity;

    sf::Vector2f movement = AppliedVelocity * dt;

    sf::Vector2f correction = GameEssentialsGlobals::CollisionCheckRB(this);

    std::cout << "Correction: " << correction.x << ", " << correction.y;

    sf::Vector2f currentPos = GameObject->getWorldPos();

    // Treat correction as positional displacement constraint
    sf::Vector2f targetPos = currentPos + movement + correction;

    GameObject->MoveTo(targetPos);
}


void Rigidbody::OnUpdate(float detlatime)
{
    //GameObject->MoveTo(GameObject->getWorldPos() + (AppliedVelocity * detlatime));
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
