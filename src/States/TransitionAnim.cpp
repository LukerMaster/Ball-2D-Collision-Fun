#include "TransitionAnim.h"


TransitionAnim::TransitionAnim(EnvVariables& vars)
	:_vars(vars),
	percentage(0.0f)
{
}

void TransitionAnim::Play(sf::Vector2i size, float speed) // Percentage from 0.0f to 1.0f
{
	percentage > 1.0f ? percentage = 1.0f : percentage;
	percentage < 0.0f ? percentage = 0.0f : percentage;
	float spd = 0.0001f; // Multiplier for speed of balls. Nothing to do with rectangles animation speed.
	if (percentage == 0.0f)
	{
		std::vector<Ball> ballVec;
		ballVec.push_back(Ball(333, sf::Vector2f(size.x / 2, size.y * 2), (int)(size.x / 1.75), 5000000.0f, sf::Color(rand()%200 + 55, rand() % 50 + 50, rand() % 200 + 55)));
		for (int i = 1; i <= 50; i++)
		{
			ballVec.push_back(Ball(i,
				sf::Vector2f((rand() % size.x), -(rand() % (int)(size.y * 0.2f)) - size.y),
				(rand() % (int)(size.y * 0.2f)) + 1,
				1.0f,
				sf::Color(rand() % 30 + 140, rand() % 30 + 140, rand() % 30 + 140),
				sf::Vector2f( ((rand() % 1) - 1 ) * spd * speed, (rand() % 3) ) * spd * speed));
		}
		_box = Box(ballVec, { size.x * 1.0f, size.y * 1.0f }, -1.0f, 3.0f * speed, sf::Color(0, 0, 0, 0));
	}
	sf::RectangleShape boxes[2];

	boxes[0].setFillColor({ 230, 230, 230 });
	boxes[1].setFillColor({ 0, 255, 50 });

	boxes[0].setSize(sf::Vector2f(size) * 5.0f);
	boxes[1].setSize(sf::Vector2f(size) * 5.0f);

	boxes[0].setOrigin(0, boxes[0].getSize().y);
	boxes[1].setOrigin(0, 0);

	if (percentage <= 0.3f)
	{
		float bAnim = cbrt(Addons::reverse_lerp(0.0f, 0.3f, percentage));
		boxes[0].setRotation(-45);
		boxes[1].setRotation(-45);
		boxes[0].setPosition((bAnim * size.x) - size.x, (bAnim * size.y));
		boxes[1].setPosition(size.x - (bAnim * size.x), (2 * size.y) - (bAnim * size.y));
	}
	else if (percentage >= 0.3f && percentage < 0.5f)
	{
		float bAnim = Addons::reverse_lerp(0.3f, 0.5f, percentage);
		bAnim = bAnim * bAnim;
		boxes[0].setPosition(bAnim * 0.5f * size.x, size.y + (bAnim * 0.5f * size.y));
		boxes[1].setPosition(bAnim * 0.5f * size.x, size.y + (bAnim * 0.5f * size.y));
		boxes[0].setRotation(-45 - (45 * bAnim));
		boxes[1].setRotation(-45 - (45 * bAnim));
		_box.Update(_vars.dt);
	}
	else if (percentage >= 0.5f && percentage < 1.0f)
	{
		_vars.curState = _vars.nextState;
		float bAnim = Addons::reverse_lerp(0.5f, 1.0f, percentage);
		bAnim = bAnim;
		boxes[0].setRotation(-90);
		boxes[1].setRotation(-90);
		boxes[0].setPosition(size.x / 2, size.y - (bAnim * size.y * 2));
		boxes[1].setPosition(size.x / 2, size.y - (bAnim * size.y * 2));
		_box.Update(_vars.dt);			
	}
	if (percentage > 0.2f)
	{
		float cAnim = Addons::reverse_lerp(0.2f, 0.95f, percentage);
		_box.balls[0].moveTo({ size.x * 0.4f + cAnim * 0.2f * size.x, size.y + _box.balls[0].GetRadius() - cAnim * (size.y + 2 * _box.balls[0].GetRadius()) });
		_box.balls[0].SetVelocity({ 0, -spd * 2 * speed });
	}

	_vars.window.draw(boxes[0]);
	_vars.window.draw(boxes[1]);
	_box.Draw(_vars);

	percentage += 0.001f * speed;
	if (percentage >= 1.0f)
	{
		percentage = 0.0f;
		_vars.transition = false;
	}

}
