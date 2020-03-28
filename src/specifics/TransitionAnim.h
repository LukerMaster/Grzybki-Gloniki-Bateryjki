#pragma once
#include "SFML/Graphics.hpp"

class TransitionAnim
{
	float curr_time;
	float length;
	bool is_playing;

	sf::Vector2i window_size;
	std::vector<sf::Sprite> bubbles;
	std::vector<sf::Sprite> planks;
public:
	TransitionAnim(sf::Texture& bubble, sf::Texture& plank, float length_, sf::Vector2u window_size_);

	void Start();
	void Step(float dt);

	float GetPercentage();

	void Draw(sf::RenderWindow& window);


	float Lerp(float a, float b, float percent);

};

