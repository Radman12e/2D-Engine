#pragma once
#include "Component.h"
#include "CollisionEventsinterface.h"
#include "Collider.h"

class Rigidbody : public Component
{
private:

	std::vector<Collider> Colliders = {};

public:
	Rigidbody()
	{
		Component();
	}

	void OnPhysicsUpdate(float detlatime) override 
	{
		


	}


};

