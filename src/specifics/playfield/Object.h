#pragma once
#include "SFML/Graphics.hpp"
enum class eObjType
{
	EmptySpace,
	Food,
	Algae,
	Bacteria,
	Shroom
};

class Object
{
public:
	sf::Sprite sprite;
	eObjType type;
	sf::Vector2i start_pos;
	// Position at the beginning of the round. For DRAWING ONLY.
	bool AI_done;
	// After each iteration of AI this is set to true to avoid doing AI twice.
	bool dead;

	sf::Vector2i end_pos;
	// Position at the end of the round. For DRAWING ONLY.

	Object(eObjType type_, sf::Vector2i start_pos_,sf::Vector2i end_pos_, sf::IntRect text_rect_ = { 0, 0, 64, 64 });
	virtual void Step(float dt) = 0;

};

