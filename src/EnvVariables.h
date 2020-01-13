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

struct Options // Program-specific
{
	bool isOpen; // Is the game open. 0 means exit.

	bool coloredHits; // Are balls colored red on collision.
	float gravityScale;
	int wallStiffness;
	int wooshPower; // How powerful wooshes are. See Box::AddWoosh()

	bool resetBox;
	enum ballColor
	{
		white, rainbow
	};
};

struct Inputs
{
	bool up;
	bool down;
	bool left;
	bool right;
	bool ret; // Return, or Enter.
	bool esc;
	
	sf::Vector2i mouse_pos;
public:
	void checkKeyPresses();
	void checkMousePos(sf::Window& win);
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
	EnvVariables(EnvVariables& other);
};

