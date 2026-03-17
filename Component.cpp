#include "Component.h"
#include <SFML/Graphics.hpp>
#include "Gameobject.h"

Component::Component(bool enabled)
{
	
	Enabled = enabled;
	this->OnAlive();
}

void Component::SetGameObject(Gameobject* ga) 
{
	GameObject = ga;
}

void Component::OnUpdate(float deltaTime)
{
	if (!this->Enabled)
	{
		return;
	}
}

void Component::OnPhysicsUpdate(float deltaTime)
{
	if (!this->Enabled)
	{
		return;
	}
}

void Component::OnDestroy()
{
	if (!this->Enabled)
	{
		return;
	}
}

void Component::OnStart()
{
	if (!this->Enabled)
	{
		return;
	}
}

void Component::OnAlive()

{
	if (!this->Enabled)
	{
		return;
	}
	//std::cout << "StartedComp!!--------------------------";
}