#pragma once
#include "Component.h"

struct ColliderStruct;
class Rigidbody : public Component
{
private:

	

    size_t id;

    std::vector<ColliderStruct> GetAllColliders(Gameobject* CurrentObject);

protected:

    
    

public:
    sf::Vector2f Velocity = sf::Vector2f(0.f, 0.f);
    sf::Vector2f AppliedVelocity = sf::Vector2f(0.f, 0.f);
    Rigidbody();
    ~Rigidbody();
    std::vector<ColliderStruct> Colliders = {};

    void InitRB() 
    {
        Colliders = GetAllColliders(this->GameObject);
    }

    //void AddColliderToRb(ColliderStruct Collider) 
    //{
    //    Colliders.push_back(Collider);
    //}

	void OnAlive() override 
	{
		


	}

    bool CheckCollision() 
    {
    
    }

    std::unique_ptr<Component> CloneComponent() override;
    

    bool FindCollider(size_t ID);

    void OnPhysicsUpdate(float detlatime) override;
    void OnUpdate(float detlatime) override;

    void UpdateColliderPositions();

   
};

