#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
class Animation // Interface for animations.
{
protected:
	float current;
	float length;
	bool is_looped;
public:
	Animation(float length_, bool is_looped_ = false)
		:length(length_),
		is_looped(is_looped_),
		current(0) {} ;

	float Lerp(float a, float b, float percent)
	{
			if (percent > 1.0f) percent = 1.0f;
			return ((b - a) * percent) + a;
		
	}

	virtual void Step(float dt)
	{
		current += dt;
	};

	virtual void Draw(sf::RenderWindow& window) = 0;
	
	bool IsDone()
	{
		if (!is_looped)
		{
			if (current >= length)
				return true;
			else
				return false;
		}
		return false;
	}
	
	bool IsLooped()
	{
		return is_looped;
	}
};

