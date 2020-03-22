#include "Application.h"
#include "specifics/StateMenu.h"
#include "specifics/StatePlayfield.h"

Application::Application(unsigned int window_height_, unsigned int window_width_, float framerate_, bool fullscreen_)
	:window(sf::VideoMode(window_height_, window_width_),
		"Grzybki, Gloniki i Bateryjki!",
		sf::Style::Titlebar | sf::Style::Close | (fullscreen_ & sf::Style::Fullscreen)),
	window_height(window_height_),
	window_width(window_width_),
	vars()
{
	vars.is_running = true;
	vars.framerate = framerate_;
	vars.fullscreen = fullscreen_;
	vars.num_of_algae = 1;
	vars.num_of_bacteria = 1;
	vars.num_of_shrooms = 1;
	vars.current_state = eState::menu;
	vars.next_state = eState::menu;

	vars.assets.font.loadFromFile("assets/gooddogp.mlg");
	vars.assets.btn_click.loadFromFile("assets/mnst.mlg");
	vars.assets.btn_hover.loadFromFile("assets/mnst.mlg");
	vars.assets.microbe_tex.loadFromFile("assets/mcb.mlg");

}

void Application::Run()
{
	sf::Event events;

	float dtDesired = (1.0f / vars.framerate) * 1000000.0f; // In microseconds. FOR (redundant) PRECISION!
	float dt = 0;

	sf::Clock dtClock;
	dtClock.restart();
	std::map<eState, std::shared_ptr<State>> states;
	states[eState::menu] = std::make_shared<StateMenu>(vars, window);

	while (vars.is_running)
	{
		// Timing
		dt = dtClock.getElapsedTime().asMicroseconds();
		if (dt < dtDesired)
		{
			sf::sleep(sf::microseconds(dtDesired) - sf::microseconds(dt));
			dt = dtClock.getElapsedTime().asMicroseconds();
		}
		else if (dt > dtDesired * 5)
			dt = dtDesired * 5;

		dtClock.restart();

		if (window.pollEvent(events))
		{
			if (events.type == sf::Event::Closed)
			{
				vars.is_running = false;
			}
		}

		//
		// Game state update
		//
		if (vars.next_state != vars.current_state)
		{
			if (vars.next_state == eState::playfield)
				states[eState::playfield] = std::make_shared<StatePlayfield>(StatePlayfield(vars, window));
			if (vars.next_state == eState::menu)
				states[eState::menu] == std::make_shared<StateMenu>(StateMenu(vars, window));


			vars.current_state = vars.next_state;
		}
		else
		{
			if (vars.current_state == eState::menu)
			{
				states.find(eState::menu)->second->Step(dt);
				states.find(eState::menu)->second->Draw();
			}

			if (vars.current_state == eState::playfield)
			{
				states.find(eState::playfield)->second->Step(dt);
				states.find(eState::playfield)->second->Draw();
			}
		}
		

		//
		//
		//
	}
}
