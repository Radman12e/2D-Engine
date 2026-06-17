#pragma once
#include "Component.h"
#include "SoundClass.h"
class SoundComponent : public Component
{

public:
	std::unordered_map<std::string, std::unique_ptr<Sound>> Sounds = {};

	~SoundComponent() = default;
	void AddSound(std::unique_ptr<Sound> s, std::string Name)
	{
		Sounds[Name] = std::move(s);
	}
	void PlaySound(std::string Name)
	{
		auto it = Sounds.find(Name);
		if (it != Sounds.end())
		{
			it->second->playSound();
		}
	}

	std::unique_ptr<Component> CloneComponent() override
	{
		std::unique_ptr<SoundComponent> c2 = std::make_unique<SoundComponent>();
		for (const auto& [key, soundPtr] : Sounds)
		{
			if (soundPtr != nullptr)
			{
				//c2->Sounds[key] = std::make_unique<Sound>(soundPtr.get()->Dir);
			}
		
		}
		//GameEssentialsGlobals::AddSpriteToRenderLayer(SpriteRendererComponent2.get(), this->Layer);
		return c2;
	}
	
};

