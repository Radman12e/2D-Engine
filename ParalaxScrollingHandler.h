#pragma once
#include "Component.h"
#include "Gameobject.h"
#include "CameraComponent.h"
#include "SpriteRendererComponent.h"
class ParalaxScrollingHandler :
    public Component
{


public:


	struct ParalaxLayer
	{
		float DisplacementMulti = 1; // Controls how fast the layer goes past, lower number = slower scroll, higher = higher scroll
		std::vector<Gameobject*> Objects = {};
		Gameobject* CentralObject = nullptr;
		Gameobject* ObjectToClone = nullptr;
		int NumOfRepeats = 3;
		//sf::Vector2f OrignPos;
	};

	std::unordered_map<std::string, ParalaxLayer> Layers;
	
	CameraComponent* FocusPoint;

	void AddLayer(std::string LayerName, Gameobject* Layer, float DisplacementMulti = 1, int NumOfRepeats = 3)
	{
		if (Layer == nullptr)
			return;

		Layer->Disable();
		Layer->SetParent(GameObject);

		ParalaxLayer NewLayer =
		{
			DisplacementMulti,
			{},
			nullptr,
			Layer,
			NumOfRepeats
		};

	
		if (Layers.find(LayerName) != Layers.end())
		{
			if (Layers[LayerName].ObjectToClone != nullptr)
			{
				Layers[LayerName].ObjectToClone->Destroy();
			}

			for (auto& obj : Layers[LayerName].Objects)
			{
				if (obj != nullptr)
					obj->Destroy();
			}
		}

		Layers[LayerName] = NewLayer;

		GenerateLayer(Layers[LayerName]);
	}

	void GenerateLayer(ParalaxLayer& Layer)
	{
		if (Layer.ObjectToClone == nullptr)
			return;

		Layer.Objects.clear();

		const int Half = Layer.NumOfRepeats / 2;

		float Width = Layer.ObjectToClone->GetComponent<SpriteRendererComponent>()->Sprite.getTextureRect().size.x;
			

		float Height = Layer.ObjectToClone->GetComponent<SpriteRendererComponent>()->Sprite.getTextureRect().size.y;

		sf::Vector2f CenterPos = FocusPoint->GetGameObject()->getWorldPos();


		for (int y = -Half; y <= Half; y++)
		{
			for (int x = -Half; x <= Half; x++)
			{
				Gameobject* Clone = Layer.ObjectToClone->Clone();

				Clone->Enable();

				sf::Vector2f Pos = CenterPos;

				Pos.x += Width * x;
				Pos.y += Height * y;

				Clone->MoveTo(Pos);

				Layer.Objects.push_back(Clone);

				if (x == 0 && y == 0)
				{
					Layer.CentralObject = Clone;
				}

			}
		}
	}


	void UpdateParalax()
	{
		if (FocusPoint == nullptr)
			return;

		sf::Vector2f CamPos = FocusPoint->GetGameObject()->getWorldPos();

		for (auto& [Name, Layer] : Layers)
		{
			
			Gameobject* Obj = Layer.CentralObject;
			for (auto& Others : Layer.Objects)
			{
				if (Others == Obj || Others->GetParent() == Obj) continue;
				Others->SetParent(Obj);
			}
			if (Obj == nullptr)
				continue;

			sf::Vector2f Pos = Obj->getWorldPos();

			Pos.x = CamPos.x * Layer.DisplacementMulti;
			Pos.y = CamPos.y * Layer.DisplacementMulti;

			Obj->SetlocalPosition(Pos);
		}
	}

	void OnUpdate(float dt) override 
	{
		UpdateParalax();
	}
	


	~ParalaxScrollingHandler()
	{
	}


};

