#pragma once
#include "Animation.h"

#include <iostream>
class PopUp : public Animation
{
	sf::Sprite icon;
	sf::Vector2i pos;
	sf::Vector2f scale;
public:
	PopUp(sf::Texture& icon_, sf::IntRect icon_rect_, sf::Vector2f pos_, sf::Vector2f scale_, float length_) // length in milliseconds.
		:icon(icon_, icon_rect_),
		pos(pos_),
		scale(scale_),
		Animation(length_)
	{};

	/*void Step(float dt)
	{
		current += dt;
	}
	*/
	void Draw(sf::RenderWindow& window)
	{
		float px = pos.x;
		float py = Lerp(pos.y, pos.y - window.getSize().y * 0.03f, current / length);
		float opacity = Lerp(0, 255, current / (length * 0.3f));

		if (current / length > 0.7f)
			opacity = 255 - Lerp(0, 255, (current/length - 0.7f) / 0.3f );

		icon.setOrigin(icon.getTextureRect().width / 2, icon.getTextureRect().height / 2);
		icon.setPosition(px + ((icon.getTextureRect().getSize().x * scale.x) / 2), py + ((icon.getTextureRect().getSize().x * scale.x) / 2));
		icon.setScale({ 0.5f, 0.5f });
		icon.setColor({ 255, 255, 255, (sf::Uint8)opacity });
		window.draw(icon);
	}
};

