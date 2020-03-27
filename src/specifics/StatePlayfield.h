#pragma once
#include "SFML/Graphics.hpp"
#include "Vars.h"
#include "State.h"

#include "playfield/AIController.h"
#include "playfield/Playfield.h"
#include "playfield/GermClasses.h"
#include "playfield/Food.h"
#include "playfield/StatBar.h"

#include "playfield/animator/Animator.h"
#include "playfield/animator/PopUp.h"
#include "playfield/animator/DeathAnim.h"

#include "../Button.h"

//#include <iostream>
class StatePlayfield : public State
{
	sf::Sprite playfield_bg;

	sf::Text sim_step;
	
	long long curr_sim_step;
	float anim_length;
	float round_current; // Used to make game round-based rather than real-time.
	float round_length;
	Button btn_back;
	Animator animator;
	Playfield playfield;
	AIController controller;
	StatBar stat_bar;

	float lerp(float a, float b, float percent);
	template <typename T>
	sf::Vector2f GetPositionByGrid(sf::Vector2<T> grid_pos);
	template <typename T>
	sf::Vector2f GetScaleByGrid(sf::Vector2<T> rect);

	std::shared_ptr<Germ> selected;
	std::shared_ptr<Object> GetObjUnder(sf::Vector2i mouse_pos);

public:
	StatePlayfield(Vars& vars_, sf::RenderWindow& window);
	virtual void Step(float dt);
	virtual void Draw();
};
