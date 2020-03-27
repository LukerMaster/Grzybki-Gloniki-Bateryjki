#pragma once
#include "Object.h"

#include <iostream>
class Germ :
	public Object
{
protected:
	
public:
	float max_health, current_health;
	float max_age, current_age;
	float max_food, current_food;

	void UpdateStats(float dt);

	Germ(sf::Vector2i start_pos_, sf::Vector2i end_pos_, eObjType type_, sf::IntRect text_rect_, float max_age_, float max_health_, float max_food_, float curr_health_, float curr_food_);
	virtual void Step(float dt) = 0;
	
};

