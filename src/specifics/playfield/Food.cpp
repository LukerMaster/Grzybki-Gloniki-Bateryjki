#include "Food.h"

Food::Food(sf::Vector2i start_pos_, sf::Vector2i end_pos_, sf::IntRect text_rect_, float food_value_)
	:Object(eObjType::Food, start_pos_, end_pos_, text_rect_),
	food_value(food_value_)
{
	
}

void Food::Step(float dt)
{
}
