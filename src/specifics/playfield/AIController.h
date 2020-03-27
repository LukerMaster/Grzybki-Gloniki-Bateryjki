#pragma once
#include "Playfield.h"
#include "Object.h"
class AIController
{
	void AlgaeAI(sf::Vector2i pawn, Playfield& env);
	void BacteriaAI(sf::Vector2i pawn, Playfield& env);
	void ShroomAI(sf::Vector2i pawn, Playfield& env);
public:
	void Decide(sf::Vector2i pawn_pos, Playfield& env);
	void EnableAI(Playfield& env);
	void ResetAnimPositions(Playfield& env);
	void CheckForDead(Playfield& env);
};

