#include "StateBox.h"

StateBox::StateBox(EnvVariables& vars)
	:State(vars)
{
	_fps.setFont(_vars.assets.font);
	_fps.setPosition(10, 10);
	_fps.setOutlineColor({ 0, 0, 0 });
	_fps.setOutlineThickness(2);
	_fps.setCharacterSize(20);
	std::vector<Ball> ballVec;
	for (int i = 0; i < 500; i++)
	{
		ballVec.push_back(Ball(i, sf::Vector2f(rand()%600, rand()%600) , 5.0f, 200.0f, { 220, 250, 220 }, { 0.0003, 0.0004 }));
	}
	_box = Box(ballVec, { 600, 600 }, 1.0f, 9.81f);
}

void StateBox::Update(float dt)
{
	if (_vars.inputs.left)  _box.AddWoosh({-_vars.options.wooshPower, 0});
	if (_vars.inputs.right) _box.AddWoosh({_vars.options.wooshPower,  0});
	if (_vars.inputs.up)    _box.AddWoosh({0, -_vars.options.wooshPower});
	if (_vars.inputs.down)  _box.AddWoosh({0, _vars.options.wooshPower});
	if (_vars.inputs.esc)  _vars.curState = eStates::stMenu;
	_box.Update(dt * 0.01f);
	_vars.window.draw(_box.GetSprite());

	if (_vars.frame % 15)
		_fps.setString(std::to_string(1000000 / _vars.real_dt));

	_vars.window.draw(_fps);
}
