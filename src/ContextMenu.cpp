#include "ContextMenu.h"

ContextMenu::ContextMenu(EnvVariables& vars, std::vector<Button> buttons, sf::Color bg_color, sf::Text label)
	:_vars(vars),
	_buttons(buttons),
	_baseColor(bg_color),
	_label(label),
	_percentage(0.0f)
{
	float width = 0.0f, height = 0.0f;
	for (int i = 0; i < _buttons.size(); i++)
	{
		
	}
	_size.x = width;
	_size.y = height;
}

bool ContextMenu::isOpen()
{
	return _opened;
}

bool ContextMenu::isHovered()
{
	if (Addons::point_in_rect(_vars.inputs.mouse_pos, GetSprite().getGlobalBounds()))
		return true;
	else
		return false;
}

sf::Sprite ContextMenu::GetSprite()
{
	sf::Sprite spr(_texture);
	spr.setPosition(sf::Vector2f(_position));
	return spr;
}

ContextMenu::ContextMenu(EnvVariables& vars)
	:_vars(vars)
{
}

void ContextMenu::Update(float dt)
{
	if (_opened)
	{
		
		sf::RenderTexture temp;
		temp.create(_size.x, _size.y);
		temp.clear(sf::Color::Transparent);

		sf::RectangleShape outline;
		outline.setFillColor({ 0, 0, 0, 0 });
		outline.setOutlineColor({ 255, 255, 255, 255 });
		outline.setOutlineThickness(1);
		outline.setSize({ _size.x - 2.0f, _size.y - 2.0f });
		outline.setPosition({ 1, 1 });
		temp.draw(outline);

		std::cout << _percentage << std::endl;
		if (_percentage < 1.0f)
		{
			for (int i = 0; i < _buttons.size(); i++)
			{
			}
		}
		else
		{
			for (int i = 0; i < _buttons.size(); i++)
			{
			}
		}
		_percentage += 0.001f * _speed * dt;
		if (_percentage >= 1.0f)
			_percentage = 1.0f;
		temp.display();
		_texture = temp.getTexture();
	}
	for(int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i].Update(dt);
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
