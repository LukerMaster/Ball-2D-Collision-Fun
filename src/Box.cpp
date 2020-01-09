#include "Box.h"

Box::Box()
{
}

Box::Box(std::vector<Ball> ballVec, sf::Vector2f boxSize, float wall_stiffness, float gravity_mult, sf::Color bg_color)
	: size(boxSize),
	wallStiffness(wall_stiffness),
	bgColor(bg_color),
	gravity(gravity_mult),
	balls(ballVec),
	selected(-1)
{
	srand(time(NULL));
	_texture.create(size.x, size.y);
}

void Box::Update(float dt)
{
	std::vector<std::pair<Ball*, Ball*>> collided;
	for (int i = 0; i < balls.size(); i++)
	{
		if (wallStiffness != -1.0f)
			ContainInBox(balls[i]);
		PullByGravity(balls[i]);
		for (int j = i; j < balls.size(); j++)
		{
			if (i != j)
			{
				if (DoBallsOverlap(balls[i], balls[j]))
				{
					StaticCollision(balls[i], balls[j]);
					if (i < j)
						collided.push_back(std::make_pair(&balls[i], &balls[j]));
				}
			}
		}
	}
	for (auto pair : collided)
	{
		DynamicCollision(*pair.first, *pair.second);
	}
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i].Update(dt);
	}
}

void Box::Draw(EnvVariables& vars)
{
	sf::RectangleShape boxShape;
	boxShape.setFillColor(bgColor);
	boxShape.setSize({size.x, size.y});
	vars.window.draw(boxShape);
	for (int i = 0; i < balls.size(); i++)
	{
		vars.window.draw(balls[i].GetShape());
	}
}

float Box::GetSDistance(sf::Vector2f point1, sf::Vector2f point2) // Never returns 0.
{
	float dist = sqrt(((point1.x - point2.x) * (point1.x - point2.x)) + ((point1.y - point2.y) * (point1.y - point2.y)));
	if (dist == 0)
	{
		//std::cout << "Warn: Zero distance between objects detected, returned 1.\n";
		return 1.0f;
	}
	else return dist;
}


float Box::GetDistance(sf::Vector2f point1, sf::Vector2f point2)
{
	return sqrt(((point1.x - point2.x) * (point1.x - point2.x)) + ((point1.y - point2.y) * (point1.y - point2.y)));
}

sf::Vector2f Box::GetVector(sf::Vector2f from, sf::Vector2f to)
{
	return sf::Vector2f(to.x - from.x , to.y - from.y);
}

sf::Vector2f Box::GetExperimentalVector(sf::Vector2f from, sf::Vector2f to)
{
	float x, y;
	x = to.x - from.x;
	y = to.y - from.y;
	if (x < 0.01f && x >= 0)
		x = 0.01f;
	else if (x > -0.01f && x < 0)
		x = -0.01f;
	if (y < 0.01f && y >= 0)
		y = 0.01f;
	else if (y > -0.01f && y < 0)
		y = -0.01f;
	return sf::Vector2f(x, y);
}

bool Box::DoBallsOverlap(Ball& b1, Ball& b2)
{
	if ((b1.GetPosition().x - b2.GetPosition().x) * (b1.GetPosition().x - b2.GetPosition().x) + (b1.GetPosition().y - b2.GetPosition().y) * (b1.GetPosition().y - b2.GetPosition().y) < (b1.GetRadius() + b2.GetRadius()) * (b1.GetRadius() + b2.GetRadius()))
		return true;
	else
		return false;
}

void Box::ContainInBox(Ball& ball)
{
	if (ball.GetPosition().x + ball.GetRadius() > size.x)
	{
		ball.moveTo({ size.x - ball.GetRadius() , ball.GetPosition().y });
		ball.SetVelocity({ -ball.GetVelocity().x * wallStiffness , ball.GetVelocity().y });
	}
	if (ball.GetPosition().x - ball.GetRadius() < 0)
	{
		ball.moveTo({ ball.GetRadius(), ball.GetPosition().y });
		ball.SetVelocity({ -ball.GetVelocity().x * wallStiffness , ball.GetVelocity().y });
	}
	if (ball.GetPosition().y + ball.GetRadius() > size.y)
	{
		ball.moveTo({ ball.GetPosition().x , size.y - ball.GetRadius() });
		ball.SetVelocity({ ball.GetVelocity().x , -ball.GetVelocity().y * wallStiffness });
	}
	if (ball.GetPosition().y - ball.GetRadius() < 0)
	{
		ball.moveTo({ ball.GetPosition().x , ball.GetRadius()});
		ball.SetVelocity({ ball.GetVelocity().x , -ball.GetVelocity().y * wallStiffness });
	}
}

int Box::GetBallByPos(sf::Vector2i pos)
{
	
	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i].IsPointInside(sf::Vector2f(pos)))
			return i;
	}
	return -1;
}

void Box::StaticCollision(Ball& b1, Ball& b2)
{
	float distance = GetSDistance(b2.GetPosition(), b1.GetPosition());
	
	sf::Vector2f vector = GetVector(b2.GetPosition(), b1.GetPosition());
	
	float overlap = (distance - b1.GetRadius() - b2.GetRadius());

	b1.move((-overlap * (b2.GetMass() / (b1.GetMass() + b2.GetMass())) * vector) / distance);
	b2.move((overlap * (b1.GetMass() / (b1.GetMass() + b2.GetMass())) * vector) / distance);
	
	
	//b1.SetColor({ 0, 0, 255 });
	//b2.SetColor({ 0, 0, 255 });
}

void Box::DynamicCollision(Ball& b1, Ball& b2)
{
	if (b1.GetMass() > b2.GetMass())
	{
		DynamicCollision(b2, b1);
	}
	else
	{
		float distance = GetSDistance(b2.GetPosition(), b1.GetPosition());
		sf::Vector2f normal = GetVector(b1.GetPosition(), b2.GetPosition()) / distance;
		sf::Vector2f tangental = { -normal.y, normal.x };

		//Dynamic collision

		float dPr1tan = Addons::dot_product(b1.GetVelocity(), tangental);
		float dPr2tan = Addons::dot_product(b2.GetVelocity(), tangental);

		float dPr1nor = Addons::dot_product(b1.GetVelocity(), normal);
		float dPr2nor = Addons::dot_product(b2.GetVelocity(), normal);

		float momentum1 = (dPr1nor * (b1.GetMass() - b2.GetMass()) + 2.0f * b2.GetMass() * dPr2nor) / (b1.GetMass() + b2.GetMass());
		float momentum2 = (dPr2nor * (b2.GetMass() - b1.GetMass()) + 2.0f * b1.GetMass() * dPr1nor) / (b1.GetMass() + b2.GetMass());
		b1.SetVelocity((tangental * dPr1tan) + (normal * momentum1));
		b2.SetVelocity((tangental * dPr2tan) + (normal * momentum2));
	}
}

void Box::PullByGravity(Ball& b1)
{
	b1.AddForce({ 0, gravity * b1.GetMass() * 0.000001f });
}

void Box::AddWoosh(sf::Vector2f direction)
{
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i].AddForce(direction);
	}
}

void Box::AddBall(Ball ball)
{
	balls.push_back(ball);
}

bool Box::isAnyBallSelected()
{
	if (selected != -1)
		return true;
	else
		return false;
}

void Box::SelectBallUnder(sf::Vector2i pos)
{
	selected = -1;
	for (int i = 0; i < balls.size(); i++)
	{
		if (GetDistance(sf::Vector2f(pos), balls[i].GetPosition()) < balls[i].GetRadius())
		{
			selected = i;
			break;
		}
	}
}

sf::Vector2f Box::GetPosOfSelected()
{
	if (selected != -1)
		return balls[selected].GetPosition();
	else return sf::Vector2f(0, 0);

}

void Box::AddForceToSelected(sf::Vector2f force)
{
	if (selected != -1)
		balls[selected].AddForce(force);
}

void Box::DeselectBall()
{
	selected = -1;
}
