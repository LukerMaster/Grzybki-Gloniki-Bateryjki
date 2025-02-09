#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
enum class eState
{
	menu,
	playfield
};

struct Assets
{
	sf::Texture microbe_tex;
	sf::Texture spaces_tex;
	sf::Texture menu_tex;
	sf::Texture playfield_tex;
	sf::Texture bg_tile_tex;
	sf::Texture bubble_tex;
	sf::Texture food_tex;
	sf::Texture death_icons;
	sf::Texture plank_tex;
	sf::Texture stat_bar;

	sf::Font font;
	sf::SoundBuffer btn_click;
	sf::SoundBuffer btn_hover;
};

struct Vars
{
	bool is_running;
	float framerate;
	bool fullscreen;

	unsigned int num_of_algae;
	unsigned int num_of_bacteria;
	unsigned int num_of_shrooms;

	int power_of_algae;
	int power_of_bacteria;
	int power_of_shrooms;

	int playfield_size;

	eState prev_state;
	eState current_state;
	eState next_state;

	Assets assets;

};

