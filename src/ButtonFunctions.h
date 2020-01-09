#pragma once
#include "EnvVariables.h"

struct ButtonFunctions
{
	static void runBox(EnvVariables& vars);
	static void exit(EnvVariables& vars);
	static void resetBox(EnvVariables& vars);
	static void moreWoosh(EnvVariables& vars);
	static void lessWoosh(EnvVariables& vars);
	static void moreGravity(EnvVariables& vars);
	static void lessGravity(EnvVariables& vars);
};



