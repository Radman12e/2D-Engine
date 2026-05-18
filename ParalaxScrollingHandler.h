#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <cmath>

#include "Component.h"
#include "Gameobject.h"
#include "CameraComponent.h"
#include "SpriteRendererComponent.h"

class ParalaxScrollingHandler : public Component
{
public:

	bool Setup = false;

	struct ParalaxObject
	{
		Gameobject* Obj = nullptr;
		sf::Vector2f Offset = {};
	};

	struct ParalaxLayer
	{
		float DisplacementMulti = 1;

		std::vector<ParalaxObject> Objects;

		Gameobject* TemplateObject = nullptr;


		int NumOfRepeats = 5;

		int Width = 0;
		int Height = 0;
	};

	std::unordered_map<std::string, ParalaxLayer> Layers;

	CameraComponent* FocusPoint = nullptr;

public:


	virtual std::unique_ptr<Component> CloneComponent() override
	{
		auto psh = std::make_unique<ParalaxScrollingHandler>();

		psh->Enabled = Enabled;
		psh->FocusPoint = FocusPoint;

		for (auto& [name, layer] : Layers)
		{
			ParalaxLayer newLayer;

			newLayer.DisplacementMulti = layer.DisplacementMulti;
			newLayer.TemplateObject = layer.TemplateObject;
			newLayer.NumOfRepeats = layer.NumOfRepeats;
			newLayer.Width = layer.Width;
			newLayer.Height = layer.Height;

			newLayer.Objects.clear();

			psh->Layers[name] = newLayer;
		}

		psh->Setup = false;

		return psh;
	}

	void AddLayer(std::string Name, Gameobject* LayerObj, float Displacement = 1.f, int Repeats = 5)
	{
		if (LayerObj == nullptr) return;


		if (Repeats < 3) Repeats = 3;

		if (Repeats % 2 == 0) Repeats++;

		SpriteRendererComponent* Renderer = LayerObj->GetComponent<SpriteRendererComponent>();

		if (Renderer == nullptr)
			return;

		auto Bounds =
			Renderer->Sprite.getGlobalBounds();

		float Width = Bounds.size.x;
		float Height = Bounds.size.y;

		if (Width <= 0 || Height <= 0)
			return;

		LayerObj->Disable();

		ParalaxLayer Layer;

		Layer.DisplacementMulti = Displacement;
		Layer.TemplateObject = LayerObj;
		Layer.NumOfRepeats = Repeats;
		Layer.Width = Width;
		Layer.Height = Height;

		if (Layers.find(Name) != Layers.end() && Setup == true)
		{
			for (auto& Obj : Layers[Name].Objects)
			{
				if (Obj.Obj != nullptr)
				{
					Obj.Obj->Destroy();
				}
			}

		}
		

		Layers[Name] = Layer;
		//this->GenerateLayer(Layers[Name]);


		this->GenerateLayer(Layers[Name]);
	

		
		
		
	}

	void GenerateLayer(ParalaxLayer& Layer)
	{
		if (Layer.TemplateObject == nullptr) return;

		Layer.Objects.clear();

		int Half = Layer.NumOfRepeats / 2;

		for (int y = -Half; y <= Half; y++)
		{
			for (int x = -Half; x <= Half; x++)
			{
				
				Gameobject* Clone = Layer.TemplateObject->Clone();

				if (Clone == nullptr)
					continue;

				Clone->Enable();

				

				ParalaxObject Obj;

				Obj.Obj = Clone;

				Obj.Offset =
				{
					static_cast<float>(x) * Layer.Width,
					static_cast<float>(y) * Layer.Height
				};
				Clone->SetParent(GameObject);

				Layer.Objects.push_back(Obj);
				
			}
		}

		
		UpdateParalax();
	}

	void UpdateParalax()
	{
		if (FocusPoint == nullptr)
			return;

		sf::Vector2f CamPos =
			FocusPoint->GetGameObject()->getWorldPos();

	

		for (auto& [Name, Layer] : Layers)
		{
	
			if (Layer.Objects.empty())
				continue;

			float Width = Layer.Width;
			float Height = Layer.Height;

			float TotalWidth =
				Width * static_cast<float>(Layer.NumOfRepeats);

			float TotalHeight =
				Height * static_cast<float>(Layer.NumOfRepeats);

			float HalfTotalWidth =
				TotalWidth * 0.5f;

			float HalfTotalHeight =
				TotalHeight * 0.5f;


			sf::Vector2f LayerCenter =
			{
				CamPos.x * Layer.DisplacementMulti,
				CamPos.y * Layer.DisplacementMulti
			};

			for (auto& Obj : Layer.Objects)
			{
				if (Obj.Obj == nullptr)
					continue;

				sf::Vector2f Pos =
				{
					LayerCenter.x + Obj.Offset.x,
					LayerCenter.y + Obj.Offset.y
				};


				while (Pos.x < CamPos.x - HalfTotalWidth)
				{
					Pos.x += TotalWidth;
				}

				while (Pos.x > CamPos.x + HalfTotalWidth)
				{
					Pos.x -= TotalWidth;
				}

	
				while (Pos.y < CamPos.y - HalfTotalHeight)
				{
					Pos.y += TotalHeight;
				}

				while (Pos.y > CamPos.y + HalfTotalHeight)
				{
					Pos.y -= TotalHeight;
				}

				Obj.Obj->MoveTo(Pos);
			}
		}
	}

	void OnUpdate(float dt) override
	{

		if (Enabled == false) return;
		if (Setup == false) 
		{
			while (GameObject->GetChildren().size() > 0)
			{
				GameObject->GetChildren().back()->Destroy();
			}
			
			for (auto& [Name, a] : Layers) 
			{
				AddLayer(Name, Layers[Name].TemplateObject, Layers[Name].DisplacementMulti, Layers[Name].NumOfRepeats);
				

			}
			Setup = true;


		}
		UpdateParalax();
	}

	ParalaxScrollingHandler()
	{
		Setup = true;
	}
	~ParalaxScrollingHandler()
	{

		Layers.clear();
	}
};