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
#include "ParalaxScrollingHandler.h"
#include "PlayerShipController.h"
#include "SideScrollerHandler.h"
#include "PrefabHandler.h"
#include "MainMenuHandler.h"
#include "HealthComponent.h"


void Scene::Init(std::string data)
{

    
    //GameEssentialsGlobals::ForceClear();
    
    SetupScene();
    
}
Scene::~Scene()
{
    //GameEssentialsGlobals::ResetState();
}
void SceneTest::SetupScene(std::string data){
    //Define view

    ResourceHandler* SceneRh = &GameEssentialsGlobals::Rh;

    ResourceHandler LocalRh;
    GameEssentialsGlobals::LocalRh = &LocalRh;


    sf::View view({ 0,0 }, { 384, 256 });
    view.setCenter({ 190 ,200 });

    sf::Font MainFont("Assets/r-type.ttf");
    MainFont.setSmooth(false);
    //MainFont.

    Gameobject* ParalaxHandler = new Gameobject();
    ParalaxScrollingHandler* psh = ParalaxHandler->AddComponent<ParalaxScrollingHandler>();



    Gameobject* SpaceBg = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    SpaceBg->Name = "Spacebg";
    sf::Texture* SpaceTex = SceneRh->InitTexture("Spacebg", "Assets/SpaceBackground1Animated.png");
    sf::IntRect SpaceRect({ 0,0 }, { 1152,256 });
    SpriteRendererComponent* SpaceSprite = SpaceBg->AddComponent<SpriteRendererComponent>(SpaceTex, SpaceRect, 0);
    AnimatorComponent* SpaceAnimator = SpaceBg->AddComponent<AnimatorComponent>();
    //Animation clip forPlayer
    sf::IntRect RectF1S({ 0,0 }, { 1152,256 });
    sf::IntRect RectF2S({ 0,256 }, { 1152,256 });
    sf::IntRect RectF3S({ 0,256 * 2 }, { 1152,256 });
    sf::IntRect RectF4S({ 0,256 * 3 }, { 1152,256 });
    AnimationFrame amSpace0 = { RectF1S, 30 };
    AnimationFrame amSpace1 = { RectF2S, 30 };
    AnimationFrame amSpace2 = { RectF3S, 30 };
    AnimationFrame amSpace3 = { RectF4S, 30 };
    Animationstrip amsSpace = { {amSpace0,amSpace1,amSpace2,amSpace3}, true };
    //--------------------------------------------------------------

    //Adds the anim and plays
    SpaceAnimator->AddAnimation(amsSpace, "idle");
    SpaceAnimator->PlayAnim("idle");
    //SpaceSprite->UpdateLayer(0);


    Gameobject* SpaceBg2 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    SpaceBg2->Name = "Spacebg2";
    sf::Texture* SpaceTex2 = SceneRh->InitTexture("spacebg2", "Assets/SpaceBackgroundl3.png");
    SpriteRendererComponent* SpaceSprite2 = SpaceBg2->AddComponent<SpriteRendererComponent>(SpaceTex2, SpaceRect, 0);

    Gameobject* SpaceBg3 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    SpaceBg3->Name = "Spacebg3";
    sf::Texture* SpaceTex3 = SceneRh->InitTexture("spacebg3", "Assets/SpaceBackgroundl4.png");
    SpriteRendererComponent* SpaceSprite3 = SpaceBg3->AddComponent<SpriteRendererComponent>(SpaceTex3, SpaceRect, 0);





    Gameobject* Root = GameEssentialsGlobals::WorldRoot;

    Gameobject* Test = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);

    Test->Name = "Test1";

    std::cout << "RootChildren: ";

    for (auto children : Root->GetChildren())
    {
        std::cout << children->Name << ",";
    }

    //--------------------------------------------------------------------- Bullet Prefab ----------------------------------
    
    Gameobject* BulletPea = new Gameobject();
    BulletPea->Name = "bullet";
    sf::IntRect BulletRect({ 0,0 }, {17,4});
    sf::Texture* BulletTex = SceneRh->InitTexture("bulletP", "Assets/Bulletplr.png");
    BulletPea->AddComponent<SpriteRendererComponent>(BulletTex, BulletRect, 10);
    BulletPea->AddComponent<BulletComponent>();
    Collider* bpcollider = BulletPea->AddComponent<Collider>();
    
   
    bpcollider->Layer = "Player";
    bpcollider->ExcludedLayers = { "Player", "LevelBounds" };
    BulletPea->AddComponent<Rigidbody>();
    bpcollider->SetupCollider();
    bpcollider->IsTrigger = true;
    
    LocalRh.InitPrefab("bulletP", BulletPea);



    Gameobject* MediumBullet = new Gameobject();
    MediumBullet->Name = "bullet";
    sf::IntRect BulletRect2({ 0,0 }, { 30,9 });
    sf::Texture* BulletTex2 = SceneRh->InitTexture("bulletM", "Assets/MediumPlrBullet30x9.png");
    MediumBullet->AddComponent<SpriteRendererComponent>(BulletTex2, BulletRect2 , 10);
    auto bc = MediumBullet->AddComponent<BulletComponent>();
    bc->Damage = 8;
    Collider* bpcollider2 = MediumBullet->AddComponent<Collider>();


    bpcollider2->Layer = "Player";
    bpcollider2->ExcludedLayers = { "Player", "LevelBounds" };
    MediumBullet->AddComponent<Rigidbody>();
    bpcollider2->SetupCollider();
    bpcollider2->IsTrigger = true;

    LocalRh.InitPrefab("bulletM", MediumBullet);


    Gameobject* LargeBullet = new Gameobject();
    LargeBullet->Name = "bullet";
    sf::IntRect BulletRect3({ 0,0 }, { 55,17 });
    sf::IntRect BulletRect3ANIM({ 0,17 }, { 55,17 });
    sf::Texture* BulletTex3 = SceneRh->InitTexture("bulletL", "Assets/BigProjectile55x17.png");
    LargeBullet->AddComponent<SpriteRendererComponent>(BulletTex3, BulletRect3, 10);
    auto bc2 = LargeBullet->AddComponent<BulletComponent>();
    bc2->Damage = 15;
    Collider* bpcollider3 = LargeBullet->AddComponent<Collider>();


    bpcollider3->Layer = "Player";
    bpcollider3->ExcludedLayers = { "Player", "LevelBounds" };
    LargeBullet->AddComponent<Rigidbody>();
    bpcollider3->SetupCollider();
    bpcollider3->IsTrigger = true;
    auto Anim = LargeBullet->AddComponent<AnimatorComponent>();
    AnimationFrame amLb2 = { BulletRect3, 10 };
    AnimationFrame amLb3 = { BulletRect3ANIM, 10 };
    Animationstrip amLbs = { {amLb2,amLb3}, true };
    Anim->AddAnimation(amLbs, "idle");
    Anim->PlayAnim("idle");

    LocalRh.InitPrefab("bulletL", LargeBullet);
   



    //--------------------------------------------------------------------- Bullet Prefab ----------------------------------
    //SpaceBackground


    //endSpaceBackground


    Gameobject* Test2 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    Test2->Name = "Test2";
   


    Gameobject* Test4 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    Test4->Name = "Test4";

    PlayerShipController* tc = Test->AddComponent<PlayerShipController>();
    tc->Enabled = true;


    //Creates the ship sprite!!
    sf::Texture* texture = SceneRh->InitTexture("Spaceship", "Assets/Spaceship.png");
    sf::IntRect rect({ 0,0 }, { 23,11 });
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





    CameraComponent* CameraComp = Test2->AddComponent<CameraComponent>();
    Test2->AddComponent<SideScrollerHandler>()->Speed = 10;
    CameraComp->SetupCameraComp(view);

    Gameobject* Wall1 = new Gameobject();
    //Wall1->AddComponent<SpriteRendererComponent>(texture, rect);
    Wall1->SetParent(Test2);
    Collider* col = Wall1->AddComponent<Collider>();
    col->SetupCollider();
    col->BoxRect = { {0,0}, {400,400} };
    Wall1->SetlocalPosition({ 192,-150 });
    Wall1->Clone()->SetlocalPosition({ -592,-150 });
    Wall1->Clone()->SetlocalPosition({ -192,90 });
    Wall1->Clone()->SetlocalPosition({ -192,-528 });



    //Test->MoveTo(sf::Vector2f(300, 200));
    Test2->MoveTo({ 200,300 });
    Test->SetParent(Test2);
    //Test->MoveTo(sf::Vector2f(600, 200));
    //Test2->MoveTo({ 200,500 });
    src->Sprite.setColor(sf::Color(255, 255, 255));

    Gameobject* ShootPoint = new Gameobject();
    ShootPoint->SetParent(Test);
    ShootPoint->SetlocalPosition({ 23,0 });
    ShootPoint->AddComponent<BasicGunComponent>();
    //ShootPoint->AddComponent<SpriteRendererComponent>(texture, rect);

    sf::Texture* Forcetx = SceneRh->InitTexture("ForceUpgrade1", "Assets/Force16x19.png");
    sf::IntRect rectF({ 0,0 }, { 16,19 });
    Gameobject* ForcePoint = new Gameobject();
    ForcePoint->SetParent(Test);
    ForcePoint->SetlocalPosition({ 21,0 });
    ForcePoint->AddComponent<SpriteRendererComponent>(Forcetx, rectF);
    AnimatorComponent* ac1f = ForcePoint->AddComponent<AnimatorComponent>();
    sf::IntRect Forcer1({ 0,0 }, { 16,19 });
    sf::IntRect Forcer2({ 0,19 }, { 16,19 });
    sf::IntRect Forcer3({ 16,0 }, { 16,19 });
    sf::IntRect Forcer4({ 16,19 }, { 16,19 });
    AnimationFrame Eam0ef = { Forcer1, 40 };
    AnimationFrame Eam1ef = { Forcer2, 40 };
    AnimationFrame Eam2ef = { Forcer3, 40 };
    AnimationFrame Eam3ef = { Forcer4, 40 };

    Animationstrip Eamsef = { {Eam0ef,Eam2ef,Eam1ef,Eam3ef}, true };
    ac1f->AddAnimation(Eamsef, "Idle1");
    ac1f->PlayAnim("Idle1");

    //Set up enemy test

    //--------------------------------------------------------------
    //Clone
    //Gameobject* EClone = Test3->Clone();
    //EClone->MoveTo(sf::Vector2f(100, 300));
    //EClone->Enable();
    //EClone->Destroy();


    //Set up Explosion test
    Gameobject* ExplosionTest = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    ExplosionTest->Name = "Test4";
    sf::Texture* texture2e = SceneRh->InitTexture("Explosion1", "Assets/Explosion.png");
    sf::IntRect rect2e({ 0,0 }, { 48,48 });
    SpriteRendererComponent* src2e = ExplosionTest->AddComponent<SpriteRendererComponent>(texture2e, rect2e);
    AnimatorComponent* AnimCompEe = ExplosionTest->AddComponent<AnimatorComponent>();
    ExplosionTest->MoveTo(sf::Vector2f(200, 300));


    //Enemy1 animation clip
    sf::IntRect e1rect1e({ 0,0 }, { 48,48 });
    sf::IntRect e1rect2e({ 48 * 1,0 }, { 48,48 });
    sf::IntRect e1rect3e({ 48 * 2,0 }, { 48,48 });
    sf::IntRect e1rect4e({ 48 * 3,0 }, { 48,48 });
    sf::IntRect e1rect5e({ 48 * 4,0 }, { 48,48 });
    sf::IntRect e1rect6e({ 48 * 5,0 }, { 48,48 });
    sf::IntRect e1rect7e({ 0,0 }, { 0,0 });
    AnimationFrame Eam0e = { e1rect1e, 10 };
    AnimationFrame Eam1e = { e1rect2e, 10 };
    AnimationFrame Eam2e = { e1rect3e, 10 };
    AnimationFrame Eam3e = { e1rect4e, 10 };
    AnimationFrame Eam4e = { e1rect5e, 10 };
    AnimationFrame Eam5e = { e1rect6e, 10 };
    AnimationFrame Eam6e = { e1rect7e, 10 };
    Animationstrip Eamse = { {Eam0e,Eam1e,Eam2e,Eam3e,Eam4e,Eam5e,Eam6e }, false };
    AnimCompEe->AddAnimation(Eamse, "ex");
    AnimCompEe->PlayAnim("ex");
    //--------------------------------------------------------------
    //LocalRh.InitPrefab("Explosion", ExplosionTest);



    //--------------------MiniExplosion---------------------------------
    Gameobject* MiniExplosion = ExplosionTest->Clone();
    sf::Texture* texture2em = SceneRh->InitTexture("Explosionmini", "Assets/BulletExplosionBlueSmall.png");
    MiniExplosion->RemoveComponent<SpriteRendererComponent>();
    sf::IntRect e1rect1em({ 0,0 }, { 17,8 });
    MiniExplosion->AddComponent<SpriteRendererComponent>(texture2em,e1rect1em);

    //sf::IntRect e1rect1em({ 0,0 }, { 17,8 });
    sf::IntRect e1rect2em({ 0,0 }, { 17,8 });
    sf::IntRect e1rect3em({ 0,8 }, { 17,8 });
    sf::IntRect e1rect4em({ 0,16 }, { 17,8 });
    sf::IntRect e1rect5em({ 0,32 }, { 17,8 });
    sf::IntRect e1rect7em({ 0,0 }, { 0,0 });
    AnimationFrame Eam0em = { e1rect1em, 4 };
    AnimationFrame Eam1em = { e1rect2em, 4 };
    AnimationFrame Eam2em = { e1rect3em, 4 };
    AnimationFrame Eam3em = { e1rect4em, 4 };
    AnimationFrame Eam4em = { e1rect5em, 4 };
    AnimationFrame Eam6em = { e1rect7em, 4 };
    Animationstrip Eamsem = { {Eam0em,Eam1em,Eam2em,Eam3em,Eam4em,Eam6em,Eam6em }, false };

    MiniExplosion->GetComponent<AnimatorComponent>()->StopAnim();
    MiniExplosion->GetComponent<AnimatorComponent>()->AddAnimation(Eamsem, "ex");
    MiniExplosion->GetComponent<AnimatorComponent>()->PlayAnim("ex");

    LocalRh.InitPrefab("miniExplosion", MiniExplosion);
    LocalRh.InitPrefab("Explosion", ExplosionTest);
    //UI START--------------------------------------------------------------


    Gameobject* UiBgObj = new Gameobject();
    sf::Texture* BgText = SceneRh->InitTexture("White", "Assets/SolidWhite.png");

    sf::IntRect Bgrect({ 0,0 }, { 384,40 });
    UiBgObj->AddComponent<SpriteRendererComponent>(BgText, Bgrect)->Sprite.setColor({ 20,20,20 });

    Gameobject* BeamText = new Gameobject();


    TextRenderer* testtext = BeamText->AddComponent<TextRenderer>(&MainFont, "BEAM", 20);

    testtext->text.setStyle(sf::Text::Bold);

    testtext->text.setFillColor({ 148, 132, 240 });
    testtext->text.setCharacterSize(12);


    Gameobject* UiCanvas = new Gameobject();

    UiCanvasComponent* UiCanvasComp = UiCanvas->AddComponent<UiCanvasComponent>();

    BeamText->SetParent(UiCanvas);

    //BeamCharge
    Gameobject* BeamCharge = new Gameobject();

    sf::Texture* TexBeam2 = SceneRh->InitTexture("BeamChargeMiddle", "Assets/BeamChageMiddle.png");
    //sf::IntRect rectBeam2({ 0,0 }, { 80,15 });
    sf::IntRect rectBeam2({ 0,0 }, { 60,15 }); //80 = 0, 60 = -10, 50 = -15 posx = (maxsize - x)/2

    BeamCharge->AddComponent<SpriteRendererComponent>(TexBeam2, rectBeam2);
    
    //End


    //BeamHolder
    Gameobject* BeamHolder = new Gameobject();
    BeamHolder->SetParent(UiCanvas);
    BeamCharge->SetParent(BeamHolder);
    sf::Texture* TexBeam = SceneRh->InitTexture("AnimBeamCharge", "Assets/AnimatedBeamCharge.png");
    sf::IntRect rectBeam({ 0,0 }, { 90,15 });
    BeamHolder->AddComponent<SpriteRendererComponent>(TexBeam, rectBeam);
    AnimatorComponent* BeamAnimComponent = BeamHolder->AddComponent<AnimatorComponent>();
    BeamHolder->AddComponent <BeamUIRelay>();

    //Animation clip forPlayer
    sf::IntRect BeamChargeR1({ 0,0 }, { 90,15 });
    sf::IntRect BeamChargeR2({ 0,15 }, { 90,15 });
    AnimationFrame BeamChargeF1 = { BeamChargeR1, 10 };
    AnimationFrame BeamChargeF2 = { BeamChargeR2, 10 };
    Animationstrip ChargedFullAnim = { {BeamChargeF2,BeamChargeF1}, true };
    Animationstrip ChargedIdleAnim = { {BeamChargeF1}, true };


    //Adds the anim and plays
    BeamAnimComponent->AddAnimation(ChargedFullAnim, "ChargedFull");
    BeamAnimComponent->AddAnimation(ChargedIdleAnim, "idle");
    BeamAnimComponent->PlayAnim("idle");

    //BeamHolderFin
    

    //Heart
    Gameobject* Heart = new Gameobject();
    Heart->SetParent(UiCanvas);
    sf::Texture* Hearttex = SceneRh->InitTexture("HeartTex", "Assets/Heart.png");
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

    UiHoldObject->SetlocalPosition({ 0,0 });
    //SpaceBg->SetParent(UiCanvas);
    //SpaceBg->SetlocalPosition({ 0,0 });
    UiCanvasComp->SetupCanvas();

    ScoreDisplay->SetlocalPosition({ 0,15 });
    BeamText->SetlocalPosition({ -90,105 });
    Score->SetlocalPosition({ 70,96 });
    BeamHolder->SetlocalPosition({ 10,110 });
    BeamCharge->SetlocalPosition({ 0,0 });
    Heart->SetlocalPosition({ -120, 110 });
    Heart2->SetlocalPosition({ -140, 110 });
    Heart3->SetlocalPosition({ -160, 110 });

    BeamCharge->SetlocalPosition({ -10,0 });


    //SET UP GAME UI --------------------------------------------------------------



    Gameobject* Test3 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    Test3->Name = "Test3";
    sf::Texture* texture2 = SceneRh->InitTexture("Drone1", "Assets/Drone1.png");
    sf::IntRect rect2({ 0,0 }, { 20,20 });
    SpriteRendererComponent* src2 = Test3->AddComponent<SpriteRendererComponent>(texture2, rect2);
    AnimatorComponent* AnimCompE = Test3->AddComponent<AnimatorComponent>();
    Collider* collider2 = Test3->AddComponent<Collider>();
    collider2->SetupCollider();
    collider2->Layer = "Enemy";
    collider2->ExcludedLayers = { "Enemy", "LevelBounds"};
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
    Test3->AddComponent<HealthComponent>();

    //Enemy2

    Gameobject* GreenAlien = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    GreenAlien->Name = "Greenie";
    sf::Texture* textureGA = SceneRh->InitTexture("GreenAlien", "Assets/Greenie3.png");
    sf::IntRect rectGA({ 10,10 }, { 30,47 });
    SpriteRendererComponent* srcGA = GreenAlien->AddComponent<SpriteRendererComponent>(textureGA, rectGA);
    AnimatorComponent* AnimCompGA = GreenAlien->AddComponent<AnimatorComponent>();
    Collider* colliderGA = GreenAlien->AddComponent<Collider>();
    colliderGA->SetupCollider();
    Rigidbody* rbGA = GreenAlien->AddComponent<Rigidbody>();
    GreenAlien->MoveTo(sf::Vector2f(200, 300));


    //Enemy1 animation clip
    sf::IntRect e1rect1GA({ 0,0 }, { 50,67 });
    sf::IntRect e1rect2GA({ 50,0 }, { 50,67 });
    AnimationFrame EamGA0 = { e1rect1GA, 80 };
    AnimationFrame EamGA1 = { e1rect2GA, 80 };

    Animationstrip UpGA = { {EamGA1}, true };
    Animationstrip IdleGA = { {EamGA0,EamGA1}, true };
    AnimCompGA->AddAnimation(IdleGA, "idle");
    AnimCompGA->AddAnimation(UpGA, "up");
    AnimCompGA->PlayAnim("idle");
    auto hpga = GreenAlien->AddComponent<HealthComponent>();

    colliderGA->Layer = "Enemy";
    colliderGA->ExcludedLayers = { "Enemy", "LevelBounds" };
    hpga->Health = 40;
    //hpga->ExplosionPoints = { {30,30},{-30,-30},{0,0},{std::rand,-30} };





    for (int i = 0; i < 50; i++)
    {
        Gameobject* aaaaaa = Test3->Clone();
        //Gameobject* EClone2 = Test3->Clone();
        //EClone2->MoveTo(sf::Vector2f(100, 400));
        float x = (rand() % 300);  // width
        float y = (rand() % 100) - 100;  // height

        aaaaaa->MoveTo(sf::Vector2f(x, y) + Test2->getWorldPos());
        
        //EClone2->Destroy();
    }

    //
    //EClone->Destroy();
    //Test3->Destroy();
    //Test3->Destroy();



    std::cout << "\n\nSize of list: " << GameEssentialsGlobals::Colliders.size();


    sf::Texture* texture3 = SceneRh->InitTexture("Ptest", "ParentTest.png");
    sf::IntRect rect3({ 0,0 }, { 60,60 });
    SpriteRendererComponent* src3 = Test4->AddComponent<SpriteRendererComponent>(texture3, rect3);

    Collider* collider = Test->AddComponent<Collider>();
    collider->SetupCollider();
    collider->Layer = "Player";
    collider->ExcludedLayers = { "Player"};
    Rigidbody* rb = Test->AddComponent<Rigidbody>();

    //SpriteRendererComponent* src100 = Test3->GetComponent<SpriteRendererComponent>();

    //std::cout << "\n\n Component found in: " << GameEssentialsGlobals::FindFirstComponent<SpriteRendererComponent>()->GetGameObject()->Name;





    Collider* collider3 = Test4->AddComponent<Collider>();
    collider3->SetupCollider();


    Test->SetlocalPosition({ -100,-60 });

    Test4->MoveTo(sf::Vector2f(20, 300));

    psh->FocusPoint = CameraComp;
    psh->GetGameObject()->MoveTo(psh->FocusPoint->GetGameObject()->getWorldPos());
    psh->AddLayer("Main", SpaceBg, -0.2, 3);
    psh->AddLayer("Main2", SpaceBg2, -0.8, 3);
    psh->AddLayer("Main3", SpaceBg3, -1.3, 3);
    psh->GetGameObject()->MoveTo(Test->getWorldPos());

    //Test4->SetParent(Test);

    //-aaaaaaaaaaaaaaaaaaab-----------------

    std::cout << "\n\nRootChildren: ";

    //for (auto children : Root->GetChildren())
    //{
    //    std::cout << children->Name << ",";
    //}
   

    //Test->Disable();
    //Test3->Clone();

    //Test->Destroy();
    //ParalaxHandler->Clone();
    //ParalaxHandler->Destroy();
    LocalRh.InitPrefab("plr", Test);
   
    //Test->SetlocalPosition({ 0,-100 });

    Gameobject* ga = LocalRh.InstansiatePrefab("plr");
    //ga->MoveTo({ 0,0 });
    

    std::cout << "\n\nFound Componnet TestComponent: " << Test->HasComponent<TestComponent>();

    std::cout << "\n\nScene: \n";
    GameEssentialsGlobals::OutputSceneGraph(Root);
    //GameEssentialsGlobals::InputService->Init();

    sf::Vector2 v2(10, 10);

    sf::RenderWindow window(sf::VideoMode({ 384, 256 }), "F-type", sf::State::Fullscreen);
    window.setFramerateLimit(120);

    auto icon = sf::Image{};
    if (icon.loadFromFile("Assets/Spaceship.png"))
    {
        window.setIcon({ 23,11 }, icon.getPixelsPtr());
    }


   

    window.setView(CameraComp->CameraView);

    GameEssentialsGlobals::SetRenderWindow(&window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    //src->Sprite = shape.spr;

    GameEssentialsGlobals::StartGame();

    

    while (GameEssentialsGlobals::Renderwindow->isOpen())
    {
        //std::cout << "\n\TICK: \n";
        while (const std::optional event = GameEssentialsGlobals::Renderwindow->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                GameEssentialsGlobals::Renderwindow->close();
        }

        //window.clear();

        //window.draw(shape);
        //window.display();


        GameEssentialsGlobals::OnGameTick();
        //GameEssentialsGlobals::OnPhysicsTick();

        //SceneTest TestScene;

        //TestScene.Init();


    }
    
    //delete this;

    }

void SceneStart::SetupScene(std::string Params)
{
    //EssentialSetup!! ------------------------------------------------------------------------


    ResourceHandler* SceneRh = new ResourceHandler();

    sf::View view({ 0,0 }, { 384, 256 });


    sf::Font MainFont("Assets/r-type.ttf");
    MainFont.setSmooth(false);

    Gameobject* UiCanvas = new Gameobject();

    UiCanvasComponent* UiCanvasComp = UiCanvas->AddComponent<UiCanvasComponent>();

    Gameobject* CameraObj = new Gameobject();
    CameraComponent* CameraComp = CameraObj->AddComponent<CameraComponent>();
    CameraComp->SetupCameraComp(view);



    // ------------------------------------------------------------------------


    Gameobject* ParalaxHandler = new Gameobject();
    ParalaxScrollingHandler* psh = ParalaxHandler->AddComponent<ParalaxScrollingHandler>();

    psh->FocusPoint = CameraComp;

    Gameobject* SpaceBg = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    SpaceBg->Name = "Spacebg";
    sf::Texture* SpaceTex = SceneRh->InitTexture("Spacebg", "Assets/SpaceBackground1Animated.png");
    sf::IntRect SpaceRect({ 0,0 }, { 1152,256 });
    SpriteRendererComponent* SpaceSprite = SpaceBg->AddComponent<SpriteRendererComponent>(SpaceTex, SpaceRect, 0);
    AnimatorComponent* SpaceAnimator = SpaceBg->AddComponent<AnimatorComponent>();
    //Animation clip forPlayer
    sf::IntRect RectF1S({ 0,0 }, { 1152,256 });
    sf::IntRect RectF2S({ 0,256 }, { 1152,256 });
    sf::IntRect RectF3S({ 0,256 * 2 }, { 1152,256 });
    sf::IntRect RectF4S({ 0,256 * 3 }, { 1152,256 });
    AnimationFrame amSpace0 = { RectF1S, 30 };
    AnimationFrame amSpace1 = { RectF2S, 30 };
    AnimationFrame amSpace2 = { RectF3S, 30 };
    AnimationFrame amSpace3 = { RectF4S, 30 };
    Animationstrip amsSpace = { {amSpace0,amSpace1,amSpace2,amSpace3}, true };
    //--------------------------------------------------------------

    //Adds the anim and plays
    SpaceAnimator->AddAnimation(amsSpace, "idle");
    SpaceAnimator->PlayAnim("idle");
    //SpaceSprite->UpdateLayer(0);


    Gameobject* SpaceBg2 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    SpaceBg2->Name = "Spacebg2";
    sf::Texture* SpaceTex2 = SceneRh->InitTexture("spacebg2", "Assets/SpaceBackgroundl3.png");
    SpriteRendererComponent* SpaceSprite2 = SpaceBg2->AddComponent<SpriteRendererComponent>(SpaceTex2, SpaceRect, 0);

    Gameobject* SpaceBg3 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    SpaceBg3->Name = "Spacebg3";
    sf::Texture* SpaceTex3 = SceneRh->InitTexture("spacebg3", "Assets/SpaceBackgroundl4.png");
    SpriteRendererComponent* SpaceSprite3 = SpaceBg3->AddComponent<SpriteRendererComponent>(SpaceTex3, SpaceRect, 0);

    psh->AddLayer("Main", SpaceBg, -0.2, 3);
    psh->AddLayer("Main2", SpaceBg2, -0.8, 3);
    psh->AddLayer("Main3", SpaceBg3, -1.3, 3);

   

    Gameobject* PlayerPreview = new Gameobject();
    PlayerPreview->SetParent(CameraObj);

    sf::Texture* texture = SceneRh->InitTexture("Spaceship", "Assets/Spaceship.png");
    sf::IntRect rect({ 0,0 }, { 23,11 });
    SpriteRendererComponent* src = PlayerPreview->AddComponent<SpriteRendererComponent>(texture, rect);
    AnimatorComponent* amc = PlayerPreview->AddComponent<AnimatorComponent>();

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


    CameraObj->AddComponent<SideScrollerHandler>()->Speed = 10;
    PlayerPreview->SetlocalPosition({0,20});
    //----------------------------Text title-----------------------------





    Gameobject* TitleText = new Gameobject();
    TextRenderer* TitleTxt = TitleText->AddComponent<TextRenderer>(&MainFont, "F TYPE", 1);
    TitleTxt->text.setFillColor(sf::Color(180, 210, 255));
    TitleTxt->text.setStyle(sf::Text::Style::Bold);
    //TitleTxt->text.setStyle(sf::Text::Style::Underlined);
    TitleText->SetlocalPosition({ -150, -90 });
    TitleText->SetParent(UiCanvas);

    //------------------------- Start text-----------------------------

    Gameobject* Starttext = new Gameobject();
    TextRenderer* Starttxt = Starttext->AddComponent<TextRenderer>(&MainFont, "Press ENTER to start.", 2);
    Starttxt->text.setFillColor(sf::Color(180, 210, 255));
    Starttxt->text.setCharacterSize(10);
    //TitleTxt->text.setStyle(sf::Text::Style::Underlined);
    Starttext->SetlocalPosition({ -40, 90 });
    Starttext->SetParent(UiCanvas);

    MainMenuHandler* mm = UiCanvas->AddComponent<MainMenuHandler>();



    
    

    //-------------------------- Must be at the end!! --------------------------

    sf::RenderWindow window(sf::VideoMode({ 384, 256 }), "F-type", sf::State::Fullscreen);
    window.setFramerateLimit(120);

    auto icon = sf::Image{};
    if (icon.loadFromFile("Assets/Spaceship.png"))
    {
        window.setIcon({ 23,11 }, icon.getPixelsPtr());
    }

    window.setView(CameraComp->CameraView);


    GameEssentialsGlobals::SetRenderWindow(&window);

    GameEssentialsGlobals::StartGame();



    while (GameEssentialsGlobals::Renderwindow->isOpen() && mm->Trans == false)
    {
     
        while (const std::optional event = GameEssentialsGlobals::Renderwindow->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                GameEssentialsGlobals::Renderwindow->close();
        }

        


        GameEssentialsGlobals::OnGameTick();
        


    }

    if (mm->Trans && mm->NextScene != nullptr)
    {
        GameEssentialsGlobals::Renderwindow->close();
        GameEssentialsGlobals::LoadScene(mm->NextScene);
    }


}