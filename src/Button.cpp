#include "Button.h"

Button::Button(EnvVariables& vars, void (*function)(EnvVariables& vars), std::string text, std::string description, sf::Vector2f pos, sf::Vector2f size)
	:_vars(vars)
{
	hitBox.setSize(size);
	hitBox.setPosition(pos);

	label.setString(text);
	label.setPosition(pos);
	label.setFont(_vars.assets.font);
	label.setCharacterSize(size.y * 0.8f);

	desc.setString(description);

	SetColors();
	hitBox.setFillColor(baseColor);

	func = function;
	_prevMousePressed = false;
	_prevHovered = false;

	_hoverSound.setBuffer(_vars.assets.menuSelect);
	_pressSound.setBuffer(_vars.assets.menuClick);
}

void Button::Update(float dt)
{
	if (Addons::point_in_rect(_vars.inputs.mouse_pos, hitBox))
	{
		if (!_prevHovered)
			_hoverSound.play();
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && _prevMousePressed)
		{
			_pressSound.play();
			(*func)(_vars);
		}
			
		hitBox.setFillColor(Addons::shift_color(hitBox.getFillColor(), hlColor, 9));
		label.setFillColor(Addons::shift_color(label.getFillColor(), hlTextColor, 4));
		
		_prevHovered = true;
	}
	else
	{
		hitBox.setFillColor(Addons::shift_color(hitBox.getFillColor(), baseColor, 3));
		label.setFillColor(Addons::shift_color(label.getFillColor(), baseTextColor, 6));
		_prevHovered = false;
	}
	Addons::point_in_rect(_vars.inputs.mouse_pos, hitBox) ? _prevHovered = true : _prevHovered = false;
	sf::Mouse::isButtonPressed(sf::Mouse::Left) ? _prevMousePressed = true : _prevMousePressed = false;
}

void Button::SetColors(sf::Color hlButton, sf::Color hlText, sf::Color button, sf::Color text) // 
{
	baseColor = button;
	baseTextColor = text;
	hlColor = hlButton;
	hlTextColor = hlText;
}

void Button::SetFunction(void(*function)(EnvVariables&))
{
	func = function;
}

void Button::Draw()
{
	_vars.window.draw(hitBox);
	_vars.window.draw(label);
}
