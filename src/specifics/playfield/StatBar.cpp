#include "StatBar.h"

StatBar::StatBar(sf::Font& font_)
	:max_health(1),
	max_food(1),
	max_energy(1),
	anim_health(1),
	anim_food(1),
	anim_energy(1),
	anim_age(0),
	age(100)
{
	name.setFont(font_);
	name.setCharacterSize(24);
	name.setFillColor({ 255, 100, 200, 255 });
	name.setOutlineColor(sf::Color::White);
	name.setOutlineThickness(4);

	age_text.setFont(font_);
	age_text.setCharacterSize(20);
	age_text.setFillColor({ 0, 100, 0, 255 });
	age_text.setOutlineColor(sf::Color::White);
	age_text.setOutlineThickness(4);
}

void StatBar::Step(float dt)
{
	float slowdown = 80.0f;
	anim_age += ((age - anim_age) / slowdown) * dt;

	anim_health += ((current_health - anim_health) / slowdown) * dt;
	anim_food += ((current_food - anim_food) / slowdown) * dt;
	anim_energy += ((current_energy - anim_energy) / slowdown) * dt;

	health_bar.setSize({ (anim_health / max_health) * 140, 20 });
	food_bar.setSize({ (anim_food / max_food) * 140, 20 });
	energy_bar.setSize({ (anim_energy / max_energy) * 140, 20 });

	health_bar.setFillColor({ 255, 0, 0, 255 });
	food_bar.setFillColor({ 155, 155, 0, 255 });
	energy_bar.setFillColor({ 100, 210, 255, 255 });

	health_bar.setPosition(bar.getPosition() - sf::Vector2f(289, 58));
	food_bar.setPosition(bar.getPosition() - sf::Vector2f(290, 37));
	energy_bar.setPosition(bar.getPosition() - sf::Vector2f(290, 17));
}

void StatBar::Create(sf::Texture& tex, sf::IntRect rect, sf::Vector2u pos, sf::Vector2u origin)
{
	bar.setTexture(tex);
	bar.setTextureRect(rect);
	bar.setOrigin(origin.x, origin.y);
	bar.setPosition(pos.x, pos.y);
}

void StatBar::SetStats(sf::Sprite sprite_,
	int age_,
	float max_health_,
	float current_health_,
	float max_food_,
	float current_food_,
	float max_energy_,
	float current_energy_,
	std::string name_)
{
	object_icon = sprite_;
	object_icon.setOrigin(object_icon.getTextureRect().height, object_icon.getTextureRect().width);
	object_icon.setScale(1, 1);
	object_icon.setPosition(bar.getPosition());

	name.setString(name_);
	name.setPosition(bar.getPosition() - sf::Vector2f(289, 90));

	age = age_;

	std::stringstream ss;
	ss.precision(1);
	ss << std::fixed;
	ss << anim_age;

	age_text.setString("Wiek:\n  " + ss.str());
	age_text.setPosition(bar.getPosition() - sf::Vector2f(147, 51));

	max_health = max_health_;
	max_food = max_food_;
	max_energy = max_energy_;

	current_health = current_health_;
	current_food = current_food_;
	current_energy = current_energy_;
}
void StatBar::Draw(sf::RenderWindow& window)
{
	window.draw(health_bar);
	window.draw(food_bar);
	window.draw(energy_bar);
	window.draw(bar);
	window.draw(name);
	window.draw(object_icon);
	window.draw(age_text);
};