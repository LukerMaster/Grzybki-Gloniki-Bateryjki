#include "StateMenu.h"

#define MAX_SOLDIERS 10


StateMenu::StateMenu(Vars& vars_, sf::RenderWindow& window_)
	:buttons
	(
		{
			{
				"exit",
				Button(0, sf::Vector2f(20, window.getSize().y - 60), { 50, 35 }, "Papa", vars.assets.font , vars.assets.btn_hover, vars.assets.btn_click, "")
			},
			{
				"moreAlgae",
				Button(0, sf::Vector2f(55, window.getSize().y - 240), { 130, 35 }, "Wincyj glonuf",vars.assets.font , vars.assets.btn_hover, vars.assets.btn_click, "")
			},
			{
				"lessAlgae",
				Button(0, sf::Vector2f(65, window.getSize().y - 120), { 120, 35 }, "Mnij glonuf",vars.assets.font , vars.assets.btn_hover, vars.assets.btn_click, "")
			},
			{
				"moreBacteria",
				Button(0, sf::Vector2f(200, window.getSize().y - 240), { 160, 35 }, "Wincyj bakteriuf",vars.assets.font , vars.assets.btn_hover, vars.assets.btn_click, "")
			},
			{
				"lessBacteria",
				Button(0, sf::Vector2f(210, window.getSize().y - 120), { 150, 35 }, "Mnij bakteriuf",vars.assets.font , vars.assets.btn_hover, vars.assets.btn_click, "")
			},
			{
				"moreShrooms",
				Button(0, sf::Vector2f(380, window.getSize().y - 240), { 150, 35 }, "Wincyj grzybuf",vars.assets.font , vars.assets.btn_hover, vars.assets.btn_click, "")
			},
			{
				"lessShrooms",
				Button(0, sf::Vector2f(390, window.getSize().y - 120), { 140, 35 }, "Mnij grzybuf",vars.assets.font , vars.assets.btn_hover, vars.assets.btn_click, "")
			},
			{
				"play",
				Button(0, sf::Vector2f(window.getSize().x - 120, window.getSize().y - 60), { 100, 35 }, "Lecimy!",vars.assets.font , vars.assets.btn_hover, vars.assets.btn_click, "")
			}
		}
	),
	State(vars_, window_)
{
	game_name.setPosition(40, 20);
	game_name.setCharacterSize(100);
	game_name.setString("Grzybki, Gloniki\ni Bateryjki!");
	game_name.setFont(vars.assets.font);
	game_name.setFillColor({ 254, 150, 0, 255 });
	game_name.setOutlineThickness(4);
	game_name.setOutlineColor({255, 255, 255, 255});

	LoadMicrobeAssets();
	
	//
	// BUTTONS
	//
	uint8_t Opacity = 0;
	buttons.find("exit")->second.baseTextColor = { 0, 77, 0, 255 };
	buttons.find("exit")->second.baseColor = { 0, 0, 0, 0 };
	buttons.find("exit")->second.hlTextColor = { 77, 255, 77, 155 };
	buttons.find("exit")->second.hlColor = { 0, 0, 0, Opacity };

	buttons.find("play")->second.baseTextColor = { 0, 77, 200, 255 };
	buttons.find("play")->second.baseColor = { 0, 0, 0, 0 };
	buttons.find("play")->second.hlTextColor = { 14, 255, 255, 155 };
	buttons.find("play")->second.hlColor = { 0, 0, 0, Opacity };

	buttons.find("moreAlgae")->second.baseTextColor = { 0, 77, 0, 255 };
	buttons.find("moreAlgae")->second.baseColor = { 0, 0, 0, 0 };
	buttons.find("moreAlgae")->second.hlTextColor = { 77, 255, 77, 225 };
	buttons.find("moreAlgae")->second.hlColor = { 0, 0, 0, Opacity };

	buttons.find("lessAlgae")->second.baseTextColor = { 0, 77, 0, 255 };
	buttons.find("lessAlgae")->second.baseColor = { 0, 0, 0, 0 };
	buttons.find("lessAlgae")->second.hlTextColor =  { 77, 255, 77, 225 };
	buttons.find("lessAlgae")->second.hlColor = { 0, 0, 0, Opacity };

	buttons.find("moreBacteria")->second.baseTextColor = { 0, 143, 179, 255 };
	buttons.find("moreBacteria")->second.baseColor = { 0, 0, 0, 0 };
	buttons.find("moreBacteria")->second.hlTextColor =  { 102, 224, 255, 225 };
	buttons.find("moreBacteria")->second.hlColor = { 0, 0, 0, Opacity };

	buttons.find("lessBacteria")->second.baseTextColor = { 0, 143, 179, 255 };
	buttons.find("lessBacteria")->second.baseColor = { 0, 0, 0, 0 };
	buttons.find("lessBacteria")->second.hlTextColor = { 102, 224, 255, 225 };
	buttons.find("lessBacteria")->second.hlColor = { 0, 0, 0, Opacity };

	buttons.find("moreShrooms")->second.baseTextColor = { 153, 0, 0, 255 };
	buttons.find("moreShrooms")->second.baseColor = { 0, 0, 0, 0 };
	buttons.find("moreShrooms")->second.hlTextColor =  { 255, 102, 102, 225 };
	buttons.find("moreShrooms")->second.hlColor = { 0, 0, 0, Opacity };

	buttons.find("lessShrooms")->second.baseTextColor = { 153, 0, 0, 255 };
	buttons.find("lessShrooms")->second.baseColor = { 0, 0, 0, 0 };
	buttons.find("lessShrooms")->second.hlTextColor = { 255, 102, 102, 225 };
	buttons.find("lessShrooms")->second.hlColor = { 0, 0, 0, Opacity };
	//
	// MENU
	//
	vars.assets.menu_tex.loadFromFile("assets/mnbg.mlg");
	menu_sprite.setTexture(vars.assets.menu_tex);
	menu_sprite.setPosition(0, 0);
	menu_sprite.setScale(window.getSize().x / (float)vars.assets.menu_tex.getSize().x , window.getSize().y / (float)vars.assets.menu_tex.getSize().y);
}

void StateMenu::Step(float dt)
{
	std::map<const char*, Button>::iterator it = buttons.begin();
	while (it != buttons.end())
	{
		it->second.Update(dt, sf::Mouse::getPosition(window));
		it++;
	}

	if (buttons.find("exit")->second.CheckAndUnclick())
	{
		vars.is_running = false;
	}
	if (buttons.find("play")->second.CheckAndUnclick())
	{
		vars.next_state = eState::playfield;
	}
	if (buttons.find("moreAlgae")->second.CheckAndUnclick())
	{
		if (vars.num_of_algae < MAX_SOLDIERS)
			vars.num_of_algae++;
	}
	if (buttons.find("lessAlgae")->second.CheckAndUnclick())
	{
		if (vars.num_of_algae > 1)
			vars.num_of_algae--;
	}
	if (buttons.find("moreBacteria")->second.CheckAndUnclick())
	{
		if (vars.num_of_bacteria < MAX_SOLDIERS)
			vars.num_of_bacteria++;
	}
	if (buttons.find("lessBacteria")->second.CheckAndUnclick())
	{
		if (vars.num_of_bacteria > 1)
			vars.num_of_bacteria--;
	}
	if (buttons.find("moreShrooms")->second.CheckAndUnclick())
	{
		if (vars.num_of_shrooms < MAX_SOLDIERS)
			vars.num_of_shrooms++;
	}
	if (buttons.find("lessShrooms")->second.CheckAndUnclick())
	{
		if (vars.num_of_shrooms > 1)
			vars.num_of_shrooms--;
	}
	algae_amount.setString(std::to_string(vars.num_of_algae));
	bacteria_amount.setString(std::to_string(vars.num_of_bacteria));
	shrooms_amount.setString(std::to_string(vars.num_of_shrooms));

	StepJumpAnimation(dt);

}

void StateMenu::Draw()
{
	window.clear(sf::Color::Black);
	window.draw(menu_sprite);

	// Draw microbes
	for (int i = 0; i < algae_jumping.size(); i++)
		window.draw(algae_jumping[i]);
	for (int i = 0; i < bacteria_jumping.size(); i++)
		window.draw(bacteria_jumping[i]);
	for (int i = 0; i < shrooms_jumping.size(); i++)
		window.draw(shrooms_jumping[i]);

	// Draw buttons
	std::map<const char*, Button>::iterator it = buttons.begin();
	while (it != buttons.end())
	{
		it->second.Draw(window);
		it++;
	}
	
	// Draw amounts
	window.draw(algae_amount);
	window.draw(bacteria_amount);
	window.draw(shrooms_amount);
	window.draw(game_name);
	window.display();
}

void StateMenu::LoadMicrobeAssets()
{
	algae_amount.setPosition(95, window.getSize().y - 200);
	bacteria_amount.setPosition(275, window.getSize().y - 200);
	shrooms_amount.setPosition(455, window.getSize().y - 200);

	algae_amount.setFont(vars.assets.font);
	bacteria_amount.setFont(vars.assets.font);
	shrooms_amount.setFont(vars.assets.font);

	algae_amount.setCharacterSize(50);
	bacteria_amount.setCharacterSize(50);
	shrooms_amount.setCharacterSize(50);

	algae_amount.setFillColor({ 0, 0, 0, 255 });
	bacteria_amount.setFillColor({ 0, 0, 0, 255 });
	shrooms_amount.setFillColor({ 0, 0, 0, 255 });

	algae_amount.setOutlineColor({ 255, 255, 255, 255 });
	bacteria_amount.setOutlineColor({ 255, 255, 255, 255 });
	shrooms_amount.setOutlineColor({ 255, 255, 255, 255 });

	algae_amount.setOutlineThickness(2);
	bacteria_amount.setOutlineThickness(2);
	shrooms_amount.setOutlineThickness(2);

}

void StateMenu::StepJumpAnimation(float dt)
{
	//
	// Balance amount of jumping microbes.
	//
	if (algae_jumping.size() > vars.num_of_algae)
	{
		algae_jumping.pop_back();
	}
	else if (algae_jumping.size() < vars.num_of_algae)
	{
		algae_jumping.push_back(sf::Sprite(vars.assets.microbe_tex, sf::IntRect((rand() % 3) * 64, 0, 64, 64)));
	}

	if (bacteria_jumping.size() > vars.num_of_bacteria)
	{
		bacteria_jumping.pop_back();
	}
	else if (bacteria_jumping.size() < vars.num_of_bacteria)
	{
		bacteria_jumping.push_back(sf::Sprite(vars.assets.microbe_tex, sf::IntRect((rand() % 3) * 64, 64, 64, 64)));
	}

	if (shrooms_jumping.size() > vars.num_of_shrooms)
	{
		shrooms_jumping.pop_back();
	}
	else if (shrooms_jumping.size() < vars.num_of_shrooms)
	{
		shrooms_jumping.push_back(sf::Sprite(vars.assets.microbe_tex, sf::IntRect((rand() % 3) * 64, 128, 64, 64)));
	}

	


	for (int i = 0; i < algae_jumping.size(); i++)
	{
		algae_jumping[i].setPosition(i * 15, window.getSize().y - 180 - 30 * sin(3.14 * ((jump_animation_frame + (i * 20)) % 100) / 100));
		algae_jumping[i].setScale(1, 0.8 + 0.2 * sin(3.14 * ((jump_animation_frame + (i * 20)) % 100) / 100));
	}
	for (int i = 0; i < bacteria_jumping.size(); i++)
	{
		bacteria_jumping[i].setPosition(i * 15 + 190, window.getSize().y - 180 - 30 * sin(3.14 * ((jump_animation_frame + (i * 20)) % 100) / 100));
		bacteria_jumping[i].setScale(1, 0.8 + 0.2 * sin(3.14 * ((jump_animation_frame + (i * 20)) % 100) / 100));
	}
	for (int i = 0; i < shrooms_jumping.size(); i++)
	{
		shrooms_jumping[i].setPosition(i * 15 + 370, window.getSize().y - 180 - 30 * sin(3.14 * ((jump_animation_frame + (i * 20)) % 100) / 100));
		shrooms_jumping[i].setScale(1, 0.8 + 0.2*sin(3.14 * ((jump_animation_frame + (i * 20)) % 100) / 100));
	}

	jump_animation_frame+= dt * 0.0002f;
}
