#pragma once
#include "specifics/State.h"
#include "specifics/StateMenu.h"
#include "specifics/StatePlayfield.h"

class StateMachine
{
	std::map<eState, std::shared_ptr<State>> states;
public:
	void AddState(eState state, Vars& vars, sf::RenderWindow& window);

	void DeleteState(eState state);

	void Step(float dt, eState state);
	
	void Draw(eState state);
};

