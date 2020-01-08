#include "SFML/Graphics.hpp"
#include "src/AppInstance.h"
#include "src/States/StateBox.h"
#include "src/States/StateMenu.h"

#include <iostream>

int main()
{
	AppInstance instance;
	instance.vars().curState = eStates::stMenu;
	instance.vars().options.isOpen = true;

	StateMenu stateMenu(instance.vars());
	StateBox stateBox(instance.vars());
	sf::Vector2f a = { 3, 2 };

	instance.states.push_back(&stateMenu);
	instance.states.push_back(&stateBox);
	instance.vars().assets.font.loadFromFile("assets/roboto.ttf");
	sf::Clock time;

	TransitionAnim transition(instance.vars());

	instance.vars().options.wooshPower = 2.0f;

	sf::Event eventHandler;

	while (instance.vars().options.isOpen)
	{
		instance.vars().window.clear(sf::Color::Black);

		// Main state loop
		instance.states[(int)instance.vars().curState]->Update(instance.vars().dt);
		if (instance.vars().transition)
		{
			instance.vars().window.draw(transition.Play({ 600, 600 }, 4.0f));
		}
		instance.vars().window.display();

		// Events
		instance.vars().window.pollEvent(eventHandler);
		if (eventHandler.type == sf::Event::Closed)
		{
			instance.vars().options.isOpen;
			instance.vars().window.close();
		}

		//Key presses
		instance.vars().inputs.checkKeyPresses();
		instance.vars().inputs.checkMousePos(instance.vars().window);
		
		// Time measurement
		instance.vars().dt = time.getElapsedTime().asMicroseconds();

		//std::cout << dt << std::endl;

		if (instance.vars().dt < 4000)
		{
			sf::sleep(sf::microseconds(4000 - (double)instance.vars().dt));
		}
		instance.vars().real_dt = time.getElapsedTime().asMicroseconds();
		instance.vars().dt = time.getElapsedTime().asMicroseconds();
		if (instance.vars().dt > 4000) instance.vars().dt = 4000;
		time.restart();
		instance.vars().frame++;
	}
	return 0;
}