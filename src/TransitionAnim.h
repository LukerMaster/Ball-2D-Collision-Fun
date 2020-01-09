#pragma once
#include "SFML/Graphics.hpp"
#include "Box.h"

#include <iostream>

class TransitionAnim
{
protected:
	sf::Texture _texture;
	Box _box;
	float _percentage;
	float _ReverseLerp(float start, float end, float value);
public:
	TransitionAnim();
	float GetPercentage();
	void Reset();
	void Progress(sf::Vector2i size, float dt, sf::RenderWindow& window, float speed = 1.0f);
};

