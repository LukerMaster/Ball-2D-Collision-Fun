#include "StateBox.h"

StateBox::StateBox(EnvVariables& vars)
	:State(vars),
	_menu(vars, { Button(vars, ButtonFunctions::exit, "Add Ball", "No description"),
		Button(vars,ButtonFunctions::exit, "Add Balls", "No description"),
		Button(vars,ButtonFunctions::exit, "Remove Balls", "No description"),
		Button(vars,ButtonFunctions::exit, "Set Gravity", "No description"),
		Button(vars,ButtonFunctions::exit, "Set Gravity", "No description"),
		Button(vars,ButtonFunctions::exit, "Set Gravity", "No description"),
		Button(vars,ButtonFunctions::exit, "Set Gravity", "No description") },
		{ 0, 0, 0, 140 }, sf::Text("Mode:", _vars.assets.font, 30)
		)
{
	_prevClicked = false;
	CreateBox();
}

void StateBox::Update(float dt)
{
	if (_vars.options.resetBox)
	{
		CreateBox();
		_vars.options.resetBox = false;
	}
	if (_vars.inputs.left)  _box.AddWoosh({ -_vars.options.wooshPower, 0 });
	if (_vars.inputs.right) _box.AddWoosh({ _vars.options.wooshPower,  0 });
	if (_vars.inputs.up)    _box.AddWoosh({ 0, -_vars.options.wooshPower });
	if (_vars.inputs.down)  _box.AddWoosh({ 0, _vars.options.wooshPower });
	if (_vars.inputs.esc)
	{
		_vars.transition = true;
		_vars.nextState = eStates::stMenu;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _prevClicked == false)
	{

		//_box.AddBall(Ball(0, sf::Vector2f(sf::Mouse::getPosition(_vars.window)), 15.0f, 4500.0f, Addons::hsv(rand() % 361, 1.0f, 1.0f)));
		//if (_menu.isOpen() && !_menu.isHovered())
			//_menu.Hide();
		//if (!_menu.isOpen())
			//_menu.Open(1.0f, sf::Mouse::getPosition(_vars.window));
		_box.SelectBallUnder(_vars.inputs.mouse_pos);
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && _prevClicked == true)
	{
		_box.AddForceToSelected(Addons::get_vector(sf::Vector2f(_vars.inputs.mouse_pos),_box.GetPosOfSelected()  ) * 0.01f);
		_box.DeselectBall();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		_box.AddBall(Ball(0, sf::Vector2f(sf::Mouse::getPosition(_vars.window)), 10.0f, 1000.0f, Addons::hsv(rand()%361, 1.0f, 1.0f)));
	}
	_box.Update(dt * 0.1f);
	_box.Draw(_vars);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (_box.isAnyBallSelected())
		{
			sf::Vertex line[2];
			line[0].position = _box.GetPosOfSelected();
			line[1].position = sf::Vector2f(_vars.inputs.mouse_pos);
			_vars.window.draw(line, 2, sf::Lines);
		}
	}


	if (_menu.isOpen())
	{
		//_menu.Update(dt);
		//_vars.window.draw(_menu.GetSprite());
	}
	sf::Mouse::isButtonPressed(sf::Mouse::Left) ? _prevClicked = true : _prevClicked = false;
}

void StateBox::CreateBox()
{
	std::vector<Ball> ballVec;
	for (int i = 0; i < 20; i++)
	{
		ballVec.push_back(Ball(i, sf::Vector2f(rand() % 600, rand() % 200), 5.0f, 1000.0f, { 220, 255, 220 }, { 0.00003, 0.00004 }));
	}
	_box = Box(ballVec, { 600, 600 }, 0.5f, 9.81f * _vars.options.gravityScale);
}
