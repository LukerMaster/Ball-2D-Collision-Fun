#pragma once
#include <vector>
#include <random>
#include <numeric>
#include <cmath>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Ball.h"

#include <iostream>

class Box
{
private:
	sf::Texture _texture;
	int _selected;
	int _hovered;
	sf::SoundBuffer _hitSound;
protected:
	float _DotProduct(sf::Vector2f v1, sf::Vector2f v2);
public:
	Box();
	Box(std::vector<Ball> ballVec, sf::Vector2f boxSize, float wall_stiffness = 0.9f, float gravity_mult = 1.0f, sf::Color bg_color = {40, 40, 40}, std::string path_to_hitsound = ""); // No wall collision if stiffness = -1.0f
	std::vector<Ball> balls;
	sf::Vector2f size;
	float wallStiffness; // If ball bounces off the wall, its speed is multiplied by this.
	float gravity;
	sf::Color bgColor;
	bool coloredHits;
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	float GetDistance(sf::Vector2f point1, sf::Vector2f point2);
	float GetSDistance(sf::Vector2f point1, sf::Vector2f point2); // If calulates 0, returns 1.
	sf::Vector2f GetVector(sf::Vector2f from, sf::Vector2f to);
	sf::Vector2f GetExperimentalVector(sf::Vector2f from, sf::Vector2f to); // Never returns 0 in x or y. Unused.
	bool DoBallsOverlap(Ball& b1, Ball&  b2);
	void StaticContain(Ball& ball); // Containing inside box.
	void DynamicContain(Ball& ball); // Calculating bounces off walls.

	int GetBallByPos(sf::Vector2i pos); // Returns -1 if not found.

	void StaticCollision(Ball& b1, Ball& b2);
	void DynamicCollision(Ball& b1, Ball& b2);
	void PullByGravity(Ball& b1);


	void UpdateGravity(float multiplier);
	void UpdateStiffness(float multiplier);

	void AddWoosh(sf::Vector2f direction); // Adds some woosh to woosh all the balls.
	void AddBall(Ball ball);

	bool isAnyBallSelected();
	void SelectBallUnder(sf::Vector2i pos);

	void DrawHoveredInfo(sf::Vector2i mouse_pos ,sf::RenderWindow& window, sf::Font& font);
	sf::Vector2f GetPosOfSelected();
	void AddForceToSelected(sf::Vector2f force, bool timesMass = false);
	void DeselectBall();

	int GetBallCount();
};

