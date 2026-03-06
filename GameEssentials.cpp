#include "GameEssentials.h"
#include "Gameobject.h"

GameEssentialsGlobals::GameEssentialsGlobals()
{

}

Gameobject GameEssentialsGlobals::WorldRoot = new Gameobject(true);

void GameEssentialsGlobals::RemoveGameObject(Gameobject* GameObject)
{
	GameObjectContainer.erase(std::remove(GameObjectContainer.begin(), GameObjectContainer.end(), GameObject), GameObjectContainer.end());

}

Gameobject* GameEssentialsGlobals::InstansiateGameObject(Gameobject* gameObject)
{
	GameObjectContainer.push_back(gameObject);
	return gameObject;

}

std::vector<Gameobject*> GameEssentialsGlobals::GameObjectContainer = std::vector <Gameobject*>();

float GameEssentialsGlobals::TicksPerSecond = 30;

sf::Clock deltaclock;

void  GameEssentialsGlobals::OnGameTick() 
{
	sf::Time dt = deltaclock.restart();

	for (auto& gameObject : GameObjectContainer)
	{
		gameObject->OnUpdate(dt.asSeconds());
	}

}