#include "TestComponent.h"
#include <iostream>

void TestComponent::OnUpdate(float dt) 
{
	Component::OnUpdate(dt);
	if (this->Enabled == false) return;

	std::cout << "\n dt: " << dt;

}