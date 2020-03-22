#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "State.h"

#include "../Button.h"
#include "Vars.h"
#include <map>
class StateMenu : public State
{
	sf::Sprite menu_sprite;

	std::map<const char*, Button> buttons;
	//
	std::vector<sf::Sprite> bacteria_jumping;
	std::vector<sf::Sprite> algae_jumping;
	std::vector<sf::Sprite> shrooms_jumping;
	//
	sf::Text bacteria_amount;
	sf::Text algae_amount;
	sf::Text shrooms_amount;
	sf::Text game_name;

	unsigned short jump_animation_frame;
public:
	StateMenu(Vars& vars, sf::RenderWindow& window);
	virtual void Step(float dt);
	virtual void Draw();


	void LoadMicrobeAssets();
	void StepJumpAnimation(float dt);
};

