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
	_prevMousePressed = false;
	_prevHovered = false;
	_hoverSound.setBuffer(_vars.assets.menuSelect);
	_pressSound.setBuffer(_vars.assets.menuClick);
}

void Button::Update(sf::Vector2i cursor_pos)
{
	sf::RectangleShape temp = hitBox;
	temp.move(position);
	
	if (Addons::point_in_rect(cursor_pos, temp))
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
	Addons::point_in_rect(cursor_pos, temp) ? _prevHovered = true : _prevHovered = false;
	sf::Mouse::isButtonPressed(sf::Mouse::Left) ? _prevMousePressed = true : _prevMousePressed = false;
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
