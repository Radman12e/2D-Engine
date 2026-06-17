#include "MainMenuHandler.h"
#include "Scene.h"
void MainMenuHandler::OnAlive()
{
	//std::cout << "StartedComp!!--------------------------";
	Component::OnAlive();
	std::cout << "StartedComp!!--------------------------";

	

	std::function<void(InputArgs IA)> OnWPressedfn = [this](InputArgs IA)
		{
			//GameEssentialsGlobals::Renderwindow->close();
			NextScene = new SceneTest();
			GameEssentialsGlobals::LoadScene(NextScene);
		};
	

	this->bindEvent(sf::Keyboard::Key::Enter, OnWPressedfn);
	

	//GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::W, OnWPressedfn);
	//GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::D, OnWPressedfn2);
	//GameEssentialsGlobals::InputEventH.UnBindEvent(sf::Keyboard::Key::W, Event);
}