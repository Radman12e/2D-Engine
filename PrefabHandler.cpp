#include "PrefabHandler.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "Gameobject.h"
#include <SFML/Audio.hpp>
void ResourceHandler::InitPrefab(std::string NameID, Gameobject* GameObjectPre)
{
    GameObjectPre->Disable();

    if (Prefabs.find(NameID) != Prefabs.end())
    {
        std::cout << "Prefab already exists: " << NameID << "\n";
        return;
    }

    Prefabs[NameID] = GameObjectPre;
}

Gameobject* ResourceHandler::InstansiatePrefab(std::string NameID)
{
    if (Prefabs.find(NameID) == Prefabs.end())
    {
        std::cout << "Prefab not found: " << NameID << "\n";
        return nullptr;
    }
    auto t = Prefabs[NameID]->Clone();
    t->Enable();
    t->MoveTo(Prefabs[NameID]->getWorldPos());
    //std::cout << "PrefabFound!";
    return t;

}

sf::Texture* ResourceHandler::InitTexture(std::string NameID, std::string Path)
{
    auto it = Textures.find(NameID);

    if (it != Textures.end())
    {
        return &it->second;
    }

    sf::Texture texture;

    if (!texture.loadFromFile(Path))
    {
        std::cout << "Failed to load texture: " << Path << "\n";
        return nullptr;
    }

    Textures[NameID] = std::move(texture);

    return &Textures[NameID];
}

sf::Texture* ResourceHandler::GetTexture(std::string NameID)
{
    if (Textures.find(NameID) == Textures.end())
    {
        std::cout << "Texture not found: " << NameID << "\n";
        return nullptr;
    }

    return &Textures[NameID];
}

sf::SoundBuffer* ResourceHandler::InitSound(const std::string& NameID, const std::string& Path)
{
    auto it = SoundBuffers.find(NameID);

    if (it != SoundBuffers.end())
    {
        return &it->second;
    }

    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile(Path))
    {
        std::cout << "Failed to load sound: " << Path << "\n";
        return nullptr;
    }

    SoundBuffers[NameID] = std::move(buffer);

    return &SoundBuffers[NameID];
}

sf::SoundBuffer* ResourceHandler::GetSound(const std::string& NameID)
{
    auto it = SoundBuffers.find(NameID);

    if (it == SoundBuffers.end())
    {
        std::cout << "Sound not found: " << NameID << "\n";
        return nullptr;
    }

    return &SoundBuffers[NameID];
}

sf::Music* ResourceHandler::InitMusic(std::string NameID, std::string Path)
{
    auto it = MusicTracks.find(NameID);

    if (it != MusicTracks.end())
    {
        return it->second;
    }

    sf::Music* music = new sf::Music();

    if (!music->openFromFile(Path))
    {
        std::cout << "Failed to load music: " << Path << "\n";

        delete music;
        return nullptr;
    }

    MusicTracks[NameID] = music;

    return music;
}

sf::Music* ResourceHandler::GetMusic(const std::string& NameID)
{
    auto it = MusicTracks.find(NameID);

    if (it == MusicTracks.end())
    {
        std::cout << "Music not found: " << NameID << "\n";
        return nullptr;
    }

    return MusicTracks[NameID];
}

ResourceHandler::~ResourceHandler()
{
    for (auto& [name, gameo] : Prefabs)
    {
        gameo->Destroy();
    }

    Textures.clear();
    SoundBuffers.clear();

    for (auto& [name, mu] : MusicTracks)
    {
        delete mu;
    }
}