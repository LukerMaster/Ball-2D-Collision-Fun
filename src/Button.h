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
	sf::Sound _hoverSound;
	sf::Sound _pressSound;
	bool _prevMousePressed;
	bool _prevHovered;
	void (*func)(EnvVariables& vars); // Function executed at click. Function pointer.
public:
	Button(EnvVariables& vars, void (*function)(EnvVariables& vars), std::string text = "Button", std::string desc = "No description.", sf::Vector2f pos = { 0, 0 }, sf::Vector2f size = { 200, 40 });
	sf::Text label;
	sf::RectangleShape hitBox;
	sf::Text desc; // Description.
	sf::Color baseColor, hlColor;
	sf::Color baseTextColor, hlTextColor;
	void Update(float dt);
	void SetColors(sf::Color hlButton = { 255, 100, 40 }, sf::Color hlText = { 0, 0, 0 }, sf::Color button = { 0, 0, 0, 0 }, sf::Color text = {255, 255, 255});
	void SetFunction(void (*function)(EnvVariables&));
	void Draw();
};

