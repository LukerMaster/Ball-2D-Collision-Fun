#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include <thread>
class ContextMenu
{
private:
	EnvVariables& _vars;
	sf::Text _label;
	std::vector<Button> _buttons;
	sf::Texture _texture;
	sf::Vector2i _position;
	sf::Vector2f _size;

	float _percentage;
	float _speed;
	bool _opened;
	bool _valid;
	sf::Color _baseColor;
public:
	ContextMenu(EnvVariables& vars);
	ContextMenu(EnvVariables& vars, std::vector<Button> buttons, sf::Color bg_color, sf::Text _label);
	bool isOpen();
	bool isHovered();
	sf::Sprite GetSprite();
	void Open(float speed, sf::Vector2i position);
	void Update(float dt);
	void Hide();
};

