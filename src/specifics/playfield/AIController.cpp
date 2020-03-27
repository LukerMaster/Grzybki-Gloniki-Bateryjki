#include "AIController.h"

void AIController::AlgaeAI(sf::Vector2i pawn_pos, Playfield& env)
{
	std::shared_ptr<Algae> pawn = env.GetAlgae(pawn_pos);

	pawn->AI_done = true; // For other classes to know that AI is done for this round.

	if (pawn->current_food > pawn->max_food * 0.8f && rand()%2) // DIVISION
	{
		sf::Vector2i spawn_point = env.CheckAroundFor(pawn_pos, eObjType::EmptySpace);
			if (spawn_point != pawn_pos)
			{
				env.AddGerm(eObjType::Algae,
					pawn_pos,
					spawn_point,
					pawn->max_age - 10 + (rand() % 21),
					100,
					100,
					pawn->current_health / 2,
					pawn->current_food / 2);

				pawn->current_health /= 2;
				pawn->current_food /= 2;
			}
	}
	else if (pawn->current_food < pawn->max_food) // PHOTOSYNTHESIS
	{
		pawn->current_food += 25;
	}

	if (pawn->current_health < pawn->max_health && pawn->current_food > pawn->max_food * 0.5f) // SELF-HEALING
	{
		pawn->current_food -= 2;
		pawn->current_health += 1;
	}

	pawn->UpdateStats(1);
}

void AIController::BacteriaAI(sf::Vector2i pawn_pos, Playfield& env)
{
	std::shared_ptr<Bacteria> pawn = env.GetBacteria(pawn_pos);

	pawn->AI_done = true;

	if (pawn->current_food > pawn->max_food * 0.8f && rand() % 2) // DIVISION
	{
		sf::Vector2i spawn_point = env.CheckAroundFor(pawn_pos, eObjType::EmptySpace);
		if (spawn_point != pawn_pos)
		{
			env.AddGerm(eObjType::Bacteria,
				pawn_pos,
				spawn_point,
				pawn->max_age - 10 + (rand() % 21),
				100,
				100,
				pawn->current_health / 2,
				pawn->current_food / 2);

			pawn->current_health /= 2;
			pawn->current_food /= 2;
		}
	}
	else
	{
		sf::Vector2i food_pos = env.CheckAroundFor(pawn_pos, eObjType::Algae);

		if (food_pos != pawn_pos)
		{
			if (rand() % 11 > 6)
			{
				pawn->current_food += env.GetGerm(food_pos)->current_food;

				env.ForceMove(pawn_pos, food_pos);
				pawn = env.GetBacteria(food_pos);
			}
			else
			{
				sf::Vector2i new_pos = env.CheckAroundFor(pawn_pos, eObjType::EmptySpace);
				if (env.Move(pawn_pos, new_pos))
					pawn = env.GetBacteria(new_pos);
			}
				
		}
		else
		{
			food_pos = env.CheckAroundFor(pawn_pos, eObjType::Bacteria);

			if (food_pos != pawn_pos)
			{
				if (rand() % 11 > 7)
				{
					pawn->current_food += env.GetGerm(food_pos)->current_food;
					env.ForceMove(pawn_pos, food_pos);
					pawn = env.GetBacteria(food_pos);
				}
			}
			else
			{
				sf::Vector2i new_pos = env.CheckAroundFor(pawn_pos, eObjType::EmptySpace);
				if (env.Move(pawn_pos, new_pos))
					pawn = env.GetBacteria(new_pos);
			}
		}	
	}
	pawn->UpdateStats(1);
}

void AIController::ShroomAI(sf::Vector2i pawn_pos, Playfield& env)
{
	std::shared_ptr<Shroom> pawn = env.GetShroom(pawn_pos);

	pawn->AI_done = true;

	if (pawn->current_food > pawn->max_food * 0.8f && rand() % 2) // DIVISION
	{
		sf::Vector2i spawn_point = env.CheckAroundFor(pawn_pos, eObjType::EmptySpace);
		if (spawn_point != pawn_pos)
		{
			env.AddGerm(eObjType::Shroom,
				pawn_pos,
				spawn_point,
				pawn->max_age - 10 + (rand() % 21),
				100,
				100,
				pawn->current_health / 2,
				pawn->current_food / 2);

			pawn->current_health /= 2;
			pawn->current_food /= 2;
		}
	}
	else
	{
		sf::Vector2i food_pos = env.CheckAroundFor(pawn_pos, eObjType::Food);
		if (pawn_pos != food_pos)
		{
			if (rand() % 2)
			{
				pawn->current_food += env.GetFood(food_pos)->food_value;

				env.ForceMove(pawn_pos, food_pos);
				pawn = env.GetShroom(food_pos);
			}
		}
		else
		{
			sf::Vector2i new_pos = env.CheckAroundFor(pawn_pos, eObjType::EmptySpace);
			if (env.Move(pawn_pos, new_pos))
				pawn = env.GetShroom(new_pos);
		}
	}
	pawn->UpdateStats(1);
}

void AIController::Decide(sf::Vector2i pawn_pos, Playfield& env)
{
	if (!env.GetObj(pawn_pos)->AI_done)
	{
		if (env.GetObj(pawn_pos)->type == eObjType::Algae)
			AlgaeAI(pawn_pos, env);
		if (env.GetObj(pawn_pos)->type == eObjType::Bacteria)
			BacteriaAI(pawn_pos, env);
		if (env.GetObj(pawn_pos)->type == eObjType::Shroom)
			ShroomAI(pawn_pos, env);
	}
}

void AIController::EnableAI(Playfield& env)
{
	for (int x = 0; x < env.GetSize(); x++)
	{
		for (int y = 0; y < env.GetSize(); y++)
		{
			env.GetObj(x, y)->AI_done = false;
		}
	}
}

void AIController::ResetAnimPositions(Playfield& env)
{
	for (int x = 0; x < env.GetSize(); x++)
	{
		for (int y = 0; y < env.GetSize(); y++)
		{
			env.GetObj(x, y)->start_pos = env.GetObj(x, y)->end_pos;
		}
	}
}

void AIController::CheckForDead(Playfield& env)
{
	for (int x = 0; x < env.GetSize(); x++)
	{
		for (int y = 0; y < env.GetSize(); y++)
		{
			if (env.GetObj(x, y)->type == eObjType::Algae || env.GetObj(x, y)->type == eObjType::Shroom || env.GetObj(x, y)->type == eObjType::Bacteria)
			{
				if (env.GetGerm(x, y)->current_health <= 0)
				{
					if (env.GetGerm(x, y)->current_food <= 0)
					{
						env.events.AddDeath(eDeathType::starved, env.GetGerm(x, y));
					}
					else if (env.GetGerm(x, y)->current_age > env.GetGerm(x, y)->max_age)
					{
						env.events.AddDeath(eDeathType::old_age, env.GetGerm(x, y));
					}

					float food_val = env.GetGerm(x, y)->current_food + 50;
					
					int tex_rect = (food_val / 25) - 2;
					if (tex_rect > 3) tex_rect = 3;

					env.Delete({ x, y });
					env.AddFood({ x, y }, { x ,y }, food_val, tex_rect);
				}
			}
		}
	}
}
