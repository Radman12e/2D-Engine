#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "EventHandler.h"
#include "Gameobject.h"
#include "Rigidbody.h"
#include "Collider.h"


//#include "PlayerController.h"

class Gameobject;

class Collider;

struct ColliderStruct
{
	Collider* collider;
	size_t id;

	
};

struct RigidbodyStruct
{
	Rigidbody* Rb;
	size_t id;
	
};

static class GameEssentialsGlobals
{
public:

	static std::unordered_map<Collider*, std::vector<Collider*>> BroadPhasePairs;

	static void RemoveRB(size_t id);

	static void RemoveCollider(size_t id);
	static void RemoveCollider(Collider* id);
	static void RunCollisionPass();

	static std::vector<ColliderStruct> Colliders;

	static std::vector<RigidbodyStruct> Rigidbodies;

	static size_t AddRigidbody(Rigidbody* rb);

	static size_t AddCollider(Collider* collider);

	GameEssentialsGlobals();
	static Gameobject* WorldRoot;

	static std::vector<Gameobject*> GameObjectContainer;

	static void RemoveGameObject(Gameobject* GameObject);

	static Gameobject* InstansiateGameObject(Gameobject* gameObject);

	
	static float tickLength;

	template<typename T>
	static T* FindFirstComponent();


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

	


	static EventHandler EventH;
	static InputEventHandler InputEventH;

	static size_t ColliderNextID;
	static size_t rbNextID;

	static void StartGame();

	static sf::Vector2f CollisionCheckRB(Rigidbody* rb);

	static sf::Vector2f CollisionCheckCollider(Collider* collider, std::vector<ColliderStruct> excludedColliders, Rigidbody* rb = nullptr);
	
	

};





template<typename T>
T* GameEssentialsGlobals::FindFirstComponent()
{
	T* ComponentT = nullptr;
	for (auto& Gameo : GameObjectContainer)
	{
		ComponentT = Gameo->template GetComponent<T>();
		if (ComponentT != nullptr)
		{
			return ComponentT;
		}
	}


	return nullptr;
}




