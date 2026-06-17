#include <SFML/Graphics.hpp>
#include "Gameobject.h"
#include "Component.h"
#include "GameEssentials.h"
#include <iostream>
#include "SpriteRendererComponent.h"
#include "AnimatorComponent.h"
#include "CameraComponent.h"
#include "UiCanvasComponent.h"
#include "TextRenderer.h"
#include "PrefabHandler.h"


void Scene::Init(std::string data)
{

    
    //GameEssentialsGlobals::ForceClear();
    
    SetupScene();
    
}
Scene::~Scene()
{
    //GameEssentialsGlobals::ResetState();
}

// Template scene--------------------------------------------------------------------------------------------------------------------------------------
void SceneTest::SetupScene(std::string data){
    //Define view

    ResourceHandler* SceneRh = &GameEssentialsGlobals::Rh;

    ResourceHandler LocalRh;
    GameEssentialsGlobals::LocalRh = SceneRh;




    sf::View view({ 0,0 }, { 384, 256 });
    view.setCenter({ 190 ,200 });


    //-------------------------------------------------------------------------------------------------------- Your code below 





    sf::Font* MainFont = SceneRh->GetFont("Assets/r-type.ttf");
    MainFont->setSmooth(false);
   
    Gameobject CameraGO = new Gameobject();
    auto CameraComp = CameraGO.AddComponent<CameraComponent>();
    CameraComp->SetupCameraComp(view);
    


    std::cout << "\n\nScene: \n";




    //---------------------------------------------------------------------------------------------------------- Your code above
    GameEssentialsGlobals::Renderwindow->setView(CameraComp->CameraView);
    //src->Sprite = shape.spr;

    GameEssentialsGlobals::StartGame();

    

   

 }

void SceneStart::SetupScene(std::string Params)
{
    //EssentialSetup!! ------------------------------------------------------------------------


    ResourceHandler* SceneRh = &GameEssentialsGlobals::Rh;

    sf::View view({ 0,0 }, { 384, 256 });


    sf::Font* MainFont = SceneRh->GetFont("Assets/r-type.ttf");
    MainFont->setSmooth(false);


    Gameobject* UiCanvas = new Gameobject();

    UiCanvasComponent* UiCanvasComp = UiCanvas->AddComponent<UiCanvasComponent>();

    Gameobject* CameraObj = new Gameobject();
    CameraComponent* CameraComp = CameraObj->AddComponent<CameraComponent>();
    CameraComp->SetupCameraComp(view);



    // ------------------------------------------------------------------------


    

    Gameobject* SpaceBg = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    SpaceBg->Name = "Spacebg";
    sf::Texture* SpaceTex = SceneRh->InitTexture("Spacebg", "Assets/SpaceBackground1Animated.png");
    sf::IntRect SpaceRect({ 0,0 }, { 1152,256 });
    SpriteRendererComponent* SpaceSprite = SpaceBg->AddComponent<SpriteRendererComponent>(SpaceTex, SpaceRect, 0);
    AnimatorComponent* SpaceAnimator = SpaceBg->AddComponent<AnimatorComponent>();
    //Animation clip for background
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

    SpaceAnimator->AddAnimation(amsSpace, "idle");
    SpaceAnimator->PlayAnim("idle");


    Gameobject* SpaceBg2 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    SpaceBg2->Name = "Spacebg2";
    sf::Texture* SpaceTex2 = SceneRh->InitTexture("spacebg2", "Assets/SpaceBackgroundl3.png");
    SpriteRendererComponent* SpaceSprite2 = SpaceBg2->AddComponent<SpriteRendererComponent>(SpaceTex2, SpaceRect, 0);

    Gameobject* SpaceBg3 = new Gameobject(sf::Vector2f(), sf::Angle(), true, nullptr);
    SpaceBg3->Name = "Spacebg3";
    sf::Texture* SpaceTex3 = SceneRh->InitTexture("spacebg3", "Assets/SpaceBackgroundl4.png");
    SpriteRendererComponent* SpaceSprite3 = SpaceBg3->AddComponent<SpriteRendererComponent>(SpaceTex3, SpaceRect, 0);

   

    //----------------------------Text title-----------------------------





    Gameobject* TitleText = new Gameobject();
    TextRenderer* TitleTxt = TitleText->AddComponent<TextRenderer>(MainFont, "Your menu", 1);
    TitleTxt->text.setFillColor(sf::Color(180, 210, 255));
    TitleTxt->text.setStyle(sf::Text::Style::Bold);
    TitleText->SetlocalPosition({ -150, -90 });
    TitleText->SetParent(UiCanvas);

    //------------------------- Start text-----------------------------

    Gameobject* Starttext = new Gameobject();
    TextRenderer* Starttxt = Starttext->AddComponent<TextRenderer>(MainFont, "START CREATING!!!", 2);
    Starttxt->text.setFillColor(sf::Color(180, 210, 255));
    Starttxt->text.setCharacterSize(10);
    Starttext->SetlocalPosition({ -40, 90 });
    Starttext->SetParent(UiCanvas);



    
    //EssentialSetup!! ------------------------------------------------------------------------

    GameEssentialsGlobals::Renderwindow->setView(CameraComp->CameraView);

    GameEssentialsGlobals::StartGame();



    


}