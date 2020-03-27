#include "Playfield.h"

Playfield::Playfield(int size_)
	:size(size_)
{
	for (int x = 0; x < size; x++)
	{
		playfield.push_back(std::vector<std::shared_ptr<Object>>());
		bg_textures.push_back(std::vector<int>());
		for (int y = 0; y < size; y++)
		{
			int chosen_texture = 0;
			if (rand() % 15 == 0) chosen_texture = rand() % 16;    // Make more grass spaces than decorations.
			else				  chosen_texture = rand() % 4 + 12;
			bg_textures[x].push_back(chosen_texture);
			playfield[x].push_back(std::make_shared<EmptySpace>());
		}
	}
}

bool Playfield::AddGerm(eObjType type, sf::Vector2i start_pos, sf::Vector2i actual_pos, float max_age, float max_health, float max_food, float current_health, float current_food)
{
	if (playfield[actual_pos.x][actual_pos.y]->type == eObjType::EmptySpace)
	{
		if (type == eObjType::Algae)
			playfield[actual_pos.x][actual_pos.y] = std::make_shared<Algae>(Algae({ start_pos.x, start_pos.y }, { actual_pos.x, actual_pos.y}, { rand() % 3 * 64, 0, 64, 64 }, max_age, max_health, max_food, current_health, current_food));
		else if (type == eObjType::Bacteria)
			playfield[actual_pos.x][actual_pos.y] = std::make_shared<Bacteria>(Bacteria({ start_pos.x, start_pos.y }, { actual_pos.x, actual_pos.y }, { rand() % 3 * 64, 64, 64, 64 }, max_age, max_health, max_food, current_health, current_food));
		else if (type == eObjType::Shroom)
			playfield[actual_pos.x][actual_pos.y] = std::make_shared<Shroom>(Shroom({ start_pos.x, start_pos.y }, { actual_pos.x, actual_pos.y }, { rand() % 3 * 64, 128, 64, 64 }, max_age, max_health, max_food, current_health, current_food));

		return true;
	}
	else return false;
}

void Playfield::AddFood(sf::Vector2i start_pos, sf::Vector2i actual_pos, float food_value, int texture)
{
	if (playfield[actual_pos.x][actual_pos.y]->type == eObjType::EmptySpace)
	{
		playfield[actual_pos.x][actual_pos.y] = std::make_shared<Food>(Food({ start_pos.x, start_pos.y}, { actual_pos.x, actual_pos.y }, { texture % 2 * 64, texture / 2 * 64, 64, 64 }, food_value));
	}
}

bool Playfield::AddGermRandom(eObjType type, float max_age, float max_health, float max_food, float current_health, float current_food)
{
	bool isSpace = false;
	sf::Vector2i pos;

	int max_tries = 20;

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (playfield[x][y]->type == eObjType::EmptySpace)
			{
				isSpace = true;
			}
		}
	}
	if (isSpace)
	{
		for (int i = 0; i <= max_tries; i++)
		{
			pos = { rand() % size, rand() % size };
			if (type == eObjType::Algae || type == eObjType::Shroom || type == eObjType::Bacteria)
			{
				if (AddGerm(type, pos, pos, max_age, max_health, max_food, current_health, current_food) == true)
					return true;
			}
				
			if (i == max_tries) // Basically - If it tried 10 times and still no space. Forget it, linearlly search for space.
			{
				for (int x = 0; x < size; x++)
				{
					for (int y = 0; y < size; y++)
					{
						if (playfield[x][y])
						{
							if (AddGerm(type, { x, y }, { x, y }, max_age, max_health, max_food, current_health, current_food) == true)
								return true;
						}
					}
				}
			}
		}
	}
	else return false;
}

sf::Vector2i Playfield::CheckAroundFor(sf::Vector2i pos, eObjType searching)
{
	std::vector<sf::Vector2i> spaces;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			int pos_x = pos.x + x;
			int pos_y = pos.y + y;

			if (pos_x >= (int)playfield.size())    pos_x = playfield.size() - 1;
			if (pos_x < 0) pos_x = 0;
			if (pos_y >= (int)playfield[pos_x].size()) pos_y = playfield[pos_x].size() - 1;
			if (pos_y < 0) pos_y = 0;


			if (playfield[pos_x][pos_y]->type == searching)
				spaces.push_back({ pos_x, pos_y });
		}
	}

	if (spaces.size() != 0)
	{
		int i = rand() % spaces.size();
		return spaces[i];
	}
	else return pos;
}

void Playfield::ForceMove(sf::Vector2i from, sf::Vector2i to)
{
	// Adding death event.
	if (playfield[to.x][to.y]->type != eObjType::EmptySpace)
	{
		events.AddDeath(eDeathType::eaten, GetObj(to), GetGerm(from));
		playfield[to.x][to.y]->dead = true;
	}
		

	// Doing logic.
	playfield[to.x][to.y] = playfield[from.x][from.y];
	playfield[to.x][to.y]->end_pos = { to.x, to.y };
	playfield[from.x][from.y] = std::make_shared<EmptySpace>();
}

bool Playfield::Move(sf::Vector2i from, sf::Vector2i to)
{
	if (playfield[to.x][to.y]->type == eObjType::EmptySpace)
	{
		ForceMove(from, to);
		return true;
	}
	return false;
}

bool Playfield::Delete(sf::Vector2i pos)
{
	if (playfield[pos.x][pos.y]->type != eObjType::EmptySpace)
	{
		playfield[pos.x][pos.y] = std::make_shared<EmptySpace>();
		return true;
	}
	return false;
}


std::shared_ptr<Object> Playfield::GetObj(sf::Vector2i pos)
{
	return playfield[pos.x][pos.y];
}

std::shared_ptr<Object> Playfield::GetObj(int x, int y)
{
	return playfield[x][y];
}

std::shared_ptr<Food> Playfield::GetFood(int x, int y)
{
	return std::static_pointer_cast<Food>(playfield[x][y]);
}

std::shared_ptr<Food> Playfield::GetFood(sf::Vector2i pos)
{
	return std::static_pointer_cast<Food>(playfield[pos.x][pos.y]);
}

std::shared_ptr<Germ> Playfield::GetGerm(sf::Vector2i pos)
{
	return std::static_pointer_cast<Germ>(playfield[pos.x][pos.y]);
}

std::shared_ptr<Germ> Playfield::GetGerm(int x, int y)
{
	return std::static_pointer_cast<Germ>(playfield[x][y]);
}

std::shared_ptr<Algae> Playfield::GetAlgae(sf::Vector2i pos)
{
	return std::static_pointer_cast<Algae>(playfield[pos.x][pos.y]);
}

std::shared_ptr<Algae> Playfield::GetAlgae(int x, int y)
{
	return std::static_pointer_cast<Algae>(playfield[x][y]);
}

std::shared_ptr<Bacteria> Playfield::GetBacteria(sf::Vector2i pos)
{
	return std::static_pointer_cast<Bacteria>(playfield[pos.x][pos.y]);
}

std::shared_ptr<Bacteria> Playfield::GetBacteria(int x, int y)
{
	return std::static_pointer_cast<Bacteria>(playfield[x][y]);
}

std::shared_ptr<Shroom> Playfield::GetShroom(sf::Vector2i pos)
{
	return std::static_pointer_cast<Shroom>(playfield[pos.x][pos.y]);
}

std::shared_ptr<Shroom> Playfield::GetShroom(int x, int y)
{
	return std::static_pointer_cast<Shroom>(playfield[x][y]);
}

sf::IntRect Playfield::GetRekt(int x, int y, int grid_size, int rect_size)
{
	return { bg_textures[x][y] % grid_size * rect_size, bg_textures[x][y] / grid_size * rect_size, rect_size, rect_size };
}

int Playfield::GetSize()
{
	return size;
}
