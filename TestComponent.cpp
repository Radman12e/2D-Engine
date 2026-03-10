#include "TestComponent.h"
#include <iostream>

void TestComponent::OnUpdate(float dt) 
{
	Component::OnUpdate(dt);
	if (this->Enabled == false) return;

	std::cout << "\n TICK: " << dt;

}

void TestComponent::OnPhysicsUpdate(float dt)
{
	Component::OnUpdate(dt);
	if (this->Enabled == false) return;

	std::cout << "\n PHYSICSTICK: " << dt;

}