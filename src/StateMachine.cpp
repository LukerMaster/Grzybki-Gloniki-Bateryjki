#include "StateMachine.h"

void StateMachine::AddState(eState state, Vars& vars, sf::RenderWindow& window)
{
	bool is_already = false;

	if (states.count(state) != 0)
		is_already = true;
	
	if (!is_already)
	{
		if (state == eState::menu)
			states[state] = std::make_shared<StateMenu>(vars, window);
		else if (state == eState::playfield)
			states[state] = std::make_shared<StatePlayfield>(vars, window);
	}
}

void StateMachine::DeleteState(eState state)
{
	states.erase(state);
}

void StateMachine::Step(float dt, eState state)
{
	if (states.count(state) != 0)
		states.find(state)->second->Step(dt);
}

void StateMachine::Draw(eState state)
{
	if (states.count(state) != 0)
		states.find(state)->second->Draw();
}