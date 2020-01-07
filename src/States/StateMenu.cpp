#include "StateMenu.h"

StateMenu::StateMenu(EnvVariables& vars)
	:State(vars)
{
	buttons.push_back(Button(_vars, "Open the box.", "Opens the box with balls and let's you start playing."));
	buttons[0].func = ButtonFunctions::runBox;
	buttons.push_back(Button(_vars, "Exit.", "Quits this epic project.", {10, 500}));
	buttons[1].SetColors({ 0, 0, 255 });
	buttons[1].func = ButtonFunctions::exit;
}

void StateMenu::Update(float dt)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		_vars.window.draw(buttons[i].GetSprite());
		buttons[i].Update(sf::Mouse::getPosition(_vars.window));
	}
	_vars.window.display();
}
