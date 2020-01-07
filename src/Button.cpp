#include "Button.h"

Button::Button(EnvVariables& vars, std::string text, std::string description, sf::Vector2f pos, sf::Vector2f size)
	:position(pos),
	_vars(vars)
{
	hitBox.setSize(size);
	label.setString(text);
	label.setFont(_vars.assets.font);
	label.setCharacterSize(30);
	label.setPosition(5, 0);
	desc.setString(description);
	hitBox.setFillColor(baseColor);
	SetColors();
	func = ButtonFunctions::exit;
	_mousePressed = false;
}

void Button::Update(sf::Vector2i cursor_pos)
{
	sf::RectangleShape temp = hitBox;
	temp.move(position);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		_mousePressed = true;
	else
	{
		if (Addons::point_in_rect(cursor_pos, temp))
		{
			hitBox.setFillColor(Addons::shift_color(hitBox.getFillColor(), hlColor, 2));
			label.setFillColor(Addons::shift_color(label.getFillColor(), hlTextColor, 4));
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _mousePressed)
				(*func)(_vars);
		}
		else
		{
			hitBox.setFillColor(Addons::shift_color(hitBox.getFillColor(), baseColor, 2));
			label.setFillColor(Addons::shift_color(label.getFillColor(), baseTextColor, 4));
			hitBox.setFillColor(baseColor);
		}
		_mousePressed = false;
	}
	
}

void Button::SetColors(sf::Color hlButton, sf::Color hlText, sf::Color button, sf::Color text) // 
{
	baseColor = button;
	baseTextColor = text;
	hlColor = hlButton;
	hlTextColor = hlText;
}

sf::Sprite Button::GetSprite()
{
	sf::RenderTexture renTex;
	renTex.create(hitBox.getSize().x, hitBox.getSize().y);
	renTex.draw(hitBox);
	renTex.draw(label);
	renTex.display();
	_drawTexture = renTex.getTexture();
	sf::Sprite btSprite = sf::Sprite(_drawTexture);
	btSprite.move(position);
	return btSprite;
}
