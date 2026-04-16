#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "GameEssentials.h"
#include "Gameobject.h"
class SpriteRendererComponent : public Component
{
private:
	//sf::IntRect rectSourceSprite(300, 0, 300, 400);
	sf::Texture Texture;
	
	sf::IntRect Rect;


public:


	sf::Sprite* Sprite = nullptr;//("");
	void OnUpdate(float dt) override;
	SpriteRendererComponent(sf::Texture texture, sf::IntRect rect);

	~SpriteRendererComponent() 
	{
		delete Sprite;
	}

	void SetTexture(sf::Texture texture, sf::IntRect rect);

	void SetRect(sf::IntRect rect)
	{
		Rect = rect;
		Sprite->setTextureRect(Rect);
		Sprite->setOrigin((sf::Vector2f)Rect.getCenter());
	}

	sf::IntRect getRect() 
	{
		return Rect;
	}

};

