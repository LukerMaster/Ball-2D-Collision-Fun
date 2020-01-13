#pragma once
#include "State.h"
#include "../Box.h"
#include "../Button.h"

enum btnFuncs
{
	eExit,
	eRunBox,
	eResetBox,
	eLessWoosh,
	eMoreWoosh,
	eLessGravity,
	eMoreGravity,
	eSwitchColoredHits,
	eLessStiffness,
	eMoreStiffness
};

class StateMenu :
	public State
{
protected:
	Box _animation;
	std::vector<Button> _buttons;
	sf::Text _name;
	sf::Text _author;
	sf::Text _controls;
	std::vector<sf::Text> _options;
	std::string _coloredHits;
	void btnRunBox();
	void btnExit();
	void btnResetBox();
	void btnMoreWoosh();
	void btnLessWoosh();
	void btnMoreGravity();
	void btnLessGravity();
	void btnSwitchColoredHits();
	void btnLessStiffness();
	void btnMoreStiffness();

	void checkButtons();
public:
	StateMenu(EnvVariables& vars);
	void Update(float dt);
};

