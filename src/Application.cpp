#include "Application.h"
#include "specifics/StateMenu.h"
#include "specifics/StatePlayfield.h"

Application::Application(unsigned int window_height_, unsigned int window_width_, float framerate_, bool fullscreen_)
	:window(sf::VideoMode(window_height_, window_width_),
		"Grzybki, Gloniki i Bateryjki!",
		sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize | (fullscreen_ & sf::Style::Fullscreen)),
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

	vars.playfield_size = 12;

	vars.assets.font.loadFromFile("assets/gooddogp.mlg");
	vars.assets.btn_click.loadFromFile("assets/mnst.mlg");
	vars.assets.btn_hover.loadFromFile("assets/mnsl.mlg");
	vars.assets.microbe_tex.loadFromFile("assets/mcb.mlg");

	vars.assets.bubble_tex.loadFromFile("assets/bble.mlg");
	vars.assets.plank_tex.loadFromFile("assets/deska.mlg");

}

void Application::Run()
{
	sf::Event events;

	float dtDesired = (1.0f / vars.framerate) * 1000.0f; // In milliseconds.
	float dt = 0;

	sf::Clock dtClock;
	dtClock.restart();
	state_machine.AddState(eState::menu, vars, window);

	while (vars.is_running)
	{
		// Timing
		dt = dtClock.getElapsedTime().asMilliseconds();
		if (dt < dtDesired)
		{
			sf::sleep(sf::milliseconds(dtDesired) - sf::milliseconds(dt));
			dt = dtClock.getElapsedTime().asMilliseconds();
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
		window.clear({ 0, 0, 0, 255 });

		state_machine.Step(dt, vars.current_state);
		state_machine.Draw(vars.current_state);

		if (vars.next_state != vars.current_state)
		{
			if (transition == nullptr)
			{
				transition = std::make_unique<TransitionAnim>(TransitionAnim(vars.assets.bubble_tex, vars.assets.plank_tex, 700, window.getSize()));
				state_machine.AddState(vars.next_state, vars, window);
			}
		}
		if (transition != nullptr)
		{
			transition->Step(dt);
			transition->Draw(window);
			if (transition->GetPercentage() > 0.7f)
				vars.current_state = vars.next_state;
			if (transition->GetPercentage() > 1.0f)
				transition = nullptr;
		}

		window.display();

		//
		//
		//
	}
}
