#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>

class Button
{
private:
	bool _clicked;
	bool _prevMousePressed;
	bool _prevHovered;
protected:
	sf::Color _GetShiftedColor(const sf::Color& current, sf::Color target, int speed = 1);
	bool _IsPointInRect(sf::Vector2i pt, sf::RectangleShape rect);
	void _Resize();
public:
	Button(sf::Vector2u window_size_, sf::Vector2f pos_, sf::Vector2f size_, std::string text, sf::Font& font, sf::SoundBuffer& hoverSound, sf::SoundBuffer& clickSound, std::string description);
	// Button that can be pressed. Use pos and size as parameter between 0 and 1.

	sf::Vector2u window_size;
	sf::Vector2f pos;
	sf::Vector2f size;

	sf::Sound hoverSound;
	sf::Sound clickSound;
	sf::Text label;
	sf::RectangleShape hitBox;
	sf::Text desc; // Description.
	sf::Color baseColor, hlColor;
	sf::Color baseTextColor, hlTextColor;
	void Update(float dt, sf::Vector2i mouse_pos, sf::Vector2u window_size_);
	void SetColors(sf::Color hlButton = { 255, 100, 40 }, sf::Color hlText = { 0, 0, 0 }, sf::Color button = { 0, 0, 0, 0 }, sf::Color text = {255, 255, 255});
	void Draw(sf::RenderWindow& window);
	bool isClicked(); // Remember to Unclick(); if you use this method or use CheckAndUnclick();
	void Unclick();
	bool CheckAndUnclick(); // Returns true if button is clicked and automatically unclicks.
};

