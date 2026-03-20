#include <SFML/Graphics.hpp>
#include "Gameobject.h"
#include "Component.h"
#include "TestComponent.h"
#include "GameEssentials.h"
#include <iostream>
#include "SpriteRendererComponent.h"
/*
    This version of the SFML "hello world" is statically linked, you may wish to try the dynamically linked version as well.
*/
#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{
    //Define view
    sf::View view({ 200, 200 }, { 400, 400 });

    Gameobject* Root = GameEssentialsGlobals::WorldRoot;

    Gameobject* Test = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);

    Test->Name = "Test1";

    std::cout << "RootChildren: " ;

    for (auto children : Root->GetChildren())
    {
        std::cout << children->Name << ",";
    }

    Gameobject* Test2 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    Test2->Name = "Test2";

    Gameobject* Test3 = new Gameobject(sf::Vector2f(), sf::Angle(), true, Test);
    Test3->Name = "Test3";

    TestComponent* tc = Test->AddComponent<TestComponent>();
    tc->Enabled = true;


    //Create A stupid rectangle!!
    sf::Texture texture("ParentTest.png");
    sf::IntRect rect({0,0}, {60,60});
    SpriteRendererComponent* src = Test->AddComponent<SpriteRendererComponent>(texture, rect);
    
    Test->MoveTo(sf::Vector2f(300, 200));
    src->Sprite->setColor(sf::Color(0, 255, 0));


    sf::Texture texture2("ChildTest.png");
    sf::IntRect rect2({ 0,0 }, { 60,60 });
    SpriteRendererComponent* src2 = Test3->AddComponent<SpriteRendererComponent>(texture2, rect2);

    //SpriteRendererComponent* src100 = Test3->GetComponent<SpriteRendererComponent>();

    std::cout << "\n\n Component found in: " << GameEssentialsGlobals::FindFirstComponent<SpriteRendererComponent>()->GetGameObject()->Name;

    Test3->SetlocalPosition(sf::Vector2f(100, 0));

    Test->MoveTo(sf::Vector2f(100, 300));

    //-aaaaaaaaaaaaaaaaaaab-----------------

    std::cout << "\n\nRootChildren: ";

    for (auto children : Root->GetChildren())
    {
        std::cout << children->Name << ",";
    }
    
   
    //Test->Destroy();


    std::cout << "\n\nFound Componnet TestComponent: " << Test->HasComponent<TestComponent>();

    std::cout << "\n\nScene: \n";
    GameEssentialsGlobals::OutputSceneGraph(Root);

    sf::Vector2 v2(10,10);

    sf::RenderWindow window(sf::VideoMode({ 400, 400 }), "SFML works!");

    window.setView(view);

    GameEssentialsGlobals::SetRenderWindow(& window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    //src->Sprite = shape.spr;

    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //window.clear();

        //window.draw(shape);

        GameEssentialsGlobals::OnGameTick();
        GameEssentialsGlobals::OnPhysicsTick();
        
        
        //window.display();
    }
}