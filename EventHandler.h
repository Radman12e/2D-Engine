#include <map>
#include <string>
#include <functional>
#include <vector>
#include <SFML/Window.hpp>


#pragma once
class EventHandler
{
private:
	
	std::unordered_map<std::string, std::vector<std::function<void()>*>> Events;
	std::unordered_map<std::string, bool> EventStatus;
	
public:

	void BindEvent(std::string str, std::function<void()>* func)
	{
		Events[str].push_back(func);
	}

	void UnBindEvent(std::string str, void(*func))
	{
		Events[str].erase(std::remove(Events[str].begin(), Events[str].end(), func), Events[str].end());		
	}

	void FireEvent(std::string str)
	{
		for (auto& element : Events[str])
		{
			if (element != nullptr)
			(*element)();

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
private:

	std::unordered_map<sf::Keyboard::Key, std::vector<std::function<void(InputArgs)>*>> KeyboardEvents;
	std::unordered_map<sf::Mouse::Button, std::vector<std::function<void(InputArgs)>*>> MouseEvents;

	std::vector <std::function<void(InputArgs)>> fnStorage;

	std::unordered_map<sf::Keyboard::Key, bool> KeyStatus;
	std::unordered_map<sf::Mouse::Button, bool> MouseButtonStatus;

public:

	void BindEvent(sf::Mouse::Button str, std::function<void(InputArgs)> func)
	{
		fnStorage.push_back(func);
		
		MouseEvents[str].push_back(&fnStorage[ fnStorage.size()-1]);
		MouseButtonStatus[str] = false;
		
	}
	void BindEvent(sf::Keyboard::Key str, std::function<void(InputArgs)> func)
	{
		fnStorage.push_back(func);
		KeyboardEvents[str].push_back(&fnStorage[fnStorage.size() - 1]);
		KeyStatus[str] = false;
	}

	void UnBindEvent(sf::Keyboard::Key str, std::function<void(InputArgs)>* func)
	{
		KeyboardEvents[str].erase(std::remove(KeyboardEvents[str].begin(), KeyboardEvents[str].end(), func), KeyboardEvents[str].end());
	}
	void UnBindEvent(sf::Mouse::Button str, std::function<void(InputArgs)>* func)
	{
		MouseEvents[str].erase(std::remove(MouseEvents[str].begin(), MouseEvents[str].end(), func), MouseEvents[str].end());
	}

	void FireEvent(sf::Keyboard::Key str, InputArgs arg)
	{
		for (auto& element : KeyboardEvents[str])
		{
			if (element != nullptr)
				(*element)(arg);

		}
	}
	void FireEvent(sf::Mouse::Button str, InputArgs arg)
	{
		for (auto& element : MouseEvents[str])
		{
			if (element != nullptr)
			{
				try
				{
					(*element)(arg);
				}
				catch (const std::exception&)
				{
					
				}
				
			}

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