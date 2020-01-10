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
	eSwitchColoredHits
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
	std::string _coloredHits;
	void btnRunBox();
	void btnExit();
	void btnResetBox();
	void btnMoreWoosh();
	void btnLessWoosh();
	void btnMoreGravity();
	void btnLessGravity();
	void btnSwitchColoredHits();

	void checkButtons();
public:
	StateMenu(EnvVariables& vars);
	void Update(float dt);
};

