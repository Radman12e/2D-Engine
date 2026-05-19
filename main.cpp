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

    Scene* ActiveScene2 = new SceneStart();

    GameEssentialsGlobals::LoadScene(ActiveScene2);
    
    //GameEssentialsGlobals::LoadScene(ActiveScene);

    
}