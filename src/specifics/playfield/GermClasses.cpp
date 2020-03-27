#include "GermClasses.h"

// ALGAE
Algae::Algae(sf::Vector2i start_pos_, sf::Vector2i end_pos_, sf::IntRect text_rect_, float max_age_, float max_health_, float max_food_, float curr_health_, float curr_food_)
	:Germ(start_pos_, end_pos_, eObjType::Algae, text_rect_, max_age_, max_health_, max_food_, curr_health_, curr_food_)
{
}

void Algae::Step(float dt)
{
	UpdateStats(dt);
}

// BACTERIA
Bacteria::Bacteria(sf::Vector2i start_pos_, sf::Vector2i end_pos_, sf::IntRect text_rect_, float max_health_, float max_food_, float max_age_, float curr_health_, float curr_food_)
	:Germ(start_pos_, end_pos_, eObjType::Bacteria, text_rect_, max_health_, max_food_, max_age_, curr_health_, curr_food_)
{

}

void Bacteria::Step(float dt)
{
	UpdateStats(dt);
}


// SHROOM
Shroom::Shroom(sf::Vector2i start_pos_, sf::Vector2i end_pos_, sf::IntRect text_rect_, float max_age_, float max_health_, float max_food_, float curr_health_, float curr_food_)
	:Germ(start_pos_, end_pos_, eObjType::Shroom , text_rect_, max_age_, max_health_, max_food_, curr_health_, curr_food_)
{
}

void Shroom::Step(float dt)
{
	UpdateStats(dt);
}
