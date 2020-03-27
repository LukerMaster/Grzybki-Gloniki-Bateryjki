#pragma once
#include "Object.h"
#include "GermClasses.h"
#include "EmptySpace.h"
#include "Food.h"
#include "EventMgr.h"

#include <vector>
class Playfield
{
private:
	int size;
	std::vector<std::vector<int>> bg_textures;
public:
	EventMgr events;
	std::vector<std::vector<std::shared_ptr<Object>>> playfield;
	Playfield(int size_);

	bool AddGerm(eObjType type, sf::Vector2i start_pos, sf::Vector2i end_pos, float max_age = 100, float max_health = 100, float max_food = 100,  float current_health = 50, float current_food = 50);
	// Adds germ onto the playfield. If no space, does nothing.

	void AddFood(sf::Vector2i start_pos, sf::Vector2i end_pos, float food_value, int texture);
	// Adds food onto the playfield. texture means which texture is used in drawing. Currently range 0-3.
	bool AddGermRandom(eObjType type, float max_age, float max_health, float max_food, float current_health, float current_food);
	// Adds an object onto the playfield with random coordinates. If no space, returns false.

	sf::Vector2i CheckAroundFor(sf::Vector2i pos, eObjType searching);
	// Checks for an object of given type and returns absolute vector to that place.

	bool Move(sf::Vector2i from, sf::Vector2i to);
	// Moves an object on playfield. Returns coordinates to moved object. Returns false if target place occupied.

	void ForceMove(sf::Vector2i from, sf::Vector2i to);
	// Moves an object on playfield. Returns coordinates to moved object. Can replace some other object.
	// Also adds death event or eat event if something is replaced.

	bool Delete(sf::Vector2i pos);
	// Deletes an object and places an empty space.



	std::shared_ptr<Object> GetObj(sf::Vector2i pos);
	std::shared_ptr<Object> GetObj(int x, int y);

	std::shared_ptr<Food> GetFood(int x, int y);
	std::shared_ptr<Food> GetFood(sf::Vector2i pos);

	std::shared_ptr<Germ> GetGerm(sf::Vector2i pos);
	std::shared_ptr<Germ> GetGerm(int x, int y);

	std::shared_ptr<Algae> GetAlgae(sf::Vector2i pos);
	std::shared_ptr<Algae> GetAlgae(int x, int y);

	std::shared_ptr<Bacteria> GetBacteria(sf::Vector2i pos);
	std::shared_ptr<Bacteria> GetBacteria(int x, int y);

	std::shared_ptr<Shroom> GetShroom(sf::Vector2i pos);
	std::shared_ptr<Shroom> GetShroom(int x, int y);

	sf::IntRect GetRekt(int x, int y, int grid_size=4, int rect_size = 64); // Sorry, I had to. Btw. it's for getting texture rect of backgrounds.

	int GetSize();
};

