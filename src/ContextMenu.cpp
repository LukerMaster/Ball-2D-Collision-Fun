#include "ContextMenu.h"

ContextMenu::ContextMenu(std::vector<Button> buttons, sf::Color bg_color, sf::Text label)
	:_buttons(buttons),
	_baseColor(bg_color),
	_label(label),
	_percentage(0.0f)
{
	
}

bool ContextMenu::isOpen()
{
	return _opened;
}

sf::Sprite ContextMenu::Show()
{
	sf::Sprite spr(_texture);
	spr.setPosition(sf::Vector2f(_position));
	return spr;
}

ContextMenu::ContextMenu()
{
}

void ContextMenu::Update(float dt)
{
	if (_opened)
	{
		float width = 0.0f, height = 0.0f;
		for (int i = 0; i < _buttons.size(); i++)
		{
			height += _buttons[i].GetSprite().getTexture()->getSize().y;
			if (_buttons[i].GetSprite().getTexture()->getSize().x > width)
				width = _buttons[i].GetSprite().getTexture()->getSize().x;
			_buttons[i].position = { 0, height };
		}
		sf::RenderTexture temp;
		temp.create(width, height);
		temp.clear(sf::Color::Transparent);
		std::cout << _percentage << std::endl;
		if (_percentage < 1.0f)
		{
			for (int i = 0; i < _buttons.size(); i++)
			{
				sf::Sprite btnSpr = sf::Sprite(_buttons[i].GetSprite());
				btnSpr.setColor(btnSpr.getColor() * sf::Color(255, 255, 255, 255 * _percentage));
				temp.draw(btnSpr);
			}
		}
		else
		{
			for (int i = 0; i < _buttons.size(); i++)
			{
				std::cout << "doot" << std::endl;
				temp.draw(_buttons[i].GetSprite());
			}
		}
		_percentage += 0.0001f * _speed * dt;
		if (_percentage >= 1.0f)
			_percentage = 1.0f;
		_texture = temp.getTexture();
	}
	for(int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i].Update(dt, sf::Vector2f(_position));
	}
}

void ContextMenu::Open(float speed, sf::Vector2i position)
{
	_opened = true;
	_percentage = 0.0f;
	_position = position;
	_speed = speed;
}

void ContextMenu::Hide()
{
	_opened = false;
}
