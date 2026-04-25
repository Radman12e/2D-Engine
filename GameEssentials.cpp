#include "GameEssentials.h"
#include "Gameobject.h"
#include "Collider.h"
#include "Rigidbody.h"

GameEssentialsGlobals::GameEssentialsGlobals()
{

}



std::vector<ColliderStruct> GameEssentialsGlobals::Colliders = {};
std::vector<RigidbodyStruct> GameEssentialsGlobals::Rigidbodies = {};

Gameobject* GameEssentialsGlobals::WorldRoot = new Gameobject(true);

void GameEssentialsGlobals::RemoveGameObject(Gameobject* GameObject)
{
	GameObjectContainer.erase(std::remove(GameObjectContainer.begin(), GameObjectContainer.end(), GameObject), GameObjectContainer.end());
    //delete(GameObject);

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

size_t GameEssentialsGlobals::ColliderNextID = 0;

size_t GameEssentialsGlobals::rbNextID = 0;

InputEventHandler GameEssentialsGlobals::InputEventH;
EventHandler GameEssentialsGlobals::EventH;

size_t GameEssentialsGlobals::AddRigidbody(Rigidbody* rb) 
{
    RigidbodyStruct collider2 = { rb , rbNextID++ };
    Rigidbodies.push_back(collider2);
    return rbNextID;
}

size_t GameEssentialsGlobals::AddCollider(Collider* collider)
{
    ColliderStruct collider2 = { collider , ColliderNextID++ };
    Colliders.push_back(collider2);
    return ColliderNextID;

}
void GameEssentialsGlobals::RemoveCollider(size_t id)
{
    auto it = std::remove_if(Colliders.begin(), Colliders.end(),
        [id](const ColliderStruct& c) { return c.id == id; });

    if (it != Colliders.end())
    {
        Colliders.erase(it, Colliders.end());
    }

}

void GameEssentialsGlobals::RemoveRB(size_t id)
{
    auto it = std::remove_if(Rigidbodies.begin(), Rigidbodies.end(),
        [id](const RigidbodyStruct& c) { return c.id == id; });

    if (it != Rigidbodies.end())
    {
        Rigidbodies.erase(it, Rigidbodies.end());
    }

}


void GameEssentialsGlobals::OnGameTick() 
{

    InputEventH.OnGameTick();

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
    

    for (auto& gameObject : GameObjectContainer)
    {
        gameObject->OnLateUpdate((TimeSinceUpdate / 1000000) * Timescale);
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
    if (depth == 0) 
    {
        std::cout << "\n\n\n ";
    }

}

void GameEssentialsGlobals::StartGame() 
{
    for (RigidbodyStruct rb : GameEssentialsGlobals::Rigidbodies) 
    {
        rb.Rb->InitRB();
    }
}

sf::Vector2f GameEssentialsGlobals::CollisionCheckRB(Rigidbody* rb)
{
    sf::Vector2f CollisionResolve = { 0,0 };

    for (ColliderStruct coll : rb->Colliders)
    {
        sf::Vector2f Collisionc = CollisionCheckCollider(coll.collider, rb->Colliders);
        if (CollisionResolve.length() < Collisionc.length())
        {
            CollisionResolve = Collisionc;
        }
        //CollisionResolve += CollisionCheckCollider(coll.collider, rb->Colliders);
        //std::cout << "\n\nCOLLIDER!!";
    }
    return (CollisionResolve);


}

sf::Vector2f GameEssentialsGlobals::CollisionCheckCollider(Collider* collider, std::vector<ColliderStruct> excludedColliders, Rigidbody* rb)
{

    sf::Vector2f collisionOff = { 0,0 };
    for (ColliderStruct coll : Colliders)
    {
        sf::Vector2f collisionOffTemp;
        bool IsExcluded = false;
        for (ColliderStruct coll2 : excludedColliders)
        {
            if (coll.collider == coll2.collider)
            {
                IsExcluded = true;
                break;
            }
           
        }

        if (IsExcluded) continue;

        collisionOffTemp = collider->CheckCollision(coll.collider);
        collision c = { coll.collider, collider, rb };
        
        if (collisionOffTemp.length() > 0 && (collider->IsTrigger || coll.collider->IsTrigger))
        {
            //std::cout << "TRIGGER";
           
            coll.collider->GetGameObject()->OnTriggerEnter(c);
        }
        else if (collisionOffTemp.length() > 0 && (!collider->IsTrigger && !coll.collider->IsTrigger))
        {
           // std::cout << "NON TRIGGERS";
            collisionOff += collisionOffTemp;
            coll.collider->GetGameObject()->OnCollisionEntered(c);
        }


    }
    return (collisionOff);
}

