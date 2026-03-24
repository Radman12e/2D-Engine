#include "UserInputService.h"
#include "GameEssentials.h"
#include <iostream>
UserInputService::UserInputService() 
{
	std::cout << "USERCREATED!!!!!!!!!!!!!!!!!!";
	std::function<void(InputArgs IA)> OnWPressedfn = [this](InputArgs IA) {std::cout << "WWW"; this->UpInputPressed(IA); };
	std::function<void(InputArgs IA)> OnAPressedfn = [this](InputArgs IA) {this->LeftInputPressed(IA); };
	std::function<void(InputArgs IA)> OnSPressedfn = [this](InputArgs IA) {this->DownInputPressed(IA); };
	std::function<void(InputArgs IA)> OnDPressedfn = [this](InputArgs IA) {this->RightInputPressed(IA); };
	std::function<void(InputArgs IA)> OnBtn1Pressedfn = [this](InputArgs IA) {this->Button1(IA); };
	std::function<void(InputArgs IA)> OnBtn2Pressedfn = [this](InputArgs IA) {this->Button2(IA); };


	GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::W, OnWPressedfn);
	GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::A, OnAPressedfn);
	GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::S, OnSPressedfn);
	GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::D, OnDPressedfn);
	GameEssentialsGlobals::InputEventH.BindEvent(sf::Mouse::Button::Left, OnBtn1Pressedfn);
	GameEssentialsGlobals::InputEventH.BindEvent(sf::Mouse::Button::Right, OnBtn2Pressedfn);
	GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::Space, OnBtn1Pressedfn);
	GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::LShift, OnBtn2Pressedfn);
}