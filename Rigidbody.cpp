#include "Rigidbody.h"
#include "CollisionEventsinterface.h"
#include "Collider.h" 
#include "Gameobject.h"

std::vector<size_t> Rigidbody::GetAllColliders(Gameobject* CurrentObject)
{
    std::vector<size_t> colliders;

    Collider* col = CurrentObject->GetComponent<Collider>();
    if (col != nullptr)
    {
        colliders.push_back(col->GetID());
    }

    for (Gameobject* child : CurrentObject->GetChildren())
    {
        std::vector<size_t> childColliders = GetAllColliders(child);

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

void Rigidbody::OnPhysicsUpdate(float detlatime)
{
    GameObject->MoveTo(GameObject->getWorldPos() + (Velocity * detlatime));


}