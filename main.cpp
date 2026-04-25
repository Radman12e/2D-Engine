#include <SFML/Graphics.hpp>
#include "Gameobject.h"
#include "Component.h"
#include "TestComponent.h"
#include "GameEssentials.h"
#include <iostream>
#include "SpriteRendererComponent.h"
#include "AnimatorComponent.h"
#include "CameraComponent.h"
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
    sf::View view({ 200, 200 }, { 384, 256 });
    view.setCenter({ 190 ,200});

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

    

    Gameobject* Test4 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    Test4->Name = "Test4";

    TestComponent* tc = Test->AddComponent<TestComponent>();
    
    
    tc->Enabled = true;


    //Creates the ship sprite!!
    sf::Texture texture("Assets/Spaceship.png");
    sf::IntRect rect({0,0}, {23,11});
    SpriteRendererComponent* src = Test->AddComponent<SpriteRendererComponent>(texture, rect);
    AnimatorComponent* amc = Test->AddComponent<AnimatorComponent>();

    //Animation clip forPlayer
    sf::IntRect arect({ 0,0 }, { 23,11 });
    sf::IntRect arect2({ 0,11 }, { 23,11 });
    sf::IntRect arect3({ 0,22 }, { 23,11 });
    sf::IntRect arect4({ 0,33 }, { 23,11 });
    AnimationFrame am0 = { arect, 50 };
    AnimationFrame am1 = { arect2, 50 };
    AnimationFrame am2 = { arect3, 50 };
    AnimationFrame am3 = { arect4, 50 };
    Animationstrip ams = { {am0,am1,am2,am3}, true };
    //--------------------------------------------------------------

    //Adds the anim and plays
    amc->AddAnimation(ams, "idle");
    amc->PlayAnim("idle");





    CameraComponent* CameraComp = Test->AddComponent<CameraComponent>();
    CameraComp->SetupCameraComp(view);
   


    
    
    Test->MoveTo(sf::Vector2f(300, 200));
    src->Sprite->setColor(sf::Color(255, 255, 255));



    //Set up enemy test
    Gameobject* Test3 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    Test3->Name = "Test3";
    sf::Texture texture2("Assets/Drone1.png");
    sf::IntRect rect2({ 0,0 }, { 20,20 });
    SpriteRendererComponent* src2 = Test3->AddComponent<SpriteRendererComponent>(texture2, rect2);
    AnimatorComponent* AnimCompE = Test3->AddComponent<AnimatorComponent>();
    Collider* collider2 = Test3->AddComponent<Collider>();
    collider2->SetupCollider();
    Rigidbody* rb2 = Test3->AddComponent<Rigidbody>();
    Test3->MoveTo(sf::Vector2f(200, 300));


    //Enemy1 animation clip
    sf::IntRect e1rect1({ 0,0 }, { 20,20 });
    sf::IntRect e1rect2({ 0,20 }, { 20,20 });
    sf::IntRect e1rect3({ 0,40 }, { 20,20 });
    sf::IntRect e1rect4({ 20,0 }, { 20,20 });
    sf::IntRect e1rect5({ 20,20 }, { 20,20 });
    AnimationFrame Eam0 = { e1rect1, 20 };
    AnimationFrame Eam1 = { e1rect4, 20 };
    AnimationFrame Eam2 = { e1rect2, 20 };
    AnimationFrame Eam3 = { e1rect5, 20 };
    AnimationFrame Eam4 = { e1rect3, 20 };
    Animationstrip Eams = { {Eam0,Eam1,Eam2,Eam3,Eam4}, true };
    AnimCompE->AddAnimation(Eams, "idle");
    AnimCompE->PlayAnim("idle");
    //--------------------------------------------------------------
    //Clone
    Gameobject* EClone = Test3->Clone();
    EClone->MoveTo(sf::Vector2f(100, 300));
    EClone->Disable();
    EClone->Enable();
    //---------------
    



    sf::Texture texture3("ParentTest.png");
    sf::IntRect rect3({ 0,0 }, { 60,60 });
    SpriteRendererComponent* src3 = Test4->AddComponent<SpriteRendererComponent>(texture3, rect3);

    Collider* collider = Test->AddComponent<Collider>();
    collider->SetupCollider();
    Rigidbody* rb = Test->AddComponent<Rigidbody>();

    //SpriteRendererComponent* src100 = Test3->GetComponent<SpriteRendererComponent>();

    std::cout << "\n\n Component found in: " << GameEssentialsGlobals::FindFirstComponent<SpriteRendererComponent>()->GetGameObject()->Name;

    

   

    Collider* collider3 = Test4->AddComponent<Collider>();
    collider3->SetupCollider();
    

    Test->MoveTo(sf::Vector2f(100, 300));

    Test4->MoveTo(sf::Vector2f(20, 300));
    //Test4->SetParent(Test);

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
    //GameEssentialsGlobals::InputService->Init();

    sf::Vector2 v2(10,10);

    sf::RenderWindow window(sf::VideoMode({ 384, 256 }), "SFML works!");

    window.setView(CameraComp->CameraView);

    GameEssentialsGlobals::SetRenderWindow(& window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    //src->Sprite = shape.spr;

    GameEssentialsGlobals::StartGame();

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