#pragma once
#include <SFML/Graphics.hpp>
class Gameobject;




class Component
{

private:
	Gameobject* GameObject = nullptr;

public:

	void SetGameObject(Gameobject* ga);

	Component(bool enabled = true);

	virtual void OnUpdate(float deltaTime);
	
	virtual void OnDestroy();

	virtual void OnStart();

	virtual void OnAlive();

	bool Enabled = true;
};

