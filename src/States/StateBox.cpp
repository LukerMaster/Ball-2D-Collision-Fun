#include "StateBox.h"

StateBox::StateBox(EnvVariables& vars)
	:State(vars)
{
	std::vector<Button> menuButtons;
	menuButtons.push_back(Button(vars, "Add Ball", "No description"));
	menuButtons.push_back(Button(vars, "Add Balls", "No description"));
	menuButtons.push_back(Button(vars, "Remove Balls", "No description"));
	menuButtons.push_back(Button(vars, "Set Gravity", "No description"));
	sf::Text menuLabel;
	menuLabel.setString("Mode:");
	menuLabel.setCharacterSize(30);
	menuLabel.setFont(_vars.assets.font);

	_menu = ContextMenu(menuButtons, { 0, 0, 0, 140 }, menuLabel);

	_prevClicked = false;
	_fps.setFont(_vars.assets.font);
	_fps.setPosition(10, 10);
	_fps.setOutlineColor({ 0, 0, 0 });
	_fps.setOutlineThickness(2);
	_fps.setCharacterSize(20);
	std::vector<Ball> ballVec;
	for (int i = 0; i < 10; i++)
	{
		ballVec.push_back(Ball(i, sf::Vector2f(rand()%600, rand()%600) , 5.0f, 8000.0f, { 220, 250, 220 }, { 0.0003, 0.0004 }));
	}
	_box = Box(ballVec, { 600, 600 }, 0.5f, 9.81f);
}

void StateBox::Update(float dt)
{
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
		_box.AddBall(Ball(0, sf::Vector2f(sf::Mouse::getPosition(_vars.window))));
		_menu.Open(1.0f, sf::Mouse::getPosition(_vars.window));
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		_box.AddBall(Ball(0, sf::Vector2f(sf::Mouse::getPosition(_vars.window))));
	}
	_box.Update(dt * 0.1f);
	_menu.Update(dt * 0.01f);
	_vars.window.draw(_box.GetSprite());

	if (_vars.frame % 15)
		_fps.setString(std::to_string(1000000 / _vars.real_dt));

	_vars.window.draw(_fps);
	if (_menu.isOpen())
		_vars.window.draw(_menu.Show());
	sf::Mouse::isButtonPressed(sf::Mouse::Left) ? _prevClicked = true : _prevClicked = false;
}