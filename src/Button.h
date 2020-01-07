#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>

#include "ButtonFunctions.h"
#include "Addons.h"

class Button
{
private:
	sf::Texture _drawTexture;
	EnvVariables& _vars;
	bool _mousePressed;
public:
	Button(EnvVariables& vars, std::string text = "Button", std::string desc = "No description.", sf::Vector2f pos = { 10, 10 }, sf::Vector2f size = { 180, 40 });
	sf::Text label;
	sf::RectangleShape hitBox;
	sf::Text desc; // Description.
	sf::Color baseColor, hlColor;
	sf::Color baseTextColor, hlTextColor;
	sf::Vector2f position; // Sprite position must be (0, 0) to draw on small dedicated texture so this position is used for placing on bigger surface.
	void (*func)(EnvVariables& vars); // Function executed at click
	void Update(sf::Vector2i cursor_pos); // Returns true if clicked.
	void SetColors(sf::Color hlButton = { 255, 100, 40 }, sf::Color hlText = { 0, 0, 0 }, sf::Color button = { 30, 30, 30 }, sf::Color text = {255, 255, 255});
	sf::Sprite GetSprite();
};

