#include <map>
#include <string>
#include <functional>
#include <vector>
#include <SFML/Window.hpp>


#pragma once
class EventHandler
{
private:
	
	struct EventBinding
	{
		size_t ID;
		std::function<void()> Eventfn;
	};

	size_t nextId = 0;

	std::unordered_map<std::string,std::vector<EventBinding>> Events;
	std::unordered_map<std::string, bool> EventStatus;
	
public:

	size_t BindEvent(std::string str, std::function<void()> func)
	{
		size_t id = nextId++;
		Events[str].push_back({ id, std::move(func) });
		return id;
	}

	void UnBindEvent(std::string str, size_t id)
	{
		auto& vec = Events[str];

		vec.erase(
			std::remove_if(vec.begin(), vec.end(),
				[id](const EventBinding& b) { return b.ID == id; }),
			vec.end()
		);
	}

	void FireEvent(std::string str)
	{
		auto it = Events.find(str);
		if (it == Events.end()) return;

		for (auto& b : Events[str])
		{
			if (b.Eventfn) b.Eventfn();
		}
	}


};

enum InputPhase
{
	Started, Ended
};

struct InputArgs
{
	InputPhase phase;
	InputArgs(InputPhase p = Started)
	{
		phase = p;
	}
};



class InputEventHandler
{

	struct EventBinding
	{
		size_t ID;
		std::function<void(InputArgs)> Eventfn;
	};

private:

	std::unordered_map<sf::Keyboard::Key, std::vector<EventBinding>> KeyboardEvents;
	std::unordered_map<sf::Mouse::Button, std::vector<EventBinding>> MouseEvents;

	

	std::unordered_map<sf::Keyboard::Key, bool> KeyStatus;
	std::unordered_map<sf::Mouse::Button, bool> MouseButtonStatus;
	size_t nextId = 0;

public:

	size_t BindEvent(sf::Mouse::Button str, std::function<void(InputArgs)> func)
	{
		//fnStorage.push_back(func);
		size_t id = nextId++;
		MouseEvents[str].push_back({ id, std::move(func) });
		MouseButtonStatus[str] = false;
		return id;
	}
	size_t BindEvent(sf::Keyboard::Key str, std::function<void(InputArgs)> func)
	{
		//fnStorage.push_back(func);
		size_t id = nextId++;
		KeyboardEvents[str].push_back({ id, std::move(func) });
		KeyStatus[str] = false;
		return id;
	}

	void UnBindEvent(sf::Keyboard::Key key, size_t funcID)
	{
		auto& vec = KeyboardEvents[key];

		vec.erase(
			std::remove_if(vec.begin(), vec.end(),
				[funcID](const EventBinding& b) { return b.ID == funcID; }),
			vec.end()
		);
	}
	void UnBindEvent(sf::Mouse::Button key, size_t funcID)
	{
		auto& vec = MouseEvents[key];

		vec.erase(
			std::remove_if(vec.begin(), vec.end(),
				[funcID](const EventBinding& b) { return b.ID == funcID; }),
			vec.end()
		);
	}

	void FireEvent(sf::Keyboard::Key key, InputArgs arg)
	{
		auto it = KeyboardEvents.find(key);
		if (it == KeyboardEvents.end()) return;

		for (auto& b : KeyboardEvents[key])
		{
			if (b.Eventfn) b.Eventfn(arg);
		}
	}

	void FireEvent(sf::Mouse::Button key, InputArgs arg)
	{
		auto it = MouseEvents.find(key);
		if (it == MouseEvents.end()) return;

		for (auto& b : MouseEvents[key])
		{
			if (b.Eventfn) b.Eventfn(arg);
		}
	}


	void OnGameTick() 
	{
		
		for (auto const& [key, val] : KeyStatus)
		{
			if (sf::Keyboard::isKeyPressed(key)) 
			{
				if (val == false) 
				{
					KeyStatus[key] = true;

					FireEvent(key, InputArgs(InputPhase::Started));
				}
				
			}
			else 
			{
				if (val == true)
				{
					KeyStatus[key] = false;

					FireEvent(key, InputArgs(InputPhase::Ended));
				}
			}

		}

		for (auto const& [key, val] : MouseButtonStatus)
		{
			if (sf::Mouse::isButtonPressed(key))
			{
				if (val == false)
				{
					MouseButtonStatus[key] = true;

					FireEvent(key, InputArgs(InputPhase::Started));
				}

			}
			else
			{
				if (val == true)
				{
					MouseButtonStatus[key] = false;

					FireEvent(key, InputArgs(InputPhase::Ended));
				}
			}

		}
	}

};