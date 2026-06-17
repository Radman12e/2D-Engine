#pragma once
#include "string"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Gameobject;

#pragma once
class ResourceHandler
{

	std::unordered_map<std::string, Gameobject*> Prefabs = {};
	std::unordered_map<std::string, sf::Texture> Textures = {};


	std::unordered_map<std::string, sf::SoundBuffer> SoundBuffers = {};
	std::unordered_map<std::string, sf::Music*> MusicTracks = {};

	std::unordered_map<std::string, sf::Font*> Fonts = {};

public:

	void InitPrefab(std::string NameID, Gameobject* GameObjectPre);

	Gameobject* InstansiatePrefab(std::string NameID);


	~ResourceHandler();

	sf::Texture* InitTexture(std::string NameID, std::string Path);


	sf::Texture* GetTexture(std::string NameID);

	sf::SoundBuffer* InitSound(const std::string& NameID, const std::string& Path);

	sf::SoundBuffer* GetSound(const std::string& NameID);

	sf::Music* InitMusic(std::string NameID, std::string Path);

	sf::Music* GetMusic(const std::string& NameID);

	sf::Font* GetFont(const std::string& Dir);

	void ClearAllResources();
};

