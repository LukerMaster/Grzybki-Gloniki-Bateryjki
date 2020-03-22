#pragma once
#include "Object.h"
class Germ :
	public Object
{
public:
	int max_health, current_health;
	int max_age, current_age;
	int max_food, current_food;

	Germ(sf::Vector2i pos_, sf::Texture& texture_, sf::IntRect text_rect_, int max_health_, int max_food_, int max_age_);
	virtual void DoAI(float dt, std::vector<std::vector<Object>> objects) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

};

