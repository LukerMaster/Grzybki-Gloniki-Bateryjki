#include "Object.h"


Object::Object(eObjType type_, sf::Vector2i pos_, sf::Texture& texture_, sf::IntRect text_rect_)
	:type(type_),
	pos(pos_),
	sprite(texture_, text_rect_)
{
}
