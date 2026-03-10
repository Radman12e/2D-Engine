#include <SFML/Graphics.hpp>
#include "Gameobject.h"
#include "Component.h"
#include "TestComponent.h"
#include "GameEssentials.h"
#include <iostream>
/*
    This version of the SFML "hello world" is statically linked, you may wish to try the dynamically linked version as well.
*/
#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{
    
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


    std::cout << "\n\nRootChildren: ";

    for (auto children : Root->GetChildren())
    {
        std::cout << children->Name << ",";
    }

    std::cout << "\n\nFound Componnet TestComponent: " << Test->HasComponent<TestComponent>();

    std::cout << "\n\nScene: \n";
    GameEssentialsGlobals::OutputSceneGraph(Root);

    sf::Vector2 v2(10,10);

    sf::RenderWindow window(sf::VideoMode({ 400, 400 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        GameEssentialsGlobals::OnGameTick();
        GameEssentialsGlobals::OnPhysicsTick();
        window.clear();
        window.draw(shape);
        window.display();
    }
}