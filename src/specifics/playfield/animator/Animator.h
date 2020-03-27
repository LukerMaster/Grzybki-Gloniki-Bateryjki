#pragma once
#include "SFML/Window.hpp"
#include <vector>
#include "Animation.h"
#include "../EventMgr.h"
class Animator
{
	EventMgr& events;
	std::vector<std::shared_ptr<Animation>> anims;
public:
	Animator(EventMgr& events_)
		:events(events_) {};

	void StepAnimations(float dt);

	void DrawAnimations(sf::RenderWindow& window);

	void AddAnimation(std::shared_ptr<Animation> anim);

	void DeleteDoneAnimations();
};

