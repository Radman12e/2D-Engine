#include "Gameobject.h"
#include "GameEssentials.h"

void Gameobject::Destroy()
{
	for (auto& component : components)
	{
		component->OnDestroy();
	}

	for (auto& child : Children)
	{
		child->Destroy();
	}

	if (Parent != nullptr)
	{

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
	}

Gameobject::Gameobject(sf::Vector2f position, sf::Angle rotation = sf::Angle::Zero, bool Enabled = true)
{
	this->transform = sf::Transformable();
	transform.setPosition(position);
	transform.rotate(rotation);
	this->Enabled = Enabled;

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

std::vector<Gameobject*> Gameobject::GetChildren()
{
	return Children;
}

Gameobject* Gameobject::AddChild(Gameobject* Child)
{
	Children.push_back(Child);

	return Child;
}

template<typename T, typename... Args>
T* Gameobject::AddComponent(Args&&... args)
{
	components.push_back(
		std::make_unique<T>(std::forward<Args>(args)...)
	);

	return static_cast<T*>(components.back().get());
}

Gameobject* Gameobject::GetParent()
{
	return Parent;
}

Gameobject* Gameobject::SetParent(Gameobject* Parent)
{
	this->Parent = Parent;
	return Parent;
}