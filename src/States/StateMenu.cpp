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
	_buttons.push_back(Button(_vars, ButtonFunctions::runBox, "Open the box.", "Opens the box with balls and let's you start playing.", { 10, 10 }));
	// Exit button
	_buttons.push_back(Button(_vars, ButtonFunctions::exit, "Exit.", "Quits this epic project.", {10, 550}));
	_buttons[1].SetColors({ 0, 255, 50 });
	// Reset button
	_buttons.push_back(Button(_vars, ButtonFunctions::resetBox, "Reset box.", "Resets the contents of the box.", { 10, 60 }));
	_buttons[2].SetColors({ 0, 50, 255 });

	// Main text in menu.
	_name.setString("Balls2D");
	_name.setCharacterSize(90);
	_name.setPosition(300, 20);
	_name.setFont(_vars.assets.font);

	_author.setString("by Lukasz Lis");
	_author.setCharacterSize(30);
	_author.setPosition(400, 550);
	_author.setFont(_vars.assets.font);
	// Create animation
	_animation = Box(ballVec, { 600, 600 }, 1.0f, 0.0f, { 30, 30, 30 });
}

void StateMenu::Update(float dt)
{
	_animation.Update(dt);
	_animation.Draw(_vars);
	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i].Draw();
		_buttons[i].Update(dt);
	}
	_vars.window.draw(_name);
	_vars.window.draw(_author);
}
