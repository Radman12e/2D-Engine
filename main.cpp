#include <SFML/Graphics.hpp>
#include "Gameobject.h"
#include "Component.h"
#include "TestComponent.h"
#include "GameEssentials.h"
#include <iostream>
#include "SpriteRendererComponent.h"
#include "AnimatorComponent.h"
#include "CameraComponent.h"
#include "UiCanvasComponent.h"
#include "TextRenderer.h"
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
    sf::View view({ 0,0 }, { 384, 256 });
    view.setCenter({ 190 ,200});

    sf::Font MainFont("Assets/r-type.ttf");
    MainFont.setSmooth(false);
    //MainFont.
    

    Gameobject* Root = GameEssentialsGlobals::WorldRoot;

    Gameobject* Test = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);

    Test->Name = "Test1";

    std::cout << "RootChildren: " ;

    for (auto children : Root->GetChildren())
    {
        std::cout << children->Name << ",";
    }


    //SpaceBackground

    Gameobject* SpaceBg = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    SpaceBg->Name = "Spacebg";
    sf::Texture* SpaceTex = new sf::Texture("Assets/SpaceBackground.png");
    sf::IntRect SpaceRect({ 0,0 }, { 1152,256 });
    SpriteRendererComponent* SpaceSprite = SpaceBg->AddComponent<SpriteRendererComponent>(SpaceTex, SpaceRect);

    //endSpaceBackground


    Gameobject* Test2 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    Test2->Name = "Test2";

    

    Gameobject* Test4 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    Test4->Name = "Test4";

    TestComponent* tc = Test->AddComponent<TestComponent>();
    
    
    tc->Enabled = true;


    //Creates the ship sprite!!
    sf::Texture* texture = new sf::Texture("Assets/Spaceship.png");
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
    src->Sprite.setColor(sf::Color(255, 255, 255));



    //Set up enemy test
    Gameobject* Test3 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    Test3->Name = "Test3";
    sf::Texture* texture2 = new sf::Texture("Assets/Drone1.png");
    sf::IntRect rect2({ 0,0 }, { 20,20 });
    SpriteRendererComponent* src2 = Test3->AddComponent<SpriteRendererComponent>(texture2, rect2);
    AnimatorComponent* AnimCompE = Test3->AddComponent<AnimatorComponent>();
    Collider* collider2 = Test3->AddComponent<Collider>();
    collider2->SetupCollider();
    Rigidbody* rb2 = Test3->AddComponent<Rigidbody>();
    //Test3->MoveTo(sf::Vector2f(200, 300));


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
    //EClone->Enable();
    //EClone->Destroy();
  

    //Set up Explosion test
    Gameobject* ExplosionTest = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    ExplosionTest->Name = "Test4";
    sf::Texture* texture2e = new sf::Texture("Assets/Explosion.png");
    sf::IntRect rect2e({ 0,0 }, { 48,48 });
    SpriteRendererComponent* src2e = ExplosionTest->AddComponent<SpriteRendererComponent>(texture2e, rect2e);
    AnimatorComponent* AnimCompEe = ExplosionTest->AddComponent<AnimatorComponent>();
    ExplosionTest->MoveTo(sf::Vector2f(200, 300));


    //Enemy1 animation clip
    sf::IntRect e1rect1e({ 0,0 }, { 48,48 });
    sf::IntRect e1rect2e({ 48 * 1,0 }, { 48,48 });
    sf::IntRect e1rect3e({  48 * 2,0 }, { 48,48 });
    sf::IntRect e1rect4e({ 48 * 3,0 }, { 48,48 });
    sf::IntRect e1rect5e({ 48 * 4,0 }, { 48,48 });
    sf::IntRect e1rect6e({ 48 * 5,0 }, { 48,48 });
    AnimationFrame Eam0e = { e1rect1e, 10 };
    AnimationFrame Eam1e = { e1rect2e, 10 };
    AnimationFrame Eam2e = { e1rect3e, 10 };
    AnimationFrame Eam3e = { e1rect4e, 10 };
    AnimationFrame Eam4e = { e1rect5e, 10 };
    AnimationFrame Eam5e = { e1rect6e, 10 };
    Animationstrip Eamse = { {Eam0e,Eam1e,Eam2e,Eam3e,Eam4e,Eam5e}, true };
    AnimCompEe->AddAnimation(Eamse, "ex");
    AnimCompEe->PlayAnim("ex");
    //--------------------------------------------------------------



    //UI START--------------------------------------------------------------


    Gameobject* UiBgObj = new Gameobject();
    sf::Texture* BgText = new sf::Texture("Assets/SolidWhite.png");

    sf::IntRect Bgrect({ 0,0 }, { 384,40 });
    UiBgObj->AddComponent<SpriteRendererComponent>(BgText, Bgrect)->Sprite.setColor({20,20,20});

    Gameobject* BeamText = new Gameobject();
   

    TextRenderer* testtext = BeamText->AddComponent<TextRenderer>(&MainFont, "BEAM");

    testtext->text.setStyle(sf::Text::Bold);

    testtext->text.setFillColor({ 148, 132, 240 });
    testtext->text.setCharacterSize(12);
    

    Gameobject* UiCanvas = new Gameobject();

    UiCanvasComponent* UiCanvasComp = UiCanvas->AddComponent<UiCanvasComponent>();

    BeamText->SetParent(UiCanvas);

    //BeamCharge
    Gameobject* BeamCharge = new Gameobject();
    
    sf::Texture* TexBeam2 = new sf::Texture("Assets/BeamChageMiddle.png");
    sf::IntRect rectBeam2({ 0,0 }, { 80,15 });
    BeamCharge->AddComponent<SpriteRendererComponent>(TexBeam2, rectBeam2);
    //End


    //BeamHolder
    Gameobject* BeamHolder = new Gameobject();
    BeamHolder->SetParent(UiCanvas);
    BeamCharge->SetParent(BeamHolder);
    sf::Texture* TexBeam = new sf::Texture("Assets/AnimatedBeamCharge.png");
    sf::IntRect rectBeam({ 0,0 }, { 90,15 });
    BeamHolder->AddComponent<SpriteRendererComponent>(TexBeam, rectBeam);
    AnimatorComponent* BeamAnimComponent = BeamHolder->AddComponent<AnimatorComponent>();

    //Animation clip forPlayer
    sf::IntRect BeamChargeR1({ 0,0 }, { 90,15 });
    sf::IntRect BeamChargeR2({ 0,15 }, { 90,15 });
    AnimationFrame BeamChargeF1 = { BeamChargeR1, 10 };
    AnimationFrame BeamChargeF2 = { BeamChargeR2, 10 };
    Animationstrip ChargedFullAnim = { {BeamChargeF1,BeamChargeF2}, true };
    Animationstrip ChargedIdleAnim = { {BeamChargeF1}, true };
  

    //Adds the anim and plays
    BeamAnimComponent->AddAnimation(ChargedFullAnim, "ChargedFull");
    BeamAnimComponent->AddAnimation(ChargedIdleAnim, "idle");
    BeamAnimComponent->PlayAnim("ChargedFull");

    //BeamHolderFin


    //Heart
    Gameobject* Heart = new Gameobject();
    Heart->SetParent(UiCanvas);
    sf::Texture* Hearttex = new sf::Texture("Assets/Heart.png");
    sf::IntRect Heartrect({ 0,0 }, { 15,15 });
    Heart->AddComponent<SpriteRendererComponent>(Hearttex, Heartrect);
    Gameobject* Heart2 = Heart->Clone();
    Gameobject* Heart3 = Heart->Clone();


    Gameobject* Score = BeamText->Clone();
    Score->Name = "Skibigidifig";
    Score->GetComponent<TextRenderer>()->text.setString("SCORE");

    Gameobject* ScoreDisplay = BeamText->Clone();
    ScoreDisplay->Name = "Skibigidifig2";
    ScoreDisplay->GetComponent<TextRenderer>()->text.setString("100000");
    ScoreDisplay->SetParent(Score);
    ScoreDisplay->GetComponent<TextRenderer>()->text.setFillColor(sf::Color::White);
    

    Gameobject* UiHoldObject = new Gameobject();
   
    UiBgObj->SetParent(UiHoldObject);
    UiBgObj->SetlocalPosition({ 0,110 });

    UiHoldObject->SetParent(UiCanvasComp->GetGameObject());
    //ScoreDisplay->SetParent(UiHoldObject);
    BeamText->SetParent(UiHoldObject);
    Score->SetParent(UiHoldObject);
    BeamHolder->SetParent(UiHoldObject);
    //BeamCharge->SetParent(UiHoldObject);
    Heart2->SetParent(UiHoldObject);
    Heart->SetParent(UiHoldObject);
    Heart3->SetParent(UiHoldObject);

    UiHoldObject->SetlocalPosition({0,0});

    UiCanvasComp->SetupCanvas();
   
    ScoreDisplay->SetlocalPosition({ 0,15 });
    BeamText->SetlocalPosition({-90,105});
    Score->SetlocalPosition({ 70,96 });
    BeamHolder->SetlocalPosition({ 10,110 });
    BeamCharge->SetlocalPosition({ 0,0 });
    Heart->SetlocalPosition({ -120, 110 });
    Heart2->SetlocalPosition({ -140, 110 });
    Heart3->SetlocalPosition({ -160, 110 });


    //SET UP GAME UI --------------------------------------------------------------


    for (int i = 0; i < 1; i++) 
    {
    
       Gameobject* EClone2 = Test3->Clone();
       EClone2->MoveTo(sf::Vector2f(100, 400));
       float x = rand() % 100;  // width
       float y = rand() % 100;  // height

        EClone2->MoveTo(sf::Vector2f(x, y));
        //EClone2->Destroy();
    }

    //
    EClone->Destroy();
    

    std::cout << "\n\nSize of list: " << GameEssentialsGlobals::Colliders.size();


    sf::Texture* texture3 = new sf::Texture("ParentTest.png");
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

    //for (auto children : Root->GetChildren())
    //{
    //    std::cout << children->Name << ",";
    //}
    
   
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
        //GameEssentialsGlobals::OnPhysicsTick();
        
        
        
        //window.display();
    }
}