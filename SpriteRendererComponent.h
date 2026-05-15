#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "GameEssentials.h"
#include "Gameobject.h"
#include "Renderable.h"
#include <iostream>

class UiCanvasComponent;
class SpriteRendererComponent : public Component, public Renderable
{
private:
	//sf::IntRect rectSourceSprite(300, 0, 300, 400);
	sf::Texture* Texture;
	sf::IntRect Rect = sf::IntRect({ 0,0 }, { 0, 0 });
	



public:
	bool Setup = false;
	void BindToCanvas(UiCanvasComponent* Canvas);

	sf::Sprite Sprite;//("");
	void OnUpdate(float dt) override;

	void Render() override;

	SpriteRendererComponent(sf::Texture* texture, sf::IntRect rect, int Layer = 10);

	~SpriteRendererComponent() 
	{
		//std::cout << "Destroyed!!!";
	}

	

	

	void OnDestroy() override 
	{
		//std::cout << Texture;
		//delete this;
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

	virtual std::unique_ptr<Component> CloneComponent();

	sf::IntRect getRect()
	{
		return Rect;
	}

};