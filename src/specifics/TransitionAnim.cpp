#include "TransitionAnim.h"

TransitionAnim::TransitionAnim(sf::Texture& bubble_tex, sf::Texture& plank_tex, float length_, sf::Vector2u window_size_)
	:curr_time(0),
	length(length_),
	is_playing(true),
	window_size(window_size_)
{
	int bubble_cnt = rand() % 10 + 500;
	for (int i = 0; i < bubble_cnt; i++)
	{
		bubbles.push_back(sf::Sprite(bubble_tex));
		float size = 1.0f * (rand() % 10 * 0.2f);
		bubbles[i].setScale(size, size);
		bubbles[i].setPosition(rand() % (int)(window_size.x - bubble_tex.getSize().x * bubbles[i].getScale().x), window_size.y + rand() % window_size.y * 0.2f);
		bubbles[i].setColor(sf::Color(rand() % 155 + 100, rand() % 155 + 100, rand() % 155 + 100, 55 ));
	}
	int plank_cnt = 6;
	for (int i = 0; i < plank_cnt; i++)
	{
		planks.push_back(sf::Sprite(plank_tex));
		planks[i].setScale(1.5f * (window_size.x / (float)planks[i].getTexture()->getSize().x), 1.0f * ((window_size.y/(float)plank_cnt) / (float)planks[i].getTexture()->getSize().y));
	}
	
}

void TransitionAnim::Start()
{
	if (!is_playing)
	{
		curr_time = 0;
		is_playing = true;
	}
	
}

void TransitionAnim::Step(float dt)
{
	curr_time += dt;
	for (int i = 0; i < planks.size(); i++)
	{
		planks[i].setPosition({
			Lerp(-(float)planks[i].getTexture()->getSize().x * planks[i].getScale().x - ((0.1f * window_size.x) * i), (float)window_size.x, (curr_time * curr_time) / (length * length)),
			(i / (float)(planks.size())) * window_size.y});
	}
	for (int i = 0; i < bubbles.size(); i++)
	{
		bubbles[i].setPosition({
			bubbles[i].getPosition().x,
			Lerp(window_size.y * 1.5f + (i * (window_size.y * 0.001f)), -window_size.y * 0.2f - (i * (window_size.y * 0.02f)), curr_time / length)
			});
	}

	if (curr_time >= length)
	{
		is_playing = false;
	}
}

float TransitionAnim::GetPercentage()
{
	return (curr_time / length);
}

void TransitionAnim::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < planks.size(); i++)
	{
		window.draw(planks[i]);
	}
	for (int i = 0; i < bubbles.size(); i++)
	{
		window.draw(bubbles[i]);
	}
}

float TransitionAnim::Lerp(float a, float b, float percent)
{
	if (percent > 1.0f) percent = 1.0f;
	return ((b - a) * percent) + a;
}
