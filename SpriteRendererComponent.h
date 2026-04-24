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
	sf::Texture Texture;
	sf::IntRect Rect = sf::IntRect({ 0,0 }, {0, 0});
	


public:

	
	sf::Sprite* Sprite = nullptr;//("");
	void OnUpdate(float dt) override;
	SpriteRendererComponent(sf::Texture texture, sf::IntRect rect);

	~SpriteRendererComponent() 
	{
		std::cout << "DELETESPRITE!";
		delete Sprite;
	}

	void SetTexture(sf::Texture texture, sf::IntRect rect);

	void SetRect(sf::IntRect rect)
	{
		Rect = rect;
		//std::cout << "Rect: " << Rect.position.x;
		//Rect = sf::IntRect();
		Sprite->setTextureRect(Rect);
		//Sprite->setOrigin((sf::Vector2f)Rect.getCenter());
	}

	sf::IntRect getRect() 
	{
		return Rect;
	}

};

