#pragma once
#include "SFML/Graphics.hpp"
#include "Vars.h"
#include "State.h"

#include "playfield/EmptySpace.h"
#include "playfield/GermClasses.h"
#include "../Button.h"

//#include <iostream>
class StatePlayfield : public State
{
	sf::Sprite playfield_bg;
	
	Button btn_back;
	std::vector<std::vector<std::shared_ptr<Object>>> objects;
public:
	StatePlayfield(Vars& vars_, sf::RenderWindow& window);
	virtual void Step(float dt);
	virtual void Draw();
};

