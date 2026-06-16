#pragma once
#include "Component.h"
#include "SoundClass.h"
class SoundComponent
{
private:
	std::vector<Sound> Sounds = {};
	int MaxSounds = 10;
public:
	SoundComponent(int MaxSounds = 10) 
	{
		this->MaxSounds = MaxSounds;
		Sounds.reserve(MaxSounds);

	}
};

