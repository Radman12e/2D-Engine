#pragma once
#include <SFML/Graphics.hpp>
#include "Gameobject.h"
#include "Component.h"
#include "GameEssentials.h"

#include <iostream>
#include <memory>
#include <vector>

#include "CollisionEventsinterface.h"

class Gameobject //: public CollisionEventsinterface
{

private:
	sf::Transformable transform;
	std::vector<std::unique_ptr<Component>> components;

	std::vector<Gameobject*> Children = {};

	Gameobject* Parent = nullptr;

	bool Enabled = true;

	bool Started = false;

protected:

	sf::Vector2f LocalPosition = sf::Vector2f(0,0);

	sf::Angle LocalRotation = sf::degrees(0.0);

	sf::Vector2f WorldPosition = sf::Vector2f(0, 0);

	sf::Angle WorldRotation = sf::degrees(0.0);



public:

	sf::Vector2f getLocalPos() { return LocalPosition; }
	sf::Angle getLocalRot() { return LocalRotation; }
	sf::Vector2f getWorldPos() { return WorldPosition; }
	sf::Angle getWorldRot() { return WorldRotation; }

	std::string Name = "Empty";

	void OnCollisionEntered(collision& CollisionObject) 
	{

		std::cout << "Collider!!" << Name;

		for (Gameobject* c : Children)
		{

			//std::vector<std::unique_ptr<Component>> a =  c->GetComponents();

			//for (auto&& comp : a)
			//{

			//	std::function<void()> fn = [&comp, &CollisionObject]()
			//		{
						//comp->OnCollisionEntered(CollisionObject);
			//		};

				
			//	comp->RunFunctionOnNectFrame(fn);
				
			//}
		}
	}
	void OnCollisionStay(collision& CollisionObject) 
	{
		
	
	}
	void OnCollisionExited(collision& CollisionObject)
	{
		

	}

	void OnTriggerEnter(collision& CollisionObject)
	{


	}
	void OnOnTriggerExited(collision& CollisionObject)
	{


	}

	void Destroy();

	void OnUpdate(float dt);
	void OnPhysicsUpdate(float dt);

	void OnStart();

	void OnAlive();

	Gameobject();

	Gameobject(bool Enabled);

	Gameobject(sf::Transformable transform, bool Enabled);

	Gameobject(sf::Vector2f position, sf::Angle rotation, bool Enabled, Gameobject* parent);

	void Ready();

	void Enable();

	void Disable();

	sf::Transformable& GetTransform();

	const std::vector<Gameobject*>& GetChildren() const;

	Gameobject* AddChild(Gameobject* Child);


	template<typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		T* compTemp = GetComponent<T>();
		if (compTemp != nullptr)
		{
			return compTemp;
		}

		auto comp = std::make_unique<T>(std::forward<Args>(args)...);
		comp->SetGameObject(this);
		comp->OnAlive();

		T* ptr = comp.get();
		components.push_back(std::move(comp));
		

		return ptr;
	}

	template<typename T>
	T* GetComponent()
	{
		for (auto& comp : components)
		{
			if (auto existing = dynamic_cast<T*>(comp.get()))
			{
				return existing;
			}

		}
		return nullptr;
	}

	template<typename T>
	bool HasComponent()
	{
		
		return (GetComponent<T>() != nullptr);
	}

	template<typename T>
	void RemoveComponent()
	{
		for (auto it = components.begin(); it != components.end(); ++it)
		{
			if (dynamic_cast<T*>(it->get()))
			{
				components.erase(it);
				return;
			}
		}
	}

	std::vector<std::unique_ptr<Component>>& GetComponents()
	{
		return components;
	}

	Gameobject* GetParent();

	Gameobject* SetParent(Gameobject* Parent);

	void RemoveChildObject(Gameobject* Child);

	void UpdateWorldTransform();

	void MoveTo(sf::Vector2f worldPos);
	void RotateTo(sf::Angle worldRot);
	
	void SetlocalRotation(sf::Angle LocalRot);
	void SetlocalPosition(sf::Vector2f LocalPos);

};

