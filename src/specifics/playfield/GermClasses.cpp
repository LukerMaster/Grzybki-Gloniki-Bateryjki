#include "GermClasses.h"

// ALGAE
Algae::Algae(sf::Vector2i pos_, sf::Texture& texture_, sf::IntRect text_rect_, int max_health_, int max_food_, int max_age_)
	:Germ(pos_, texture_, text_rect_, max_health_, max_food_, max_age_)
{
}

void Algae::DoAI(float dt, std::vector<std::vector<Object>> objects)
{
}

void Algae::Draw(sf::RenderWindow& window)
{
}

// BACTERIA
Bacteria::Bacteria(sf::Vector2i pos_, sf::Texture& texture_, sf::IntRect text_rect_, int max_health_, int max_food_, int max_age_)
	:Germ(pos_, texture_, text_rect_, max_health_, max_food_, max_age_)
{
}

void Bacteria::DoAI(float dt, std::vector<std::vector<Object>> objects)
{
}

void Bacteria::Draw(sf::RenderWindow& window)
{
}

// SHROOM
Shroom::Shroom(sf::Vector2i pos_, sf::Texture& texture_, sf::IntRect text_rect_, int max_health_, int max_food_, int max_age_)
	:Germ(pos_, texture_, text_rect_, max_health_, max_food_, max_age_)
{
}

void Shroom::DoAI(float dt, std::vector<std::vector<Object>> objects)
{
}

void Shroom::Draw(sf::RenderWindow& window)
{
}
