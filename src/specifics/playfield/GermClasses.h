#pragma once
#include "Germ.h"


class Algae :
	public Germ
{
public:
	Algae(sf::Vector2i pos_, sf::Texture& texture_, sf::IntRect text_rect_, int max_health_, int max_food_, int max_age_);
	virtual void DoAI(float dt, std::vector<std::vector<Object>> objects);
	virtual void Draw(sf::RenderWindow& window);
};

class Bacteria :
	public Germ
{
public:
	Bacteria(sf::Vector2i pos_, sf::Texture& texture_, sf::IntRect text_rect_, int max_health_, int max_food_, int max_age_);
	virtual void DoAI(float dt, std::vector<std::vector<Object>> objects);
	virtual void Draw(sf::RenderWindow& window);
};

class Shroom :
	public Germ
{
public:
	Shroom(sf::Vector2i pos_, sf::Texture& texture_, sf::IntRect text_rect_, int max_health_, int max_food_, int max_age_);
	virtual void DoAI(float dt, std::vector<std::vector<Object>> objects);
	virtual void Draw(sf::RenderWindow& window);
};