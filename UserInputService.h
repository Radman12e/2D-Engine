
#include "PlayerController.h"
#include <iostream>


#pragma once
class UserInputService
{
	PlayerController* PlrObject = nullptr;

public:
	UserInputService();

	void SetPlrObject(PlayerController* ga)
	{
		PlrObject = ga;
	}

private:
	void UpInputPressed(InputArgs Ia) 
	{
		
		if (PlrObject != nullptr) 
		{
			
			PlrObject->OnUpInput(Ia);
		}
	}
	void DownInputPressed(InputArgs Ia)
	{
		if (PlrObject != nullptr)
		{
			PlrObject->OnDownInput(Ia);
		}

	}
	void LeftInputPressed(InputArgs Ia)
	{
		if (PlrObject != nullptr)
		{
			PlrObject->OnLeftInput(Ia);
		}

	}
	void RightInputPressed(InputArgs Ia)
	{
		if (PlrObject != nullptr)
		{
			PlrObject->OnRightInput(Ia);
		}

	}
	void Button1(InputArgs Ia)
	{
		if (PlrObject != nullptr)
		{
			PlrObject->OnButton1(Ia);
		}

	}
	void Button2(InputArgs Ia)
	{
		if (PlrObject != nullptr)
		{
			PlrObject->OnButton2(Ia);
		}

	}
};

