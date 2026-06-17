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
#include "Scene.h";
/*
    This version of the SFML "hello world" is statically linked, you may wish to try the dynamically linked version as well.
*/
#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{

   

   

    //-------------------------- Must be at the end!! --------------------------

    sf::RenderWindow window(sf::VideoMode({ 384, 256 }), "F-type", sf::State::Fullscreen);
    window.setFramerateLimit(120);

    auto icon = sf::Image{};
    if (icon.loadFromFile("Assets/Spaceship.png"))
    {
        window.setIcon({ 23,11 }, icon.getPixelsPtr());
    }

    


    GameEssentialsGlobals::SetRenderWindow(&window);


    Scene* ActiveScene2 = new SceneStart();
    GameEssentialsGlobals::LoadScene(ActiveScene2);
    
    
    while (GameEssentialsGlobals::Renderwindow->isOpen())
    {

        while (const std::optional event = GameEssentialsGlobals::Renderwindow->pollEvent())
        {
            if (event->is<sf::Event::Closed>()) 
            {
                
                GameEssentialsGlobals::Rh.ClearAllResources();
                GameEssentialsGlobals::Renderwindow->close();

            }
        }

     


        GameEssentialsGlobals::OnGameTick();
        //std::cout << "Loaded!";



    }
   
    GameEssentialsGlobals::ResetState();

    std::cout << "Shutdown!";

    
}