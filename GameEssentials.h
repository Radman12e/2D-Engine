#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "EventHandler.h"

class Gameobject;

static class GameEssentialsGlobals
{
public:

	GameEssentialsGlobals();
	static Gameobject* WorldRoot;

	static std::vector<Gameobject*> GameObjectContainer;

	static void RemoveGameObject(Gameobject* GameObject);

	static Gameobject* InstansiateGameObject(Gameobject* gameObject);
	
	static float tickLength;

	static float physicsTimeStep;

	static float Timescale;

	sf::Clock clock;

	static sf::RenderWindow* Renderwindow;

	static void OnGameTick();
	static void SetRenderWindow(sf::RenderWindow* rwin) 
	{
		Renderwindow = rwin;
	}

	static void OnPhysicsTick();

	static void OnFreeTick();

	static void OutputSceneGraph(Gameobject* obj, int depth = 0);

	static void GameStart();


	static EventHandler EventH;
	static InputEventHandler InputEventH;

};


