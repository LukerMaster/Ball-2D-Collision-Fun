#include "StateMenu.h"
void StateMenu::btnRunBox()
{
	_vars.nextState = eStates::stBox;
	_vars.transition = true;
}

void StateMenu::btnExit()
{
	_vars.options.isOpen = false;
	_vars.window.close();
}

void StateMenu::btnResetBox()
{
	_vars.options.resetBox = true;
}

void StateMenu::btnMoreWoosh()
{
	if (_vars.options.wooshPower <= 0.995)
		_vars.options.wooshPower += 0.005;
}

void StateMenu::btnLessWoosh()
{
	if (_vars.options.wooshPower >= 0.005)
		_vars.options.wooshPower -= 0.005;
}

void StateMenu::btnMoreGravity()
{
	if (_vars.options.gravityScale <= 4.75f)
		_vars.options.gravityScale += 0.25f;
}

void StateMenu::btnLessGravity()
{
	if (_vars.options.gravityScale >= -0.75f)
		_vars.options.gravityScale -= 0.25f;
}

void StateMenu::checkButtons()
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i].CheckAndUnclick())
		{
			switch (_buttons[i].funcID)
			{
			case eExit:
				btnExit();
				break;
			case eRunMenu:
				break;
			case eRunBox:
				btnRunBox();
				break;
			case eResetBox:
				btnResetBox();
				break;
			case eLessWoosh:
				btnLessWoosh();
				break;
			case eMoreWoosh:
				btnMoreWoosh();
				break;
			case eLessGravity:
				btnLessGravity();
				break;
			case eMoreGravity:
				btnMoreGravity();
				break;
			default:
			#ifdef DEBUG
				std::cout << "Minor warn: Clicked a button without a function.\n";
			#endif
				break;
			}
		}
	}
}



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
	_options.push_back(sf::Text("Woosh", vars.assets.font, 30));
	_options.push_back(sf::Text("Gravity", vars.assets.font, 30));

	_options[0].setPosition({ 50, 260 });
	_options[1].setPosition({ 50, 320 });

	_buttons.push_back(Button(btnFuncs::eRunBox,      { 10, 10 }, { 180, 40 }, "Open the box.",	_vars.assets.font, _vars.assets.menuSelect, _vars.assets.menuClick,"Opens the box with balls and let's you start playing."));
	_buttons.push_back(Button(btnFuncs::eExit,		  {10, 550 }, { 180, 40 }, "Exit.",			_vars.assets.font, _vars.assets.menuSelect, _vars.assets.menuClick, "Quits this epic project." ));
	_buttons.push_back(Button(btnFuncs::eResetBox,    { 10, 60 }, { 180, 40 }, "Reset box.",	_vars.assets.font, _vars.assets.menuSelect, _vars.assets.menuClick, "Resets the contents of the box." ));
	_buttons.push_back(Button(btnFuncs::eLessWoosh,   { 10, 260}, { 40, 40  }, " <",			_vars.assets.font, _vars.assets.menuSelect, _vars.assets.menuClick, "Less woosh power when you press arrow keys."));
	_buttons.push_back(Button(btnFuncs::eMoreWoosh,   {150, 260}, { 40, 40  }, " >",			_vars.assets.font, _vars.assets.menuSelect, _vars.assets.menuClick, "More woosh power when you press arrow keys."));
	_buttons.push_back(Button(btnFuncs::eLessGravity, {10, 320 }, { 40, 40  }, " <",			_vars.assets.font, _vars.assets.menuSelect, _vars.assets.menuClick, "More powerful gravity inside the box."));
	_buttons.push_back(Button(btnFuncs::eMoreGravity, {150, 320}, { 40, 40  }, " >",			_vars.assets.font, _vars.assets.menuSelect, _vars.assets.menuClick, "Less powerful gravity inside the box."));
	_buttons.push_back(Button(btnFuncs::eColoredBalls, {150, 320}, { 40, 40  }, " >",			_vars.assets.font, _vars.assets.menuSelect, _vars.assets.menuClick, "Less powerful gravity inside the box."));

	_buttons[1].SetColors({ 0, 255, 50 });

	_buttons[2].SetColors({ 0, 50, 255 });

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
	_animation.Draw(_vars.window);
	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i].Draw(_vars.window);
		_buttons[i].Update(dt, _vars.inputs.mouse_pos);
	}

	_options[0].setString("Woosh		" + std::to_string((int)(_vars.options.wooshPower * 5001)) + "%");
	_options[1].setString("Gravity		" + std::to_string((int)(_vars.options.gravityScale * 100)) + "%");
	for (int i = 0; i < _options.size(); i++)
	{
		_vars.window.draw(_options[i]);
	}

	checkButtons();

	_vars.window.draw(_name);
	_vars.window.draw(_author);
}
