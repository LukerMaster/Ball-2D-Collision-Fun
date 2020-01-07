#pragma once
#include "State.h"
#include "../Box.h"

#include <iostream>

class StateBox :
	public State
{
	sf::Text _fps;
	Box _box;
public:
	StateBox(EnvVariables& vars);
	void Update(float dt);
};

