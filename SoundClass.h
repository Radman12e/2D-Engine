#pragma once
#include "Component.h"
#include "PrefabHandler.h"
#include "GameEssentials.h"
#include <SFML/Audio.hpp>
class Sound
{
private:
    sf::SoundBuffer* buffer;
    std::unique_ptr<sf::Sound> Audio = nullptr;
public:
    bool SoundLoaded = false;
    
    std::string Dir = "";

    Sound(std::string dir)
    {
        Dir = dir;
        buffer = GameEssentialsGlobals::Rh.InitSound(dir, dir);
        if (buffer == nullptr) return;
        SoundLoaded = true;
        Audio = std::make_unique<sf::Sound>(*buffer);
    }

    ~Sound() 
    {
        if (Audio != nullptr && Audio.get()) 
        {
            Audio->stop();
        }
    }

    void playSound() 
    {
        if (Audio != nullptr && SoundLoaded) Audio->play();

    }

    void stopSound()
    {
        if (Audio != nullptr && SoundLoaded) Audio->stop();

    }

    sf::Sound* GetSound()
    {
        return Audio.get();
    }


};

