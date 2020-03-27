#pragma once
#include "SFML/Graphics.hpp"
#include <sstream>
#include <iomanip>

#include <iostream>
class StatBar
{
	float max_health;
	float max_food;
	float max_energy;

	float current_health;
	float current_food;
	float current_energy;

	float anim_health;
	float anim_food;
	float anim_energy;

	float age;
	float anim_age;

	sf::Sprite bar;
	sf::Sprite object_icon;

	sf::RectangleShape health_bar;
	sf::RectangleShape food_bar;
	sf::RectangleShape energy_bar;

	sf::Text text_health;
	sf::Text text_food;
	sf::Text text_energy;

	sf::Text name;
	sf::Text age_text;

public:

	StatBar(sf::Font& font_);

	void Step(float dt);
	void Create(sf::Texture& tex, sf::IntRect rect, sf::Vector2u pos, sf::Vector2u origin);
	void SetStats(sf::Sprite sprite_,
		int age_,
		float max_health_,
		float current_health_,
		float max_food_,
		float current_food_,
		float max_energy_,
		float current_energy_,
		std::string name_);

	void Draw(sf::RenderWindow& window);

};

