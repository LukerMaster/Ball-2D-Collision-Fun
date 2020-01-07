#include "StateMenu.h"

StateMenu::StateMenu(EnvVariables& vars)
	:State(vars),
	_animation(4, {600, 600}, 1.0f, 0.0f, {10, 10, 10})
{

	_buttons.push_back(Button(_vars, "Open the box.", "Opens the box with balls and let's you start playing."));
	_buttons[0].func = ButtonFunctions::runBox;
	_buttons.push_back(Button(_vars, "Exit.", "Quits this epic project.", {10, 550}));
	_buttons[1].SetColors({ 0, 0, 255 });
	_buttons[1].func = ButtonFunctions::exit;

	// Main text in menu.
	_name.setString("Balls2D");
	_name.setCharacterSize(90);
	_name.setPosition(300, 20);
	_name.setFont(_vars.assets.font);
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
	_vars.window.display();
}
