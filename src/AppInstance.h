#pragma once
#include "SFML/Graphics.hpp"
#include "States/State.h"
#include "States/StateBox.h"
#include "EnvVariables.h"

struct AppInstance
{
	EnvVariables _vars;
public:
	AppInstance();

	EnvVariables& vars();
	std::vector<State*> states;
};

