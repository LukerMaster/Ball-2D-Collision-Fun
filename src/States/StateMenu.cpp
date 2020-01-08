#include "StateMenu.h"

StateMenu::StateMenu(EnvVariables& vars)
	:State(vars)
{
	std::vector<Ball> ballVec;

	for (int i = 0; i < 8; i++)
	{
		ballVec.push_back(Ball(i,
			sf::Vector2f((i % 3) * 140 + rand()%20 + 200, rand()%120 + 300),
			40,
			20000,
			sf::Color(rand() % 30 + 50, rand() % 30 + 50, rand() % 30 + 50),
			sf::Vector2f(rand()%10 * 0.00001f, rand() % 10 * 0.00001f)));
	}

	// Start button
	_buttons.push_back(Button(_vars, "Open the box.", "Opens the box with balls and let's you start playing."));
	_buttons[0].func = ButtonFunctions::runBox;

	// Exit button
	_buttons.push_back(Button(_vars, "Exit.", "Quits this epic project.", {10, 550}));
	_buttons[1].SetColors({ 0, 255, 50 });
	_buttons[1].func = ButtonFunctions::exit;

	// Main text in menu.
	_name.setString("Balls2D");
	_name.setCharacterSize(90);
	_name.setPosition(300, 20);
	_name.setFont(_vars.assets.font);

	// Create animation
	_animation = Box(ballVec, { 600, 600 }, 1.0f, 0.0f, { 30, 30, 30 });
}

void StateMenu::Update(float dt)
{
	_animation.Update(dt);
	_vars.window.draw(_animation.GetSprite());
	for (int i = 0; i < _buttons.size(); i++)
	{
		_vars.window.draw(_buttons[i].GetSprite());
		_buttons[i].Update(sf::Mouse::getPosition(_vars.window));
	}
	_vars.window.draw(_name);
}
