#include "Component.h"
#include <SFML/Graphics.hpp>
#include "Gameobject.h"
//#include "EventHandler.h"
#include "GameEssentials.h"

Component::Component(bool enabled) 
{
	
	Enabled = enabled;
	
}

void Component::SetGameObject(Gameobject* ga) 
{
	GameObject = ga;
}

void Component::OnUpdate(float deltaTime)
{
	if (!this->Enabled)
	{
		return;
	}
}

void Component::OnPhysicsUpdate(float deltaTime)
{
	if (!this->Enabled)
	{
		return;
	}
}

void Component::OnDestroy()
{
	
}

void Component::OnStart()
{
	if (!this->Enabled)
	{
		return;
	}
}

void Component::OnAlive()

{
	if (!this->Enabled)
	{
		return;
	}
	//std::cout << "StartedComp!!--------------------------";
}

void Component::UnbindAllEvents() 
{
	for (auto& id : BasicEvents)
	{
		GameEssentialsGlobals::EventH.UnBindEvent(id.key, id.id);
	}
	for (auto& id : ComponentInputKeyEvents)
	{
		GameEssentialsGlobals::InputEventH.UnBindEvent(id.key, id.id);
	}
	for (auto& id : ComponentInputMouseEvents)
	{
		GameEssentialsGlobals::InputEventH.UnBindEvent(id.key, id.id);
	}
}

size_t Component::bindEvent(std::string Key, std::function<void(EventArgs)> fn)
{
	//InputArgs IA = {};
	size_t ID = GameEssentialsGlobals::EventH.BindEvent(Key, fn);

	BasicEvents.push_back({ Key,ID });
	return ID;
}

size_t Component::bindEvent(sf::Keyboard::Key Key, std::function<void(InputArgs)> fn)
{
	size_t ID = GameEssentialsGlobals::InputEventH.BindEvent(Key, fn);

	ComponentInputKeyEvents.push_back({ Key,ID });
	return ID;
}

size_t Component::bindEvent(sf::Mouse::Button Key, std::function<void(InputArgs)> fn)
{
	size_t ID = GameEssentialsGlobals::InputEventH.BindEvent(Key, fn);

	ComponentInputMouseEvents.push_back({ Key,ID });
	return ID;

}