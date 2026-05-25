#include "SpriteRendererComponent.h"
#include "UiCanvasComponent.h"

void SpriteRendererComponent::BindToCanvas(UiCanvasComponent* Canvas)
{
	std::function<void(EventArgs)> OnSPressedfn = [this](EventArgs)
		{
			GameEssentialsGlobals::Renderwindow->draw(this->Sprite);
		};

	this->bindEvent("CanvasUpdate"+std::to_string(Canvas->ID), OnSPressedfn);
}

void SpriteRendererComponent::OnUpdate(float dt)
{
	if (Setup == false) 
	{
		Setup = true;
		GameEssentialsGlobals::AddSpriteToRenderLayer(this, this->GetLayer());
	}
	if (this->Enabled == false) return;

	//GameEssentialsGlobals::EventH.FireEvent("TestEvent1");

	

	

}

void SpriteRendererComponent::Render() 
{
	if (!Enabled) return;
	if (GameEssentialsGlobals::Renderwindow != nullptr)
	{
		//std::cout << "Rendered!!";
		Sprite.setPosition(this->GameObject->getWorldPos());
		Sprite.setRotation(this->GameObject->getLocalRot());
		GameEssentialsGlobals::Renderwindow->draw(Sprite);
	}
}

SpriteRendererComponent::SpriteRendererComponent(sf::Texture* texture, sf::IntRect rect, int Layer) : Sprite(*texture, rect)
{
	Texture = texture;
	Rect = rect;
	Sprite = sf::Sprite(*Texture, Rect);
	std::cout << "\n" << "------------------ sprite made ------------------------\n";
	Sprite.setOrigin((sf::Vector2f)Rect.getCenter());
	this->Layer = Layer;
	GameEssentialsGlobals::AddSpriteToRenderLayer(this, Layer);
	Setup = true;
}



std::unique_ptr<Component> SpriteRendererComponent::CloneComponent()
{
	std::unique_ptr<SpriteRendererComponent> SpriteRendererComponent2 = std::make_unique<SpriteRendererComponent>(*this);
	SpriteRendererComponent2.get()->Setup = false;
	//GameEssentialsGlobals::AddSpriteToRenderLayer(SpriteRendererComponent2.get(), this->Layer);
	return SpriteRendererComponent2;
}
void SpriteRendererComponent::SetTexture(sf::Texture* texture, sf::IntRect rect)
{
	Texture = texture;
	Rect = rect;
	Sprite.setTexture(*texture);
	Sprite.setTextureRect(rect);
	Sprite.setOrigin((sf::Vector2f)Rect.getCenter());
}