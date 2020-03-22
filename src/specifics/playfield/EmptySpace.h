#pragma once
#include "Object.h"
class EmptySpace :
	public Object
{
public:
	EmptySpace(sf::Vector2i pos_, sf::Texture& texture_, sf::IntRect text_rect_);
	virtual void DoAI(float dt, std::vector<std::vector<Object>> objects);
	virtual void Draw(sf::RenderWindow& window);
};

