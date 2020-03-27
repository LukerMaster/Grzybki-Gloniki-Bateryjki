#include "Object.h"


Object::Object(eObjType type_, sf::Vector2i start_pos_, sf::Vector2i end_pos_, sf::IntRect text_rect_)
	:type(type_),
	start_pos(start_pos_),
	end_pos(end_pos_),
	AI_done(true),
	dead(false)
{
	sprite.setTextureRect(text_rect_);
}
