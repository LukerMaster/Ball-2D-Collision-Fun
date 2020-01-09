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

bool Addons::point_in_rect(sf::Vector2i pt, sf::FloatRect rect)
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
	if (abs(returned.a - target.a) < speed) returned.a = target.a;

	if (returned.r > target.r) returned.r -= speed;
	if (returned.r < target.r) returned.r += speed;

	if (returned.g > target.g) returned.g -= speed;
	if (returned.g < target.g) returned.g += speed;

	if (returned.b > target.b) returned.b -= speed;
	if (returned.b < target.b) returned.b += speed;

	if (returned.a > target.a) returned.a -= speed;
	if (returned.a < target.a) returned.a += speed;
	return returned;
}

float Addons::reverse_lerp(float start, float end, float value)
{
	return -(value - start) / (start - end);
}

sf::Color Addons::hsv(int hue, float sat, float val)
{
	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(val * 255, t * 255, p * 255);
	case 1: return sf::Color(q * 255, val * 255, p * 255);
	case 2: return sf::Color(p * 255, val * 255, t * 255);
	case 3: return sf::Color(p * 255, q * 255, val * 255);
	case 4: return sf::Color(t * 255, p * 255, val * 255);
	case 5: return sf::Color(val * 255, p * 255, q * 255);
	}
}

sf::Vector2f Addons::get_vector(sf::Vector2f from, sf::Vector2f to)
{
		return sf::Vector2f(to.x - from.x, to.y - from.y);
}

