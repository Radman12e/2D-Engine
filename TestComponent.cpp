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
		GameObject->GetComponent<Rigidbody>()->Velocity = { GameObject->GetComponent<Rigidbody>()->Velocity.x,GameObject->GetComponent<Rigidbody>()->Velocity.y - 30 };
		//GameObject->MoveTo(sf::Vector2f(300, 200));
	}

}
void TestComponent::OnAPressed(InputArgs args)
{
	if (args.phase == InputPhase::Started)
	{
		GameObject->GetComponent<Rigidbody>()->Velocity = { GameObject->GetComponent<Rigidbody>()->Velocity.x - 30,GameObject->GetComponent<Rigidbody>()->Velocity.y };
		//GameObject->MoveTo(sf::Vector2f(300, 200));
	}

}
void TestComponent::OnSPressed(InputArgs args)
{
	if (args.phase == InputPhase::Started)
	{
		GameObject->GetComponent<Rigidbody>()->Velocity = { GameObject->GetComponent<Rigidbody>()->Velocity.x,GameObject->GetComponent<Rigidbody>()->Velocity.y + 30 };

		//GameObject->MoveTo(sf::Vector2f(300, 200));
	}

}
void TestComponent::OnDPressed(InputArgs args)
{
	if (args.phase == InputPhase::Started)
	{
		GameObject->GetComponent<Rigidbody>()->Velocity = { GameObject->GetComponent<Rigidbody>()->Velocity.x + 30 ,GameObject->GetComponent<Rigidbody>()->Velocity.y };

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

	std::function<void()> EventTest = [this]()
		{
			//if (!this) return;
			std::cout << "Triggered External";
		};

	std::function<void(InputArgs IA)> OnAPressedfn = [this](InputArgs IA)
		{
			this->OnAPressed(IA);
		};

	std::function<void(InputArgs IA)> OnSPressedfn = [this](InputArgs IA)
		{
			this->OnSPressed(IA);
		};
	std::function<void(InputArgs IA)> OnDPressedfn = [this](InputArgs IA)
		{
			this->OnDPressed(IA);
		};

	this->bindEvent(sf::Keyboard::Key::W, OnWPressedfn);
	this->bindEvent(sf::Keyboard::Key::A, OnAPressedfn);
	this->bindEvent(sf::Keyboard::Key::D, OnDPressedfn);
	this->bindEvent(sf::Keyboard::Key::S, OnSPressedfn);
	//this->bindEvent("TestEvent1", EventTest);

	//GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::W, OnWPressedfn);
	//GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::D, OnWPressedfn2);
	//GameEssentialsGlobals::InputEventH.UnBindEvent(sf::Keyboard::Key::W, Event);
}

TestComponent::TestComponent()
{
	
}