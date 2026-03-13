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

float GameEssentialsGlobals::tickLength = 8333.3f;

float GameEssentialsGlobals::physicsTimeStep = 33333.3f;

sf::RenderWindow* GameEssentialsGlobals::Renderwindow = nullptr;

std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point currentTime;

std::chrono::steady_clock::time_point PhyslastTime = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point PhyscurrentTime;

float dt = 0;
float pdt = 0;

float TimeSinceUpdate;
float TimeSincePhys;

float GameEssentialsGlobals::Timescale = 1.0f;

void GameEssentialsGlobals::OnGameTick() 
{

    Renderwindow->clear();

    currentTime = std::chrono::steady_clock::now();
	dt = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count();
    lastTime = currentTime;
    TimeSinceUpdate += dt;
    
    if (TimeSinceUpdate < tickLength)
    {
        
        return;
    }
    
    
	for (auto& gameObject : GameObjectContainer)
	{
		gameObject->OnUpdate((TimeSinceUpdate/1000000)*Timescale);
	}
    TimeSinceUpdate = 0;

    Renderwindow->display();
}

void GameEssentialsGlobals::OnPhysicsTick()
{

    PhyscurrentTime = std::chrono::steady_clock::now();
    pdt = std::chrono::duration_cast<std::chrono::microseconds>(PhyscurrentTime - PhyslastTime).count();
    PhyslastTime = PhyscurrentTime;
    TimeSincePhys += pdt;

    if (TimeSincePhys > physicsTimeStep)
    {
        for (auto& gameObject : GameObjectContainer)
        {
            gameObject->OnPhysicsUpdate((TimeSincePhys/ 1000000) * Timescale);
        }
        TimeSincePhys = 0;
    }
    else 
    {
        
    }
    
    
}

void GameEssentialsGlobals::OutputSceneGraph(Gameobject* obj, int depth)
{
    if (!obj) return;

    std::string indent = "";
    std::string branch = "";

    if (depth > 0)
    {
        indent = "\n"+ std::string((depth - 1) * 12, ' ');
        branch = "    |--- ";
    }

    std::cout << indent << branch << "(GameObject) " << obj->Name << "      ";

    const auto& comps = obj->GetComponents();
    if (!comps.empty())
    {
        for (auto& comp : comps)
        {
            std::cout << "(Component) [" << typeid(*comp).name() << "]  ";
        }
    }

    for (auto child : obj->GetChildren())
    {
        OutputSceneGraph(child, depth + 1);
    }
}

