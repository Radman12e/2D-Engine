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

	//bool StartEnabled = true;

	bool Started = false;

protected:

	sf::Vector2f LocalPosition = sf::Vector2f(0,0);

	sf::Angle LocalRotation = sf::degrees(0.0);

	sf::Vector2f WorldPosition = sf::Vector2f(0, 0);

	sf::Angle WorldRotation = sf::degrees(0.0);



public:

	bool QueueForDestroy = false;

	sf::Vector2f getLocalPos() { return LocalPosition; }
	sf::Angle getLocalRot() { return LocalRotation; }
	sf::Vector2f getWorldPos() { return WorldPosition; }
	sf::Angle getWorldRot() { return WorldRotation; }

	std::string Name = "Empty";

	void OnCollisionEntered(collision& CollisionObject);
	void OnCollisionStay(collision& CollisionObject);
	void OnCollisionExited(collision& CollisionObject);
	void OnTriggerEnter(collision& CollisionObject);
	void OnTriggerExited(collision& CollisionObject);

	void LateDestroy();
	

	void Destroy();

	void OnUpdate(float dt);
	void OnPhysicsUpdate(float dt);

	void OnStart();

	void OnAlive();

	void OnLateUpdate(float dt);
	
	Gameobject();

	~Gameobject() 
	{
		//std::cout << "DESTROYOBJECT!!!";
	}

	Gameobject(bool Enabled);

	Gameobject(sf::Transformable transform, bool Enabled);

	Gameobject(sf::Vector2f position, sf::Angle rotation, bool Enabled, Gameobject* parent);

	void Ready();

	void Enable();

	void Disable();

	sf::Transformable& GetTransform();

	std::vector<Gameobject*> GetChildren() ;

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

	std::vector<Gameobject*> GetDescendants()
	{
		std::vector<Gameobject*> result;

		for (Gameobject* child : Children)
		{
			result.push_back(child);

			auto subDescendants = child->GetDescendants();
			result.insert(result.end(), subDescendants.begin(), subDescendants.end());
		}

		return result;
	}

	Gameobject* Clone()
	{
		Gameobject* clone = new Gameobject();

		clone->Name = Name;
		clone->Enabled = Enabled;

		clone->LocalPosition = LocalPosition;
		clone->LocalRotation = LocalRotation;
		clone->WorldPosition = WorldPosition;
		clone->WorldRotation = WorldRotation;

	
		for (const auto& comp : components)
		{
			auto newComp = comp->CloneComponent();
			if (newComp == nullptr) continue;
			newComp->SetGameObject(clone);

			clone->components.push_back(std::move(newComp));
		}
		clone->SetParent(this->Parent);
		
		for (Gameobject* child : GetChildren())
		{
			Gameobject* childClone = child->Clone();
			childClone->SetParent(clone);
			childClone->Enable();
		}

		

		return clone;
	}

};

