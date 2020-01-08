#pragma once
#include "EnvVariables.h"
#include "SFML/Graphics.hpp"

#include <iostream>

class Addons
{
public:
	static float dot_product(sf::Vector2f v1, sf::Vector2f v2);
	static bool point_in_rect(sf::Vector2i pt, sf::RectangleShape rect);
	static bool point_in_rect(sf::Vector2i pt, sf::FloatRect rect);
	static sf::Color shift_color(const sf::Color& current, sf::Color target, int speed = 1);
	static float reverse_lerp(float start, float end, float value);
	static sf::Color hsv(int hue, float sat, float val);
};