#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "GameEssentials.h"
#include "Gameobject.h"
#include <iostream>
class SpriteRendererComponent : public Component
{
private:
	//sf::IntRect rectSourceSprite(300, 0, 300, 400);
	sf::Texture* Texture;
	sf::IntRect Rect = sf::IntRect({ 0,0 }, { 0, 0 });



public:


	sf::Sprite Sprite;//("");
	void OnLateUpdate(float dt) override;
	SpriteRendererComponent(sf::Texture* texture, sf::IntRect rect);

	~SpriteRendererComponent() 
	{
		
	}

	void OnDestroy() override 
	{
		//std::cout << "DELETESPRITE!";
		
	}

	void SetTexture(sf::Texture* texture, sf::IntRect rect);

	void SetRect(sf::IntRect rect)
	{
		Rect = rect;
		//std::cout << "Rect: " << Rect.position.x;
		//Rect = sf::IntRect();
		Sprite.setTextureRect(Rect);
		//Sprite->setOrigin((sf::Vector2f)Rect.getCenter());
	}

	virtual std::unique_ptr<Component> CloneComponent()
	{
		return std::make_unique<SpriteRendererComponent>(*this);
	}

	sf::IntRect getRect()
	{
		return Rect;
	}

};