#pragma once
#include "SFML/Graphics.hpp"
#include "specifics/Vars.h"
class Application
{
	Vars vars;
	sf::RenderWindow window;
	unsigned int window_width;
	unsigned int window_height;

public:
	Application(unsigned int window_height = 500, unsigned int window_width = 500, float framerate_ = 60.0f , bool fullscreen_ = false);
	void Run();
};

