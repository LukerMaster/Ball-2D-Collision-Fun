#pragma once
#include "State.h"
#include "../Button.h"
#include "../ButtonFunctions.h"

class StateMenu :
	public State
{
private:
	std::vector<Button> buttons;
public:
	StateMenu(EnvVariables& vars);
	void Update(float dt);
};

