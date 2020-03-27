#pragma once
#include "Object.h"
class Food :
	public Object
{
public:
	float food_value;
	Food(sf::Vector2i start_pos_, sf::Vector2i end_pos_, sf::IntRect text_rect_,float food_value_);
	virtual void Step(float dt);
};

