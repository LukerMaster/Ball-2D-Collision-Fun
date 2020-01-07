#include "Addons.h"

float Addons::dot_product(sf::Vector2f v1, sf::Vector2f v2)
{
		return (v1.x * v2.x) + (v1.y * v2.y);
}

bool Addons::point_in_rect(sf::Vector2i pt, sf::RectangleShape rect)
{
	if (pt.x > rect.getPosition().x&& pt.x < rect.getPosition().x + rect.getSize().x
		&& pt.y > rect.getPosition().y&& pt.y < rect.getPosition().y + rect.getSize().y)
		return true;
	else
		return false;
}

sf::Color Addons::shift_color(const sf::Color& current, sf::Color target, int speed)
{
	sf::Color returned = current; // This is because sf::getFillColor() only returns const&.

	if (abs(returned.r - target.r) < speed) returned.r = target.r;
	if (abs(returned.g - target.g) < speed) returned.g = target.g;
	if (abs(returned.b - target.b) < speed) returned.b = target.b;

	if (returned.r > target.r) returned.r -= speed;
	if (returned.r < target.r) returned.r += speed;

	if (returned.g > target.g) returned.g -= speed;
	if (returned.g < target.g) returned.g += speed;

	if (returned.b > target.b) returned.b -= speed;
	if (returned.b < target.b) returned.b += speed;
	return returned;
}

