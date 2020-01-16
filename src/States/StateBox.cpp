#include "StateBox.h"

sf::Vector2f StateBox::_GetVector(sf::Vector2f from, sf::Vector2f to)
{
	return sf::Vector2f(to.x - from.x, to.y - from.y);
}

float StateBox::_GetDistance(sf::Vector2f point1, sf::Vector2f point2)
{
	return sqrt(((point1.x - point2.x) * (point1.x - point2.x)) + ((point1.y - point2.y) * (point1.y - point2.y)));
}

sf::Color StateBox::_getHSVColor(int hue, float sat, float val)
{
	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));

	switch (h)
	{
		default:
		case 0:
		case 6: return sf::Color(val * 255, t * 255, p * 255);
		case 1: return sf::Color(q * 255, val * 255, p * 255);
		case 2: return sf::Color(p * 255, val * 255, t * 255);
		case 3: return sf::Color(p * 255, q * 255, val * 255);
		case 4: return sf::Color(t * 255, p * 255, val * 255);
		case 5: return sf::Color(val * 255, p * 255, q * 255);
	}
}


//
//
//
// User functions below.
//
//
//


StateBox::StateBox(EnvVariables& vars)
	:State(vars)
{
	_prevClicked = false;
	cooldown = 0;
	CreateBox();
}

void StateBox::Update(float dt)
{
	// If box is reset.
	if (_vars.options.resetBox)
	{
		CreateBox();
		_vars.options.resetBox = false;
	}
	// If balls hitting each other are colored.
	if (_vars.options.coloredHits)
		_box.coloredHits = true;
	else
		_box.coloredHits = false;

	_box.UpdateGravity(_vars.options.gravityScale);
	_box.UpdateStiffness((float)_vars.options.wallStiffness * 0.01f);

	if (_vars.inputs.left)  _box.AddWoosh({ (float)-_vars.options.wooshPower * 0.005f, 0 });
	if (_vars.inputs.right) _box.AddWoosh({ (float)_vars.options.wooshPower * 0.005f,  0 });
	if (_vars.inputs.up)    _box.AddWoosh({ 0, (float)-_vars.options.wooshPower * 0.005f });
	if (_vars.inputs.down)  _box.AddWoosh({ 0,(float)_vars.options.wooshPower * 0.005f });
	if (_vars.inputs.esc)
	{
		_vars.transition = true;
		_vars.nextState = eStates::stMenu;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _prevClicked < 5)
	{
		_box.SelectBallUnder(_vars.inputs.mouse_pos);
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && _prevClicked)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			_box.AddForceToSelected(_GetVector(sf::Vector2f(_vars.inputs.mouse_pos), _box.GetPosOfSelected()) * _GetDistance(sf::Vector2f(_vars.inputs.mouse_pos), _box.GetPosOfSelected()) * 0.001f, true);
		}
		else
		{
			_box.AddForceToSelected(_GetVector(sf::Vector2f(_vars.inputs.mouse_pos),_box.GetPosOfSelected() ) * _GetDistance(sf::Vector2f(_vars.inputs.mouse_pos), _box.GetPosOfSelected()) * 0.001f, false);
		}
		_box.DeselectBall();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (_box.GetBallCount() < 1000)
			_box.AddBall(Ball(0, sf::Vector2f(sf::Mouse::getPosition(_vars.window)), 11.0f, 200.0f, _getHSVColor(rand()%361, 1.0f, 1.0f)));
	}
	if (cooldown == 0 && _box.GetBallCount() < 1000)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			_box.AddBall(Ball(2, sf::Vector2f(sf::Mouse::getPosition(_vars.window)), 15.0f, 2000.0f, _getHSVColor((rand() % 30) + 280, ((rand() % 60) + 40) * 0.01f, 1.0f)));
			cooldown = 100;
		}
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			_box.AddBall(Ball(4, sf::Vector2f(sf::Mouse::getPosition(_vars.window)), 20.0f, 4000.0f, _getHSVColor((rand() % 20)+10, 1.0f, (rand() % 50) * 0.01f)));
			cooldown = 100;
		}	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			_box.AddBall(Ball(8, sf::Vector2f(sf::Mouse::getPosition(_vars.window)), 30.0f, 8000.0f, _getHSVColor(rand() % 40 + 200, ((rand()%60) + 40) * 0.01f, ((rand() % 20) * 0.01f) + 0.8f)));
			cooldown = 100;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			_box.AddBall(Ball(8, sf::Vector2f(sf::Mouse::getPosition(_vars.window)), 40.0f, 32000.0f, _getHSVColor(rand()%360, (rand() % 20) * 0.01f, 1.0f)));
			cooldown = 100;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			_box.AddBall(Ball(8, sf::Vector2f(sf::Mouse::getPosition(_vars.window)), 50.0f, 256000.0f, _getHSVColor((rand() % 30)+40, ((rand() % 20) + 80) * 0.01f, 1.0f)));
			cooldown = 100;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			_box.AddBall(Ball(8, sf::Vector2f(sf::Mouse::getPosition(_vars.window)), 100.0f, 65536000.0f, _getHSVColor(rand() % 20, 1.0f, ((rand()%20) + 80) * 1.0f)));
			cooldown = 100;
		}
	}
	
	_box.Update(dt * 0.1f);
	_box.Draw(_vars.window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (_box.isAnyBallSelected())
		{
			Arrow arrow(_getHSVColor(rand() % 255, 1.0f, 1.0f)* sf::Color(255, 255, 255, 128), { 0, 0, 0, 0 }, 2.0f);
			arrow.Draw(_vars.window, sf::Vector2f(_vars.inputs.mouse_pos), _box.GetPosOfSelected());
		}
	}

	_box.DrawHoveredInfo(_vars.inputs.mouse_pos, _vars.window, _vars.assets.font);


	sf::Mouse::isButtonPressed(sf::Mouse::Left) ? _prevClicked++ : _prevClicked--;
	_prevClicked = (_prevClicked < 0 ? 0 : _prevClicked);
	_prevClicked = (_prevClicked > 5 ? 5 : _prevClicked);

	cooldown > 0 ? cooldown-- : cooldown = cooldown;
}

void StateBox::CreateBox()
{
	std::vector<Ball> ballVec;
	_box = Box(ballVec, { 600, 600 }, 0.5f, 9.81f * _vars.options.gravityScale, {40, 40, 40});
}
