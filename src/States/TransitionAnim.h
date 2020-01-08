#pragma once
#include "SFML/Graphics.hpp"
#include "../EnvVariables.h"
#include "../Addons.h"
#include "../Box.h"

#include <iostream>

class TransitionAnim
{
	EnvVariables& _vars;
	sf::Texture _texture;
	Box _box;
	float percentage;
public:
	TransitionAnim(EnvVariables& vars);
	void Play(sf::Vector2i size, float speed = 1.0f);
};

