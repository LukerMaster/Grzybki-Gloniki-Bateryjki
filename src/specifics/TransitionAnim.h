#pragma once
#include "SFML/Graphics.hpp"

class BubbleParticle
{
	sf::Sprite sprite;
	int lifetime;
};

class TransitionAnim
{
	std::vector<sf::Sprite> bubbles;
	TransitionAnim();
};

