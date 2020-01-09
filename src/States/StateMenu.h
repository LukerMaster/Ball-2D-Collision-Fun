#pragma once
#include "State.h"
#include "../Box.h"
#include "../Button.h"
#include "../ButtonFunctions.h"
#include "TransitionAnim.h"

class StateMenu :
	public State
{
private:
	Box _animation;
	std::vector<Button> _buttons;
	sf::Text _name;
	sf::Text _author;
	std::vector<sf::Text> _options;
public:
	StateMenu(EnvVariables& vars);
	void Update(float dt);
};

