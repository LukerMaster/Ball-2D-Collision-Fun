#include "Arrow.h"

sf::Vector2f Arrow::_GetVector(sf::Vector2f from, sf::Vector2f to)
{
	return sf::Vector2f(to.x - from.x, to.y - from.y);
}

sf::Vector2f Arrow::_RotateVector(sf::Vector2f vec, float degrees)
{
	sf::Vector2f newVec;
	float rads = (degrees * 3.14159265359f) / 180;
	newVec.x = (cos(rads) * vec.x) - (sin(rads) * vec.y);
	newVec.y = (sin(rads) * vec.x) + (cos(rads) * vec.y);
	return newVec;
}

Arrow::Arrow(sf::Color arrowColor, sf::Color borderColor, float BorderThiccness)
	:baseColor(arrowColor),
	outlineColor(borderColor),
	outlineThiccness(BorderThiccness)
{
	_arrowShape.setPointCount(3);
}

void Arrow::Draw(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f point)
{
	_arrowShape.setPoint(2, point);
	sf::Vector2f offset = _GetVector(start, point);
	offset = _RotateVector(offset, 90) * 0.02f;
	_arrowShape.setPoint(0, start + offset);
	_arrowShape.setPoint(1, start - offset);
	_arrowShape.setFillColor(baseColor);
	_arrowShape.setOutlineThickness(outlineThiccness);
	_arrowShape.setOutlineColor(outlineColor);
	

	window.draw(_arrowShape);
}
