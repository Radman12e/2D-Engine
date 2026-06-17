#include "Gameobject.h"
#include "GameEssentials.h"


void Gameobject::Destroy()
{
	Disable();
	QueueForDestroy = true;
	if (this == GameEssentialsGlobals::WorldRoot)
		return;
	
	//std::cout << "DESTROY";
	

	for (auto& component : components)
	{
		component->Disable();
		component->OnDestroy();
		
		//std::cout << "DESTROY";
	}

	if (Parent != nullptr)
	{

		Parent->RemoveChildObject(this);
	}

	while (!Children.empty())
	{
		//std::cout << "DESTROY";
		Children.back()->Destroy();
		//Children.pop_back();
	}

	//std::cout << "\n\nGameObjectDelete!\n\n";
	//delete this;
	GameEssentialsGlobals::RemoveGameObject(this);
	
	//std::cout << "GameObjectDelete!";
	
	
	
}
void Gameobject::LateDestroy() 
{
	
	
}


void Gameobject::OnUpdate(float dt)
{
	
	if (!Enabled) return;
	for (auto& component : components)
	{
		if (!component)
		{
			std::cout << "NULL COMPONENT FOUND\n";
			continue;
		}
		component->OnTrueUpdate(dt);
		//component->OnUpdate(dt);
	}
}


void Gameobject::OnLateUpdate(float dt)
{
	
	if (QueueForDestroy) 
	{
		//std::cout << "\n\n GameObjectDelete! " << QueueForDestroy;
		this->LateDestroy();
	}

	if (!Enabled) return;
	for (auto& component : components)
	{
		if (!component)
		{
			std::cout << "NULL COMPONENT FOUND\n";
			continue;
		}
		component->OnLateUpdate(dt);
		//component->OnUpdate(dt);
	}
}

void Gameobject::OnPhysicsUpdate(float dt)
{
	if (!Enabled) return;
	for (auto& component : components)
	{
		if (!component)
		{
			std::cout << "NULL COMPONENT FOUND\n";
			continue;
		}
		component->OnPhysicsUpdate(dt);
	}
}

void Gameobject::OnStart()
{
	if (!Enabled) return;
	for (auto& component : components)
	{
		component->OnStart();
	}
}

void Gameobject::OnAlive()
{
	for (auto& component : components)
	{
		component->OnAlive();
	}
}


Gameobject::Gameobject()
{
	this->transform = sf::Transformable();
	this->Enabled = true;

	OnAlive(); 

	GameEssentialsGlobals::InstansiateGameObject(this);
	this->SetParent(GameEssentialsGlobals::WorldRoot);
}

Gameobject::Gameobject(bool Enabled)
{
	this->transform = sf::Transformable();
	this->Enabled = Enabled;

	if (Enabled)
	{
		OnAlive();
	}

	GameEssentialsGlobals::InstansiateGameObject(this);
	this->SetParent(GameEssentialsGlobals::WorldRoot);
}

Gameobject::Gameobject(sf::Transformable transform, bool Enabled)
{
	this->transform = transform;
	this->Enabled = Enabled;

	if (Enabled)
	{
		OnAlive();
	}
	GameEssentialsGlobals::InstansiateGameObject(this);
	this->SetParent(GameEssentialsGlobals::WorldRoot);
}


Gameobject::Gameobject(sf::Vector2f position, sf::Angle rotation, bool Enabled, Gameobject* parent)
{
	this->transform = sf::Transformable();
	transform.setPosition(position);
	transform.rotate(rotation);
	this->Enabled = Enabled;

	if (parent != nullptr)
	{
		this->SetParent(parent);
	}
	else
	{
		this->SetParent(GameEssentialsGlobals::WorldRoot);
	}

	if (Enabled)
	{
		OnAlive();
	}
	GameEssentialsGlobals::InstansiateGameObject(this);
}

void Gameobject::Ready()
{
	OnAlive();
	OnStart();
}

void Gameobject::Enable()
{
	if (Enabled == true) return;
	this->Enabled = true;
	OnAlive();
	if (Started == false)
	{
		Started = true;
		OnStart();
	}

	for (auto& component : components)
	{
		component->Enable();
	}
	
}

void Gameobject::Disable()
{
	if (Enabled == false) return;
	this->Enabled = false;
	for (auto& component : components)
	{
		component->Disable();
	}
	for (auto& c : GetDescendants()) 
	{
		c->Disable();
	}
}

sf::Transformable& Gameobject::GetTransform()
{
	return transform;
}

std::vector<Gameobject*> Gameobject::GetChildren()
{
	return Children;
}

Gameobject* Gameobject::AddChild(Gameobject* Child)
{
	Children.push_back(Child);


	if (Child->GetParent() != this) 
	{
		Child->SetParent(this);
	}

	return Child;
}



Gameobject* Gameobject::GetParent()
{
	return Parent;
}

void Gameobject::RemoveChildObject(Gameobject* Child)
{
	
	Children.erase(std::remove(Children.begin(), Children.end(), Child), Children.end());

}


Gameobject* Gameobject::SetParent(Gameobject* parent)
{
	if (this->Parent != nullptr)
	{
		this->Parent->RemoveChildObject(this);
	}

	this->Parent = parent;

	if (parent != nullptr)
	{
		parent->AddChild(this);
	}

	return parent;
}

void Gameobject::UpdateWorldTransform()
{
	this->WorldPosition = LocalPosition;
	this->WorldRotation = LocalRotation;

	if (Parent != nullptr)
	{
		this->WorldPosition += Parent->GetTransform().getPosition();
		this->WorldRotation += Parent->GetTransform().getRotation();
	}

	transform.setPosition(this->WorldPosition);
	transform.setRotation(this->WorldRotation);

	for (auto child : Children)
	{
		child->UpdateWorldTransform();
	}


}

void Gameobject::MoveTo(sf::Vector2f worldPos)
{
	if (Parent != nullptr)
	{
		LocalPosition = worldPos - Parent->GetTransform().getPosition();
	}
	else
	{
		LocalPosition = worldPos;
	}

	UpdateWorldTransform();
}

void Gameobject::RotateTo(sf::Angle worldRot)
{
	if (Parent != nullptr)
	{
		LocalRotation = worldRot - Parent->GetTransform().getRotation();
	}
	else
	{
		LocalRotation = worldRot;
	}

	UpdateWorldTransform();
}

void Gameobject::SetlocalRotation(sf::Angle LocalRot) 
{
	this->LocalRotation = LocalRot;
	UpdateWorldTransform();
}

void Gameobject::SetlocalPosition(sf::Vector2f LocalPos)
{
	this->LocalPosition = LocalPos;
	UpdateWorldTransform();
}

void Gameobject::OnCollisionEntered(collision& CollisionObject)
{
	if (!Enabled) return;
	std::vector<Gameobject*> a = GetDescendants();
	a.push_back(this);
	for (Gameobject* c : a)
	{

		auto& ab = c->GetComponents();

		for (auto&& comp : ab)
		{


			comp->OnCollisionEntered(CollisionObject);





		}
	}
}

void Gameobject::OnCollisionExited(collision& CollisionObject)
{
	if (!Enabled) return;
	std::vector<Gameobject*> a = GetDescendants();
	a.push_back(this);
	for (Gameobject* c : a)
	{

		auto& ab = c->GetComponents();

		for (auto&& comp : ab)
		{


			comp->OnCollisionExited(CollisionObject);





		}
	}
}

void Gameobject::OnTriggerEnter(collision& CollisionObject)
{
	if (!Enabled) return;
	std::vector<Gameobject*> a = GetDescendants();
	a.push_back(this);
	for (Gameobject* c : a)
	{

		auto& ab = c->GetComponents();

		for (auto&& comp : ab)
		{


			comp->OnTriggerEntered(CollisionObject);





		}
	}
}
void Gameobject::OnTriggerExited(collision& CollisionObject)
{
	if (!Enabled) return;
	std::vector<Gameobject*> a = GetDescendants();
	a.push_back(this);
	for (Gameobject* c : a)
	{

		auto& ab = c->GetComponents();

		for (auto&& comp : ab)
		{


			comp->OnTriggerExited(CollisionObject);





		}
	}
}