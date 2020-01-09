#pragma once
#include "State.h"
#include "../Box.h"
#include "../ContextMenu.h"

#include <iostream>

class StateBox :
	public State
{
	sf::Text _fps;
	Box _box;
	bool _prevClicked;
	ContextMenu _menu;
	sf::Vector2f _dragEnd;
public:
	StateBox(EnvVariables& vars);
	void Update(float dt);
	void CreateBox();
};

