#pragma once
#include <SFML/Graphics.hpp>



class Component
{
public:

	Component()
	{
	}
	Component(bool enabled) 
	{
		this->Enabled = enabled;
	}

	virtual void OnUpdate(float deltaTime) 
	{
		if (!this->Enabled) 
		{
			return;
		}
	}
	
	virtual void OnDestroy() 
	{
		if (!this->Enabled)
		{
			return;
		}
	}

	virtual void OnStart()
	{
		if (!this->Enabled)
		{
			return;
		}
	}

	virtual void OnAlive()

	{
		if (!this->Enabled)
		{
			return;
		}
	}

	bool Enabled = true;
};

