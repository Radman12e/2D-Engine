#pragma once
#include <SFML/Graphics.hpp>
#include "Gameobject.h"
#include "Component.h"
#include "GameEssentials.h"

class Gameobject
{

private:
	sf::Transformable transform;
	std::vector<std::unique_ptr<Component>> components;

	std::vector<Gameobject*> Children = {};

	Gameobject* Parent = nullptr;

	bool Enabled = true;

	bool Started = false;

	
	




public:
	void Destroy();

	void OnUpdate(float dt);

	void OnStart();

	void OnAlive();

	Gameobject();

	Gameobject(bool Enabled);

	Gameobject(sf::Transformable transform, bool Enabled);

	Gameobject(sf::Vector2f position, sf::Angle rotation, bool Enabled);

	void Ready();

	void Enable();

	void Disable();

	sf::Transformable& GetTransform();

	std::vector<Gameobject*> GetChildren();

	Gameobject* AddChild(Gameobject* Child);

	template<typename T, typename... Args>
	T* AddComponent(Args&&... args);

	Gameobject* GetParent();

	Gameobject* SetParent(Gameobject* Parent);

};

