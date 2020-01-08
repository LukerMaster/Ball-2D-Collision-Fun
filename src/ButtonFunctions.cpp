#include "ButtonFunctions.h"

void ButtonFunctions::runBox(EnvVariables& vars)
{
	vars.nextState = eStates::stBox;
	vars.transition = true;
}

void ButtonFunctions::exit(EnvVariables& vars)
{
	vars.options.isOpen = false;
	vars.window.close();
}

void ButtonFunctions::resetBox(EnvVariables& vars)
{
	vars.options.resetBox = true;
}
