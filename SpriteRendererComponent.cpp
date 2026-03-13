#include "SpriteRendererComponent.h"

void SpriteRendererComponent::OnUpdate(float dt)
{
	if (this->Enabled == false) return;

	Sprite->setPosition(this->GameObject->getWorldPos());
	Sprite->setRotation(this->GameObject->getLocalRot());

	

	if (GameEssentialsGlobals::Renderwindow != nullptr) 
	{
		//std::cout << "Rendered!!";
		GameEssentialsGlobals::Renderwindow->draw(*Sprite);
	}

}
SpriteRendererComponent::SpriteRendererComponent(sf::Texture texture, sf::IntRect rect)
{
	Texture = texture;
	Rect = rect;
	Sprite = new sf::Sprite(Texture, Rect);
	std::cout << "\n" << "------------------ sprite made ------------------------\n";
	Sprite->setOrigin((sf::Vector2f)Rect.getCenter());
}

void SpriteRendererComponent::SetTexture(sf::Texture texture, sf::IntRect rect)
{
	Texture = texture;
	Rect = rect;
	Sprite->setTexture(texture);
	Sprite->setTextureRect(rect);
	Sprite->setOrigin((sf::Vector2f)Rect.getCenter());
}