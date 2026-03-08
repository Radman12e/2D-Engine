#include "GameEssentials.h"
#include "Gameobject.h"

GameEssentialsGlobals::GameEssentialsGlobals()
{

}

Gameobject* GameEssentialsGlobals::WorldRoot = new Gameobject(true);

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

void GameEssentialsGlobals::OnGameTick() 
{
	sf::Time dt = deltaclock.restart();

	for (auto& gameObject : GameObjectContainer)
	{
		gameObject->OnUpdate(dt.asSeconds());
	}

}

void GameEssentialsGlobals::OutputSceneGraph(Gameobject* obj, int depth)
{
    if (!obj) return;

    std::string indent = "";
    std::string branch = "";

    if (depth > 0)
    {
        indent = std::string((depth - 1) * 4, ' ');
        branch = "      |--- ";
    }

    std::cout << indent << branch << "(GameObject) " << obj->Name << "\n";

    // Components
    const auto& comps = obj->GetComponents();
    if (!comps.empty())
    {
        for (auto& comp : comps)
        {
            std::cout << indent << "                |--- (Component) [" << typeid(*comp).name() << "]\n";
        }
    }

    // Children
    for (auto child : obj->GetChildren())
    {
        OutputSceneGraph(child, depth + 1);
    }
}