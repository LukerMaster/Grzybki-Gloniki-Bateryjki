#pragma once
#include "Germ.h"

class Algae :
	public Germ
{
public:
	Algae(sf::Vector2i start_pos_, sf::Vector2i end_pos_, sf::IntRect text_rect_, float max_age_, float max_health_, float max_food_, float curr_health_, float curr_food_);
	virtual void Step(float dt);
};

class Bacteria :
	public Germ
{
public:
	Bacteria(sf::Vector2i start_pos_, sf::Vector2i end_pos_, sf::IntRect text_rect_, float max_age_, float max_health_, float max_food_, float curr_health_, float curr_food_);
	virtual void Step(float dt);
};

class Shroom :
	public Germ
{
public:
	Shroom(sf::Vector2i start_pos_, sf::Vector2i end_pos_, sf::IntRect text_rect_, float max_age_, float max_health_, float max_food_, float curr_health_, float curr_food_);
	virtual void Step(float dt);
};