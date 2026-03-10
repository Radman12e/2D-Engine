#include "Gameobject.h"
#include "GameEssentials.h"


void Gameobject::Destroy()
{
	if (this == GameEssentialsGlobals::WorldRoot)
		return;
	for (auto& component : components)
	{
		component->OnDestroy();
	}

	while (!Children.empty())
	{
		Children.back()->Destroy();
	}

	if (Parent != nullptr)
	{
		Parent->RemoveChildObject(this);
	}
	GameEssentialsGlobals::RemoveGameObject(this);

	delete this;
}

void Gameobject::OnUpdate(float dt)
{
	for (auto& component : components)
	{
		component->OnUpdate(dt);
	}
}

void Gameobject::OnPhysicsUpdate(float dt)
{
	for (auto& component : components)
	{
		component->OnPhysicsUpdate(dt);
	}
}

void Gameobject::OnStart()
{
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

		if (Enabled)
		{
			OnAlive();
		}

		GameEssentialsGlobals::InstansiateGameObject(this);
		this->SetParent(GameEssentialsGlobals::WorldRoot);

	}

Gameobject::Gameobject(bool Enabled = true)
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

Gameobject::Gameobject(sf::Transformable transform, bool Enabled = true)
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

Gameobject::Gameobject(sf::Vector2f position = sf::Vector2f(0,0), sf::Angle rotation = sf::Angle::Zero, bool Enabled = true, Gameobject* parent = nullptr)
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
	this->Enabled = true;
	OnAlive();
	if (Started == false)
	{
		Started = true;
		OnStart();
	}
}

void Gameobject::Disable()
{
	this->Enabled = false;
}

sf::Transformable& Gameobject::GetTransform()
{
	return transform;
}

const std::vector<Gameobject*>& Gameobject::GetChildren() const
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

