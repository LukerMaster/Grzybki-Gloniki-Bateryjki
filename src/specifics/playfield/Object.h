#pragma once
#include "SFML/Graphics.hpp"
enum class eObjType
{
	Space,
	Germ,
	Food
};

class Object
{
public:
	sf::Sprite sprite;
	eObjType type;
	sf::Vector2i pos;
	Object(eObjType type_, sf::Vector2i pos_, sf::Texture& texture_, sf::IntRect text_rect_);
	virtual void DoAI(float dt, std::vector<std::vector<Object>> objects) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
};

