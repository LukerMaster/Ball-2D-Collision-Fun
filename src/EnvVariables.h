#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "eStates.h"

struct Assets
{
	sf::Font font;
	sf::SoundBuffer menuSelect;
	sf::SoundBuffer menuClick;
};

struct Options
{
	bool isOpen; // Is the game open. 0 means exit.

	bool coloredHits; // Are balls colored red on collision.
	float wooshPower; // How powerful wooshes are. See Box::AddWoosh()
};

struct Inputs
{
	bool up;
	bool down;
	bool left;
	bool right;
	bool ret; // Return, or Enter.
	bool esc;
public:
	void checkKeyPresses();
};


struct EnvVariables
{
	unsigned short frame; // For doing stuff periodically. for example if (frame % 3) ... .
	float dt;
	float real_dt; // DO NOT EVER USE FOR ANYTHING EXCEPT DISPLAYING. For pchysics, check float dt;
	Inputs inputs;
	Options options;
	Assets assets;
	sf::RenderWindow window;
	eStates curState;
	eStates nextState;
	bool transition;
public:
	EnvVariables();
};

