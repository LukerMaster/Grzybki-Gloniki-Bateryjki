#pragma once
#include "SFML/Graphics.hpp"
#include "Vars.h"
class State
{
protected:
	Vars& vars;
	sf::RenderWindow& window;
public:
	State(Vars& vars_, sf::RenderWindow& window_);
	virtual void Step(float dt) = 0;
	virtual void Draw() = 0;
};

