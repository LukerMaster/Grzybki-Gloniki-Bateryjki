#include "Germ.h"

Germ::Germ(sf::Vector2i pos_, sf::Texture& texture_, sf::IntRect text_rect_, int max_health_, int max_food_, int max_age_)
	:Object(eObjType::Germ, pos_,texture_, text_rect_),
	max_age(max_age_),
	max_health(max_health_),
	max_food(max_food_),
	current_age(0),
	current_health(max_health),
	current_food(max_food)
{
}
