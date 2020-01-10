#pragma once
#include "State.h"
#include "../Arrow.h"
#include "../Box.h"

#include <iostream>

class StateBox :
	public State
{
protected:
	sf::Text _fps;
	Box _box;
	bool _prevClicked;
	sf::Vector2f _dragEnd;
	sf::Vector2f _GetVector(sf::Vector2f from, sf::Vector2f to);
	float _GetDistance(sf::Vector2f point1, sf::Vector2f point2);
	sf::Color _getHSVColor(int hue, float sat, float val);
public:
	StateBox(EnvVariables& vars);
	void Update(float dt);
	void CreateBox();
};

