#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include "EventHandler.h"
#include "CollisionEventsinterface.h"
#include <iostream>
//#include "GameEssentials.h"

class Gameobject;




class Component
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

	std::vector< std::function<void()>> FunctionQueueNextFrame = {};

protected:
	Gameobject* GameObject = nullptr;
	


	size_t bindEvent(std::string Key, std::function<void(EventArgs)> fn);


	size_t bindEvent(sf::Keyboard::Key Key, std::function<void(InputArgs)> fn);

	size_t bindEvent(sf::Mouse::Button Key, std::function<void(InputArgs)> fn);

	

public:
	void UnbindAllEvents();
	void OnTrueUpdate(float deltaTime)
	{
		if (!FunctionQueueNextFrame.empty()) 
		{
			for (auto& fn : FunctionQueueNextFrame)
			{
				fn();
			}
			FunctionQueueNextFrame.clear();
		}
		OnUpdate(deltaTime);
		
	}

	void SetGameObject(Gameobject* ga);

	Component(bool enabled = true);
	virtual ~Component()
	{
		//std::cout << "DELETED1!";
		UnbindAllEvents();
	}

	void RunFunctionOnNectFrame(std::function<void()> fn)
	{
		FunctionQueueNextFrame.push_back(fn);
	}

	virtual void OnUpdate(float deltaTime);

	virtual void OnPhysicsUpdate(float deltaTime);
	
	virtual void OnDestroy();

	virtual void OnStart();

	virtual void OnAlive();

	virtual void OnCollisionEntered(collision& CollisionObject) {};
	virtual void OnCollisionStay(collision& CollisionObject)  {};
	virtual void OnCollisionExited(collision& CollisionObject) {};

	virtual void OnTriggerEntered(collision& CollisionObject) {};
	virtual void OnTriggerExited(collision& CollisionObject) {};


	virtual void OnLateUpdate(float dt) {};

	virtual std::unique_ptr<Component> CloneComponent() 
	{
		//return nullptr;
		return std::make_unique<Component>(*this);
	}

	

	bool Enabled = true;

	Gameobject* GetGameObject() 
	{
		
		return GameObject;
	}

	virtual void Disable() 
	{
		this->Enabled = false;
	}
	virtual void Enable() 
	{
		this->Enabled = true;
	}

};

