#include "Button.h"

sf::Color Button::_GetShiftedColor(const sf::Color& current, sf::Color target, int speed)
{
	sf::Color returned = current; // This is because sf::getFillColor() only returns const&.

	if (abs(returned.r - target.r) < speed) returned.r = target.r;
	if (abs(returned.g - target.g) < speed) returned.g = target.g;
	if (abs(returned.b - target.b) < speed) returned.b = target.b;
	if (abs(returned.a - target.a) < speed) returned.a = target.a;

	if (returned.r > target.r) returned.r -= speed;
	if (returned.r < target.r) returned.r += speed;

	if (returned.g > target.g) returned.g -= speed;
	if (returned.g < target.g) returned.g += speed;

	if (returned.b > target.b) returned.b -= speed;
	if (returned.b < target.b) returned.b += speed;

	if (returned.a > target.a) returned.a -= speed;
	if (returned.a < target.a) returned.a += speed;
	return returned;
}

bool Button::_IsPointInRect(sf::Vector2i pt, sf::RectangleShape rect)
{
	if (pt.x > rect.getPosition().x&& pt.x < rect.getPosition().x + rect.getSize().x
		&& pt.y > rect.getPosition().y&& pt.y < rect.getPosition().y + rect.getSize().y)
		return true;
	else
		return false;
}


void Button::_Resize()
{
	hitBox.setSize({ size.x * window_size.x, size.y * window_size.y });
	hitBox.setPosition({ pos.x * window_size.x, pos.y * window_size.y });
	label.setPosition({ pos.x * window_size.x, pos.y * window_size.y });
	label.setCharacterSize(size.y * window_size.y * 0.8f);
}

//
//
//
// User functions below
//
//
//


Button::Button(sf::Vector2u window_size_, sf::Vector2f pos_, sf::Vector2f size_, std::string text, sf::Font& font, sf::SoundBuffer& HoverSound, sf::SoundBuffer& ClickSound, std::string description)
{
	size = size_;
	pos = pos_;
	window_size = window_size_;
	_clicked = false;

	_Resize();

	label.setString(text);
	
	label.setFont(font);
	
	label.setOutlineColor({ 255, 255, 255, 255 });
	label.setOutlineThickness(4);
	desc.setString(description);

	SetColors();
	hitBox.setFillColor(baseColor);

	_prevMousePressed = false;
	_prevHovered = false;

	hoverSound.setBuffer(HoverSound);
	clickSound.setBuffer(ClickSound);
}

void Button::Update(float dt, sf::Vector2i mouse_pos, sf::Vector2u window_size_)
{
	window_size = window_size_;
	_Resize();

	if (_IsPointInRect(mouse_pos, hitBox))
	{
		if (!_prevHovered)
			hoverSound.play();
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && _prevMousePressed)
		{
			clickSound.play();
			_clicked = true;
		}
		hitBox.setFillColor(_GetShiftedColor(hitBox.getFillColor(), hlColor, 9 * dt * 0.3f));
		label.setFillColor(_GetShiftedColor(label.getFillColor(), hlTextColor, 4 * dt * 0.3f));
		
		_prevHovered = true;
	}
	else
	{
		hitBox.setFillColor(_GetShiftedColor(hitBox.getFillColor(), baseColor, 3 * dt * 0.3f));
		label.setFillColor(_GetShiftedColor(label.getFillColor(), baseTextColor, 6 * dt * 0.3f));
		_prevHovered = false;
	}
	_IsPointInRect(mouse_pos, hitBox) ? _prevHovered = true : _prevHovered = false;
	sf::Mouse::isButtonPressed(sf::Mouse::Left) ? _prevMousePressed = true : _prevMousePressed = false;
}

void Button::SetColors(sf::Color hlButton, sf::Color hlText, sf::Color button, sf::Color text) // 
{
	baseColor = button;
	baseTextColor = text;
	hlColor = hlButton;
	hlTextColor = hlText;
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(hitBox);
	window.draw(label);
}

bool Button::isClicked()
{
	return _clicked;
		
}

void Button::Unclick()
{
	_clicked = false;
}

bool Button::CheckAndUnclick()
{
	if (_clicked)
	{
		_clicked = false;
		return true;
	}
	else
		return false;
}
