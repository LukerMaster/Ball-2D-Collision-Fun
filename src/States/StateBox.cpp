#include "StateBox.h"

StateBox::StateBox(EnvVariables& vars)
	:_box(300, { 600, 600 }, 0.9f), State(vars)
{
	_fps.setFont(_vars.assets.font);
	_fps.setPosition(10, 10);
	_fps.setOutlineColor({ 0, 0, 0 });
	_fps.setOutlineThickness(2);
	_fps.setCharacterSize(20);
}

void StateBox::Update(float dt)
{
	if (_vars.inputs.left)  _box.AddWoosh({-_vars.options.wooshPower, 0});
	if (_vars.inputs.right) _box.AddWoosh({_vars.options.wooshPower,  0});
	if (_vars.inputs.up)    _box.AddWoosh({0, -_vars.options.wooshPower});
	if (_vars.inputs.down)  _box.AddWoosh({0, _vars.options.wooshPower});

	_box.Update(dt * 0.01f);
	_vars.window.draw(sf::Sprite(_box.GetTexture().getTexture()));

	if (_vars.frame % 15)
		_fps.setString(std::to_string(1000000 / _vars.dt));

	_vars.window.draw(_fps);

	_vars.window.display();
}
