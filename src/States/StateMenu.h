#pragma once
#include "State.h"
#include "../Box.h"
#include "../Button.h"

enum btnFuncs
{
	eExit,
	eRunMenu,
	eRunBox,
	eResetBox,
	eLessWoosh,
	eMoreWoosh,
	eLessGravity,
	eMoreGravity,
};

class StateMenu :
	public State
{
protected:
	Box _animation;
	std::vector<Button> _buttons;
	sf::Text _name;
	sf::Text _author;
	std::vector<sf::Text> _options;
	void btnRunBox();
	void btnExit();
	void btnResetBox();
	void btnMoreWoosh();
	void btnLessWoosh();
	void btnMoreGravity();
	void btnLessGravity();

	void checkButtons();
public:
	StateMenu(EnvVariables& vars);
	void Update(float dt);
};

