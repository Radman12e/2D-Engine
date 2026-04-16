#pragma once
#include "Component.h"


class Rigidbody : public Component
{
private:

	std::vector<size_t> Colliders = {};

    size_t id;

    std::vector<size_t> GetAllColliders(Gameobject* CurrentObject);

protected:

    sf::Vector2f Velocity = sf::Vector2f(0.f, 0.f);

public:
    Rigidbody();
    ~Rigidbody();
    

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

    void OnPhysicsUpdate(float detlatime) override;


};

