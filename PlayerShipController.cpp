#include "PlayerShipController.h"

void PlayerShipController::OnUpdate(float dt)
{
	//Component::OnUpdate(dt);
	if (this->Enabled == false) return;
	if (Setup1 == false) 
	{
		Setup1 = true;
		Setup();
	}
	sf::Vector2f MovementResolve = {0,0};

	if (WHeld) MovementResolve.y -= 80 * SpeedMulti;
	if (AHeld) MovementResolve.x -= 80 * SpeedMulti;
	if (SHeld) MovementResolve.y += 80 * SpeedMulti;
	if (DHeld) MovementResolve.x += 80 * SpeedMulti;

	GameObject->GetComponent<Rigidbody>()->Velocity = MovementResolve;

	if (SpaceHeld) 
	{
		BeamHeldTime += dt;
	}

	//std::cout << "\n TICK: " << dt;

}

void PlayerShipController::OnPhysicsUpdate(float dt)
{
	Component::OnPhysicsUpdate(dt);
	if (this->Enabled == false) return;


	//std::cout << "\n PHYSICSTICK: " << dt;

}

void PlayerShipController::OnWPressed(InputArgs args)
{
	if (args.phase == InputPhase::Started)
	{
		WHeld = true;
		
		//GameObject->MoveTo(sf::Vector2f(300, 200));
	}
	else if (args.phase == InputPhase::Ended) 
	{
		WHeld = false;
	}
}
void PlayerShipController::OnAPressed(InputArgs args)
{
	if (args.phase == InputPhase::Started)
	{
		AHeld = true;

		//GameObject->MoveTo(sf::Vector2f(300, 200));
	}
	else if (args.phase == InputPhase::Ended)
	{
		AHeld = false;
	}

}
void PlayerShipController::OnSPressed(InputArgs args)
{
	if (args.phase == InputPhase::Started)
	{
		SHeld = true;

		//GameObject->MoveTo(sf::Vector2f(300, 200));
	}
	else if (args.phase == InputPhase::Ended)
	{
		SHeld = false;
	}

}
void PlayerShipController::OnDPressed(InputArgs args)
{
	if (args.phase == InputPhase::Started)
	{
		DHeld = true;

		//GameObject->MoveTo(sf::Vector2f(300, 200));
	}
	else if (args.phase == InputPhase::Ended)
	{
		DHeld = false;
	}

}

void PlayerShipController::OnSpacePressed(InputArgs args)
{
	if (args.phase == InputPhase::Started)
	{
		if (PeaShooter != nullptr) 
		{
			PeaShooter->BulletPrefab = "bulletP";
			PeaShooter->FireGun({ 1,0 }); //Fires right!
			
		}
		SpaceHeld = true;
		GameEssentialsGlobals::EventH.FireEvent("ShootStart");
	}
	else if (args.phase == InputPhase::Ended)
	{
		SpaceHeld = false;
		if (BeamHeldTime > TimeForLargeBeam && PeaShooter != nullptr)
		{
			PeaShooter->BulletPrefab = "bulletL";
			PeaShooter->FireGun({ 1,0 });
			PeaShooter->BulletPrefab = "bulletP";
		}
		else if (BeamHeldTime > TimeForMediumBeam && PeaShooter != nullptr)
		{
			PeaShooter->BulletPrefab = "bulletM";
			PeaShooter->FireGun({ 1,0 });
			PeaShooter->BulletPrefab = "bulletP";
		}

		
		BeamHeldTime = 0;
		GameEssentialsGlobals::EventH.FireEvent("ShootEnd");
	
		
	}

}



void PlayerShipController::OnAlive()
{
	//std::cout << "StartedComp!!--------------------------";
	Component::OnAlive();
	std::cout << "StartedComp!!--------------------------";



	std::function<void(InputArgs IA)> OnWPressedfn = [this](InputArgs IA)
		{
			this->OnWPressed(IA);
		};
	std::function<void(InputArgs IA)> OnAPressedfn = [this](InputArgs IA)
		{
			this->OnAPressed(IA);
		};

	std::function<void(InputArgs IA)> OnSPressedfn = [this](InputArgs IA)
		{
			this->OnSPressed(IA);
		};
	std::function<void(InputArgs IA)> OnDPressedfn = [this](InputArgs IA)
		{
			this->OnDPressed(IA);
		};

	std::function<void(InputArgs IA)> OnSpacePressedfn = [this](InputArgs IA)
		{
			this->OnSpacePressed(IA);
		};

	this->bindEvent(sf::Keyboard::Key::W, OnWPressedfn);
	this->bindEvent(sf::Keyboard::Key::A, OnAPressedfn);
	this->bindEvent(sf::Keyboard::Key::D, OnDPressedfn);
	this->bindEvent(sf::Keyboard::Key::S, OnSPressedfn);
	this->bindEvent(sf::Keyboard::Key::Space, OnSpacePressedfn);

	//GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::W, OnWPressedfn);
	//GameEssentialsGlobals::InputEventH.BindEvent(sf::Keyboard::Key::D, OnWPressedfn2);
	//GameEssentialsGlobals::InputEventH.UnBindEvent(sf::Keyboard::Key::W, Event);
}
