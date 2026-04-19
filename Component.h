#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include "EventHandler.h"
#include "CollisionEventsinterface.h"
//#include "GameEssentials.h"

class Gameobject;




class Component : public CollisionEventsinterface
{

	

private: 

	struct ComponentEvent
	{
		std::string key;
		size_t id;
	};

	struct ComponentInputKeyEvent
	{
		sf::Keyboard::Key key;
		size_t id;
	};

	struct ComponentInpuMouseEvent
	{
		sf::Mouse::Button key;
		size_t id;
	};

	std::vector<ComponentEvent> BasicEvents = {};
	std::vector<ComponentInputKeyEvent> ComponentInputKeyEvents = {};
	std::vector<ComponentInpuMouseEvent> ComponentInputMouseEvents = {};

protected:
	Gameobject* GameObject = nullptr;
	void UnbindAllEvents();
	
	
	size_t bindEvent(std::string Key, std::function<void()> fn);

	size_t bindEvent(sf::Keyboard::Key Key, std::function<void(InputArgs)> fn);
	
	size_t bindEvent(sf::Mouse::Button Key, std::function<void(InputArgs)> fn);
	


public:

	void SetGameObject(Gameobject* ga);

	Component(bool enabled = true);
	~Component() 
	{
		UnbindAllEvents();
	}

	virtual void OnUpdate(float deltaTime);

	virtual void OnPhysicsUpdate(float deltaTime);
	
	virtual void OnDestroy();

	virtual void OnStart();

	virtual void OnAlive();

	bool Enabled = true;

	Gameobject* GetGameObject() 
	{
		return GameObject;
	}

};

