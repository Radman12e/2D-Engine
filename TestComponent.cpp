#include "TestComponent.h"

void TestComponent::OnUpdate(float dt) 
{
	Component::OnUpdate(dt);
	if (this->Enabled == false) return;

	//std::cout << "\n TICK: " << dt;

}

void TestComponent::OnPhysicsUpdate(float dt)
{
	Component::OnPhysicsUpdate(dt);
	if (this->Enabled == false) return;

	//std::cout << "\n PHYSICSTICK: " << dt;

}


void OnWPressed2(InputArgs args) 
{

}

void TestComponent::OnWPressed(InputArgs args)
{
	if (args.phase == InputPhase::Started) 
	{
		GameObject->MoveTo(GameObject->getWorldPos() + sf::Vector2f(0, -10));
		//GameObject->MoveTo(sf::Vector2f(300, 200));
	}

}
void TestComponent::OnAPressed(InputArgs args)
{
	if (args.phase == InputPhase::Started)
	{
		GameObject->MoveTo(GameObject->getWorldPos() + sf::Vector2f(0, -10));
		//GameObject->MoveTo(sf::Vector2f(300, 200));
	}

}
void TestComponent::OnSPressed(InputArgs args)
{
	if (args.phase == InputPhase::Started)
	{
		GameObject->MoveTo(GameObject->getWorldPos() - sf::Vector2f(10, 0));
		//GameObject->MoveTo(sf::Vector2f(300, 200));
	}

}
void TestComponent::OnDPressed(InputArgs args)
{
	if (args.phase == InputPhase::Started)
	{
		GameObject->MoveTo(GameObject->getWorldPos() + sf::Vector2f(0, 10));
		//GameObject->MoveTo(sf::Vector2f(300, 200));
	}

}

void TestComponent::OnAlive()
{
	//std::cout << "StartedComp!!--------------------------";
	Component::OnAlive();
	std::cout << "StartedComp!!--------------------------";

	

	std::function<void(InputArgs IA)> OnWPressedfn = [this](InputArgs IA)
		{
			//if (!this) return;
			this->OnWPressed(IA);
		};

	GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::W, OnWPressedfn);
}

TestComponent::TestComponent()
{
	this->OnAlive();
}