#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include <thread>
class ContextMenu
{
private:
	sf::Text _label;
	std::vector<Button> _buttons;
	sf::Texture _texture;
	sf::Vector2i _position;
	float _percentage;
	float _speed;
	bool _opened;
	bool _valid;
	sf::Color _baseColor;
public:
	ContextMenu();
	ContextMenu(std::vector<Button> buttons, sf::Color bg_color, sf::Text _label);
	bool isOpen();
	sf::Sprite Show();
	void Open(float speed, sf::Vector2i position);
	void Update(float dt);
	void Hide();
};

