#pragma once
#include <vector>
#include <SFML/System.hpp>
class Gameobject;

class GameEssentialsGlobals
{
public:

	GameEssentialsGlobals();
	static Gameobject WorldRoot;

	static std::vector<Gameobject*> GameObjectContainer;

	static void RemoveGameObject(Gameobject* GameObject);

	static Gameobject* InstansiateGameObject(Gameobject* gameObject);
	
	static float TicksPerSecond;

	sf::Clock clock;

	void OnGameTick();

	void OnPhysicsTick();
};


