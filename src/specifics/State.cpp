#include "State.h"

State::State(Vars& vars_, sf::RenderWindow& window_, eState type_)
	:vars(vars_),
	window(window_),
	type(type_)
{
}
