#pragma once
#include "SFML/Graphics.hpp"
#include "../EnvVariables.h"

class State
{
protected:
	EnvVariables& _vars;
public:
	State(EnvVariables& vars);
	virtual void Update(float dt) = 0;
};

