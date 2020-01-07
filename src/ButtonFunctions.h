#pragma once
#include "EnvVariables.h"

class ButtonFunctions
{
private:
	EnvVariables& _vars;
public:
	static void runBox(EnvVariables& vars);
	static void exit(EnvVariables& vars);
};

