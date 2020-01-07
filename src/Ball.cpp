#include "Ball.h"

Ball::Ball(int id, sf::Vector2f position, float radius, eMaterial material, float massMult)
	: _pos(position),
	_mass(massMult),
	_radius(radius),
	_id(id),
	_material(material)
{
	_vel = { 0, 0 };
	_acc = { 0, 0 };
	_shape = sf::CircleShape(_radius, 30);
	switch (material)
	{
	case Paper:
		_baseColor = sf::Color(240, 240, 240);
		_mass *= 0.01f;
		break;
	case Plastic:
		_baseColor = sf::Color(255, 255, 200);
		_mass *= 0.1f;
		break;
	case Wood:
		_baseColor = sf::Color(240, 150, 60);
		break;
	case Stone:
		_baseColor = sf::Color(120, 120, 120);
		_mass *= 10.0f;
		break;
	case Lead:
		_baseColor = sf::Color(50, 50, 100);
		_mass *= 100.0f;
		break;
	default:
		break;
	}
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
