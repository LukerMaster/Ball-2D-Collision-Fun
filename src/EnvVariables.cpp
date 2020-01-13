#include "EnvVariables.h"
#include <iostream>

EnvVariables::EnvVariables()
	:window(sf::VideoMode(600, 600), "Kulki-Turlu-Turlu", sf::Style::Titlebar | sf::Style::Close)
{
	options.coloredHits = false;
	options.isOpen = true;
	options.wooshPower = 100;
	options.gravityScale = 1.0f;
	options.wallStiffness = 85;

	inputs.down = false;
	inputs.up = false;
	inputs.left = false;
	inputs.right = false;
	inputs.ret = false;
	inputs.esc = false;

	transition = false;

	assets.menuSelect.loadFromFile("assets/mnsl.mlg");
	assets.menuClick.loadFromFile("assets/mnst.mlg");
	assets.font.loadFromFile("assets/rb.mlg");
	assets.icon.loadFromFile("assets/ng.mlg");
	curState = eStates::stMenu;

	window.setIcon(256, 256, assets.icon.getPixelsPtr());

}

void Inputs::checkKeyPresses()
{
	sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? right = true : right = false;
	sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? left = true : left = false;
	sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? up = true : up = false;
	sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? down = true : down = false;
	sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ? ret = true : ret = false;
	sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ? esc = true : esc = false;


}

void Inputs::checkMousePos(sf::Window& win)
{
	mouse_pos = sf::Mouse::getPosition(win);
}
