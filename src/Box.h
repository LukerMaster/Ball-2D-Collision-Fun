#pragma once
#include <vector>
#include <random>
#include <numeric>
#include <cmath>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Ball.h"
#include "Addons.h"

#include <iostream>

class Box
{
private:
	sf::RenderTexture _texture;
public:
	Box(int ballAmount, sf::Vector2f boxSize, float wall_stiffness = 0.9f);

	std::vector<Ball> balls;
	sf::Vector2f size;
	float wallStiffness; // If ball bounces off the wall, its speed is multiplied by this.

	void Update(float dt);
	sf::RenderTexture& GetTexture();

	float GetDistance(sf::Vector2f point1, sf::Vector2f point2);
	float GetSDistance(sf::Vector2f point1, sf::Vector2f point2); // If calulates 0, returns 1.
	sf::Vector2f GetVector(sf::Vector2f from, sf::Vector2f to);
	sf::Vector2f GetExperimentalVector(sf::Vector2f from, sf::Vector2f to); // Never returns 0 in x or y. Unused.
	bool DoBallsOverlap(Ball& b1, Ball&  b2);
	void ContainInBox(Ball& ball);

	int GetBallByPos(sf::Vector2i pos); // Returns -1 if not found.

	void StaticCollision(Ball& b1, Ball& b2);
	void DynamicCollision(Ball& b1, Ball& b2);
	void PullByGravity(Ball& b1);

	void AddWoosh(sf::Vector2f direction); // Adds some woosh to woosh all the balls.
};

