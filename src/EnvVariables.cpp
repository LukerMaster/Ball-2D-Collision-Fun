#include "EnvVariables.h"
#include <iostream>

EnvVariables::EnvVariables()
	:window(sf::VideoMode(600, 600), "Kulki-Turlu-Turlu")
{
	options.coloredHits = false;
	options.isOpen = true;
	options.wooshPower = 0.02f;

	inputs.down = false;
	inputs.up = false;
	inputs.left = false;
	inputs.right = false;
	inputs.ret = false;
	inputs.esc = false;

	curState = eStates::stMenu;
}

void Inputs::checkKeyPresses()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		right = true;
	else
		right = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		left = true;
	else
		left = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		up = true;
	else
		up = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		down = true;
	else
		down = false;
}
