#include "ButtonFunctions.h"

void ButtonFunctions::runBox(EnvVariables& vars)
{
	vars.curState = eStates::stBox;
}

void ButtonFunctions::exit(EnvVariables& vars)
{
	vars.options.isOpen = false;
	vars.window.close();
}
