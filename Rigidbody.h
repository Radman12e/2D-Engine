#pragma once
#include "Component.h"

struct ColliderStruct;
class Rigidbody : public Component
{
private:

	

    size_t id;

    std::vector<ColliderStruct> GetAllColliders(Gameobject* CurrentObject);

protected:

    sf::Vector2f Velocity = sf::Vector2f(0.f, 0.f);
    

public:
    Rigidbody();
    ~Rigidbody();
    std::vector<ColliderStruct> Colliders = {};

    void InitRB() 
    {
        Colliders = GetAllColliders(this->GameObject);
    }

	void OnAlive() override 
	{
		


	}

    bool CheckCollision() 
    {
    
    }

    bool FindCollider(size_t ID) {
       
        if (Colliders.empty()) {
            return false;
        }

       
        return std::find(Colliders.begin(), Colliders.end(), ID) != Colliders.end();
    }

    void OnPhysicsUpdate(float detlatime) override;
    void OnUpdate(float detlatime) override;

};

