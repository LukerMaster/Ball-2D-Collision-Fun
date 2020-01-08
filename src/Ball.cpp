#include "Ball.h"

Ball::Ball(int Id, sf::Vector2f position, float radius, float mass, sf::Color custom_color, sf::Vector2f starting_vel)
	: _pos(position),
	_mass(mass),
	_radius(radius),
	id(Id),
	_baseColor(custom_color)
{
	_vel = { starting_vel.x, starting_vel.y };
	_acc = { 0, 0 };
	if (_radius > 150)
		_shape = sf::CircleShape(_radius, 50);
	else
		_shape = sf::CircleShape(_radius, 30);

	_shape.setFillColor(_baseColor);
	_shape.setOrigin({ radius, radius });
	_shape.setPosition(_pos.x, _pos.y);
}

float Ball::GetRadius()
{
	return _radius;
}

const sf::Vector2f& Ball::GetForce()
{
	return sf::Vector2f(_acc.x * _mass, _acc.y * _mass);
}

const sf::Vector2f& Ball::GetPosition()
{
	return _pos;
}

float Ball::GetMass()
{
	return _mass;
}

const sf::Vector2f& Ball::GetVelocity()
{
	return _vel;
}

const sf::Vector2f& Ball::GetAcceleration()
{
	return _acc;
}

const sf::CircleShape& Ball::GetShape()
{
	return _shape;
}

const sf::Color& Ball::GetBaseColor()
{
	return _baseColor;
}


void Ball::move(sf::Vector2f amount)
{
	_pos.x += amount.x;
	_pos.y += amount.y;
	_shape.setPosition(_pos);
}

void Ball::moveTo(sf::Vector2f pos)
{
	_pos.x = pos.x;
	_pos.y = pos.y;
	_shape.setPosition(_pos);
}

void Ball::AddForce(sf::Vector2f force)
{
	_acc.x += force.x / _mass;
	_acc.y += force.y / _mass;
}

void Ball::AddVelocity(sf::Vector2f velocity)
{
	_vel.x += velocity.x;
	_vel.y += velocity.y;
}

void Ball::SetVelocity(sf::Vector2f velocity)
{
	_vel.x = velocity.x;
	_vel.y = velocity.y;
}

void Ball::SetColor(sf::Color color)
{
	_shape.setFillColor(color);
}

void Ball::Update(float dt)
{
	_vel += _acc;
	_pos += _vel * dt;
	_shape.setPosition(_pos);
	_acc -= -_acc * 0.8f;
	if (fabs(_acc.x) > 0.00002f) _acc.x = 0;
	if (fabs(_acc.y) > 0.00002f) _acc.y = 0;

	if (_shape.getFillColor().r > _baseColor.r) _shape.setFillColor(sf::Color(_shape.getFillColor().r - 1, _shape.getFillColor().g, _shape.getFillColor().b));
	if (_shape.getFillColor().r < _baseColor.r) _shape.setFillColor(sf::Color(_shape.getFillColor().r + 1, _shape.getFillColor().g, _shape.getFillColor().b));
	if (_shape.getFillColor().g > _baseColor.g) _shape.setFillColor(sf::Color(_shape.getFillColor().r, _shape.getFillColor().g - 1, _shape.getFillColor().b));
	if (_shape.getFillColor().g < _baseColor.g) _shape.setFillColor(sf::Color(_shape.getFillColor().r, _shape.getFillColor().g + 1, _shape.getFillColor().b));
	if (_shape.getFillColor().b > _baseColor.b) _shape.setFillColor(sf::Color(_shape.getFillColor().r, _shape.getFillColor().g, _shape.getFillColor().b - 1));
	if (_shape.getFillColor().b < _baseColor.b) _shape.setFillColor(sf::Color(_shape.getFillColor().r, _shape.getFillColor().g, _shape.getFillColor().b + 1));

}

bool Ball::IsPointInside(sf::Vector2f point)
{
	if (sqrt(((point.x - _pos.x) * (point.x - _pos.x)) + ((point.y - _pos.y) * (point.y - _pos.y))) < _radius)
		return true;
	else
		return false;
}
