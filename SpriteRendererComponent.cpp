#include "SpriteRendererComponent.h"

void SpriteRendererComponent::OnLateUpdate(float dt)
{
	if (this->Enabled == false) return;

	Sprite.setPosition(this->GameObject->getWorldPos());
	Sprite.setRotation(this->GameObject->getLocalRot());

	//GameEssentialsGlobals::EventH.FireEvent("TestEvent1");

	

	if (GameEssentialsGlobals::Renderwindow != nullptr) 
	{
		//std::cout << "Rendered!!";
		GameEssentialsGlobals::Renderwindow->draw(Sprite);
	}

}
SpriteRendererComponent::SpriteRendererComponent(sf::Texture* texture, sf::IntRect rect) : Sprite(*texture, rect)
{
	Texture = texture;
	Rect = rect;
	Sprite = sf::Sprite(*Texture, Rect);
	std::cout << "\n" << "------------------ sprite made ------------------------\n";
	Sprite.setOrigin((sf::Vector2f)Rect.getCenter());
}

void SpriteRendererComponent::SetTexture(sf::Texture* texture, sf::IntRect rect)
{
	Texture = texture;
	Rect = rect;
	Sprite.setTexture(*texture);
	Sprite.setTextureRect(rect);
	Sprite.setOrigin((sf::Vector2f)Rect.getCenter());
}