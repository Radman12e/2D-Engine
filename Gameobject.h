#pragma once
#include <SFML/Graphics.hpp>
#include "Gameobject.h"
#include "Component.h"
class Gameobject
{

private:
	sf::Transform transform;
	std::vector<std::unique_ptr<Component>> components;
	bool Enabled = true;

	void Destroy()
	{
		for (auto& component : components)
		{
			component->OnDestroy();
		}
		delete this;
	}

	void OnUpdate(float dt)
	{
		for (auto& component : components)
		{
			component->OnUpdate(dt);
		}
	}

	void OnStart()
	{
		for (auto& component : components)
		{
			component->OnStart();
		}
	}

	void OnAlive()
	{
		for (auto& component : components)
		{
			component->OnAlive();
		}
	}

public:
	Gameobject(bool Enabled = true)
	{
		this->transform = sf::Transform();
		this->Enabled = Enabled;
	}

	Gameobject(sf::Transform transform, bool Enabled = true)
	{
		this->transform = transform;
		this->Enabled = Enabled;
	}

	Gameobject(sf::Vector2f position, sf::Angle rotation = sf::Angle::Zero, bool Enabled = true)
	{
		this->transform = sf::Transform();
		transform.translate(position);
		transform.rotate(rotation);
		this->Enabled = Enabled;
	}

	sf::Transform& GetTransform()
	{
		return transform;
	}


	template<typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		components.push_back(
			std::make_unique<T>(std::forward<Args>(args)...)
		);

		return static_cast<T*>(components.back().get());
	}

};

