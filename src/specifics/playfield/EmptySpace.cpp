#include "EmptySpace.h"

EmptySpace::EmptySpace(sf::Vector2i pos_, sf::Texture& texture_, sf::IntRect text_rect_)
	:Object(eObjType::Space, pos_, texture_, text_rect_)
{

}

void EmptySpace::DoAI(float dt, std::vector<std::vector<Object>> objects)
{
}

void EmptySpace::Draw(sf::RenderWindow& window)
{
}
