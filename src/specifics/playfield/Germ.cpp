#include "Germ.h"


void Germ::UpdateStats(float dt)
{
	if (current_age > max_age)
	{
		max_health -= dt * (rand() % 10);
	}

	if (current_health > max_health) current_health = max_health;
	if (current_health < 0) current_health = 0;
	if (current_food > max_food) current_food = max_food;
	if (current_food <= 0) { current_health -= dt * 5; current_food = 0; }

	current_age += dt;
	current_food -= dt;
}

Germ::Germ(sf::Vector2i start_pos_, sf::Vector2i end_pos_, eObjType type_, sf::IntRect text_rect_, float max_age_ = 100, float max_health_ = 100, float max_food_ = 100, float curr_health_ = 50, float curr_food_ = 50)
	:Object(type_, start_pos_, end_pos_, text_rect_),
	max_age(max_age_),
	max_health(max_health_),
	max_food(max_food_),
	current_age(0),
	current_health(curr_health_),
	current_food(curr_food_)
{
}
