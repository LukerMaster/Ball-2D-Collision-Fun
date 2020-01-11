#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>

class Ball
{
private:
	float _radius;
	float _mass;

	sf::Vector2f _pos; // position is based on this. Not sprite position.
	sf::Vector2f _vel; // Velocity
	sf::Vector2f _acc; // Acceleration
	sf::CircleShape _shape;
	sf::Color _baseColor; // If ball changes color, update method brings it back to this.
	sf::Color _GetShiftedColor(const sf::Color& current, sf::Color target, int speed);

public:

	Ball(int id, sf::Vector2f position = { 10, 10 }, float radius = 5, float mass = 1000, sf::Color = { 200, 200, 200 }, sf::Vector2f starting_vel = {0, 0}); // Materials: "wood", "stone", "paper"
	sf::Sound hitSound;
	float GetRadius();
	float GetMass();

	int id; // Unused
	const sf::Vector2f& GetForce();
	const sf::Vector2f& GetPosition();
	const sf::Vector2f& GetVelocity();
	const sf::Vector2f& GetAcceleration();
	const sf::CircleShape& GetShape();
	const sf::Color& GetBaseColor();

	void move(sf::Vector2f amount);
	void moveTo(sf::Vector2f pos);

	void AddForce(sf::Vector2f force);
	void AddVelocity(sf::Vector2f velocity);
	void SetVelocity(sf::Vector2f velocity);
	void SetColor(sf::Color color);


	void Update(float dt);

	bool IsPointInside(sf::Vector2f point);
};

