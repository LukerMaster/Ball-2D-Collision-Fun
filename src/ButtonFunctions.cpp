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

void ButtonFunctions::moreWoosh(EnvVariables& vars)
{
	if (vars.options.wooshPower <= 0.995f)
		vars.options.wooshPower += 0.005f;
}

void ButtonFunctions::lessWoosh(EnvVariables& vars)
{
	if (vars.options.wooshPower >= 0.005f)
		vars.options.wooshPower -= 0.005f;
}

void ButtonFunctions::moreGravity(EnvVariables& vars)
{
	if (vars.options.gravityScale <= 4.75f)
		vars.options.gravityScale += 0.25f;
}

void ButtonFunctions::lessGravity(EnvVariables& vars)
{
	if (vars.options.gravityScale >= -0.75f)
		vars.options.gravityScale -= 0.25f;
}
