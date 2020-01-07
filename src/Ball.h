#pragma once
#include "SFML/Graphics.hpp"

#include <iostream>

enum eMaterial
{
	Paper, // Mass x0.01
	Plastic, // Mass x0.1
	Wood, // Mass x1
	Stone, // Mass x10
	Lead // Mass x100
};

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

	eMaterial _material;

	int _id; // Unused
public:
	Ball(int id, sf::Vector2f position = {10, 10}, float radius = 5, eMaterial mat = Wood, float massMult = 1000); // Materials: "wood", "stone", "paper"
	float GetRadius();
	float GetMass();

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

