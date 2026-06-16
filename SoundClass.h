#pragma once
#include "Component.h"
#include "PrefabHandler.h"
#include "GameEssentials.h"
#include <SFML/Audio.hpp>
class Sound
{
private:
    sf::SoundBuffer* buffer;
    sf::Sound* soundTest;
    std::unique_ptr<sf::Sound> Audio = nullptr;
public:
    bool SoundLoaded = false;
    


    Sound(std::string dir)
    {
        buffer = GameEssentialsGlobals::Rh.InitSound(dir, dir);
        if (buffer == nullptr) return;
        SoundLoaded = true;
        Audio = std::make_unique<sf::Sound>(*buffer);
    }
    ~Sound() = default;

    void playSound() 
    {
        if (Audio != nullptr && SoundLoaded) Audio->play();

    }

    sf::Sound* GetSound()
    {
        return Audio.get();
    }


};

