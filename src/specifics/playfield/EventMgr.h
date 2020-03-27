#pragma once
#include "GermClasses.h"
#include "Food.h"

enum class eDeathType
{
	starved,
	eaten,
	old_age
};

struct DeathData
{
	std::shared_ptr<Object> dead;
	std::shared_ptr<Germ> killer;
	eDeathType cause;
	DeathData(eDeathType cause_, std::shared_ptr<Object> dead_, std::shared_ptr<Germ> killer_)
		:cause(cause_),
		dead(dead_),
		killer(killer_) {};

};

struct FoodEatData
{
	std::shared_ptr<Food> food;
	std::shared_ptr<Germ> eater;

	FoodEatData(std::shared_ptr<Food> food_, std::shared_ptr<Germ> eater_)
		:food(food_),
		eater(eater_) {};
};

class EventMgr // Class purely for getting information. No logics/calculations done here.
{
	std::vector<DeathData> deaths;
public:

	DeathData& GetDeath();

	void AddDeath(eDeathType cause_, std::shared_ptr<Object> dead_, std::shared_ptr<Germ> killer_ = nullptr);
	void RemoveLastDeath();
	void ClearDeaths();
	bool AreStillDeaths();

};

