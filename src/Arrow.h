#pragma once
#include <cmath>
#include <iostream>

#include "SFML/Graphics.hpp"
class Arrow
{
protected:
	sf::ConvexShape _arrowShape;
	sf::Vector2f _GetVector(sf::Vector2f from, sf::Vector2f to);
	sf::Vector2f _RotateVector(sf::Vector2f vec, float degrees);
public:
	sf::Color baseColor;
	sf::Color outlineColor;
	float outlineThiccness;
	Arrow(sf::Color arrowColor = { 255, 255, 255, 0 }, sf::Color borderColor = { 0, 0, 0, 255 }, float BorderThiccness = 1.0f);
	void Draw(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f point);
};

