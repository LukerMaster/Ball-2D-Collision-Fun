#include "Button.h"

sf::Color Button::_GetShiftedColor(const sf::Color& current, sf::Color target, int speed)
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

bool Button::_IsPointInRect(sf::Vector2i pt, sf::RectangleShape rect)
{
	if (pt.x > rect.getPosition().x&& pt.x < rect.getPosition().x + rect.getSize().x
		&& pt.y > rect.getPosition().y&& pt.y < rect.getPosition().y + rect.getSize().y)
		return true;
	else
		return false;
}


//
//
//
// User functions below
//
//
//


Button::Button(unsigned int Id, sf::Vector2f pos, sf::Vector2f size, std::string text, sf::Font& font, sf::SoundBuffer& HoverSound, sf::SoundBuffer& ClickSound, std::string description)
	:funcID(Id)
{
	_clicked = false;

	hitBox.setSize(size);
	hitBox.setPosition(pos);

	label.setString(text);
	label.setPosition(pos);
	label.setFont(font);
	label.setCharacterSize(size.y * 0.8f);

	desc.setString(description);

	SetColors();
	hitBox.setFillColor(baseColor);

	_prevMousePressed = false;
	_prevHovered = false;

	hoverSound.setBuffer(HoverSound);
	clickSound.setBuffer(ClickSound);
}

void Button::Update(float dt, sf::Vector2i mouse_pos)
{
	if (_IsPointInRect(mouse_pos, hitBox))
	{
		if (!_prevHovered)
			hoverSound.play();
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && _prevMousePressed)
		{
			clickSound.play();
			_clicked = true;
		}
		hitBox.setFillColor(_GetShiftedColor(hitBox.getFillColor(), hlColor, 9));
		label.setFillColor(_GetShiftedColor(label.getFillColor(), hlTextColor, 4));
		
		_prevHovered = true;
	}
	else
	{
		hitBox.setFillColor(_GetShiftedColor(hitBox.getFillColor(), baseColor, 3));
		label.setFillColor(_GetShiftedColor(label.getFillColor(), baseTextColor, 6));
		_prevHovered = false;
	}
	_IsPointInRect(mouse_pos, hitBox) ? _prevHovered = true : _prevHovered = false;
	sf::Mouse::isButtonPressed(sf::Mouse::Left) ? _prevMousePressed = true : _prevMousePressed = false;
}

void Button::SetColors(sf::Color hlButton, sf::Color hlText, sf::Color button, sf::Color text) // 
{
	baseColor = button;
	baseTextColor = text;
	hlColor = hlButton;
	hlTextColor = hlText;
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(hitBox);
	window.draw(label);
}

bool Button::isClicked()
{
	return _clicked;
		
}

void Button::Unclick()
{
	_clicked = false;
}

bool Button::CheckAndUnclick()
{
	if (_clicked)
	{
		_clicked = false;
		return true;
	}
	else
		return false;
}
