#pragma once
#include "SFML/Graphics.hpp"
#include "Vars.h"
class State
{
protected:
	eState type;
	Vars& vars;
	sf::RenderWindow& window;
public:
	State(Vars& vars_, sf::RenderWindow& window_, eState type);
	virtual void Step(float dt) = 0;
	virtual void Draw() = 0;

	eState GetType() { return type; };
};

