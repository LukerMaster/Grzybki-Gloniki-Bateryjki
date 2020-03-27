#pragma once
#include "Animation.h"
class DeathAnim :
	public Animation
{
	sf::Sprite body;
	sf::Vector2f start_pos;
	sf::Vector2f end_pos;
	sf::Vector2f scale;
public:
	DeathAnim(sf::Texture& germ_text, sf::IntRect text_rect, sf::Vector2f start_pos_, sf::Vector2f end_pos_, sf::Vector2f scale_, float length_)
		:body(germ_text, text_rect),
		start_pos(start_pos_),
		end_pos(end_pos_),
		scale(scale_),
		Animation(length_)
	{};

	void Draw(sf::RenderWindow& window)
	{
		body.setOrigin(body.getTextureRect().width / 2, body.getTextureRect().height / 2);
		body.setPosition(Lerp(start_pos.x, end_pos.x, current / (length * 2.0f)) + ((body.getTextureRect().width * scale.x) / 2), Lerp(start_pos.y, end_pos.y, current / (length * 2.0f)) + ((body.getTextureRect().height * scale.y) / 2));
		body.setScale({Lerp(1, 0, current / (length * 2.0f)), Lerp(1, 0, current / (length * 2.0f))});
		body.scale(scale);
		int opacity = 255 - Lerp(0, 255, current / length);
		body.setColor({ 255, 255, 255, (sf::Uint8)opacity });
		window.draw(body);
	}

};

