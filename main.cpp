#include "SFML/Graphics.hpp"
#include "src/AppInstance.h"
#include "src/States/StateBox.h"
#include "src/States/StateMenu.h"
#include "src/TransitionAnim.h"

#define DEBUG

#include <iostream>
//v0.0.2
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
	sf::Clock time;
	
	sf::Text debug_fps;
	debug_fps.setCharacterSize(15);
	debug_fps.setFont(instance.vars().assets.font);
	debug_fps.setPosition(520, 580);
	debug_fps.setOutlineColor({ 30, 30, 30 });
	debug_fps.setOutlineThickness(1);
	
	TransitionAnim transition;

	sf::Event eventHandler;

	while (instance.vars().options.isOpen)
	{
		instance.vars().window.clear(sf::Color::Black);

		// Main state loop
		//
		//
		//
		instance.states[(int)instance._vars.curState]->Update(instance._vars.dt);

		if (instance._vars.transition)
		{
			transition.Progress({ 600, 600 }, instance._vars.dt, instance._vars.window, 3.0f);
			if (transition.GetPercentage() > 0.5f)
				instance._vars.curState = instance._vars.nextState;
			if (transition.GetPercentage() >= 1.0f)
			{
				transition.Reset();
				instance._vars.transition = false;
			}
				
		}
		instance._vars.window.draw(debug_fps);
		instance._vars.window.display();
		//
		//
		//


		// Events
		instance._vars.window.pollEvent(eventHandler);
		if (eventHandler.type == sf::Event::Closed)
		{
			instance._vars.options.isOpen;
			instance._vars.window.close();
		}

		//Key presses
		instance._vars.inputs.checkKeyPresses();
		instance._vars.inputs.checkMousePos(instance._vars.window);
		
		// Time measurement
		instance._vars.dt = time.getElapsedTime().asMicroseconds();



		if (instance.vars().dt < 4000)
		{
			sf::sleep(sf::microseconds(4000 - (double)instance._vars.dt));
		}

		if (instance._vars.frame % 20 == 0)
			debug_fps.setString( std::to_string(1000000 / time.getElapsedTime().asMicroseconds()) + " FPS");

		instance._vars.real_dt = time.getElapsedTime().asMicroseconds();
		instance._vars.dt = time.getElapsedTime().asMicroseconds();
		if (instance._vars.dt > 4000) instance._vars.dt = 4000;
		time.restart();
		instance._vars.frame++;
	}
	return 0;
}