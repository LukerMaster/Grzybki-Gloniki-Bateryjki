#include "StatePlayfield.h"


float StatePlayfield::lerp(float a, float b, float percent)
{
	if (percent > 1.0f) percent = 1.0f;
	return ((b - a) * percent) + a;
}

template<typename T>
sf::Vector2f StatePlayfield::GetPositionByGrid(sf::Vector2<T> grid_pos)
{
	return { (575 / (float)vars.playfield_size) * grid_pos.x + 57, (575 / (float)vars.playfield_size) * grid_pos.y + 13 };
}

template <typename T>
sf::Vector2f StatePlayfield::GetScaleByGrid(sf::Vector2<T> rect)
{
	return { (575 / (float)vars.playfield_size) / rect.x, (575 / (float)vars.playfield_size) / rect.y };
}

std::shared_ptr<Object> StatePlayfield::GetObjUnder(sf::Vector2i mouse_pos)
{
	if (mouse_pos.x > 57 && mouse_pos.x < (575 + 57) && mouse_pos.y > 13 && mouse_pos.y < (575 + 13))
		return playfield.GetObj(sf::Vector2i( ((mouse_pos.x - 57.0f) / 575.0f) * playfield.GetSize(), ((mouse_pos.y - 13.0f) / 575) * playfield.GetSize() ));
	else
		return nullptr;
}

StatePlayfield::StatePlayfield(Vars& vars_, sf::RenderWindow& window_)
	:State(vars_, window_),
	round_current(0),
	btn_back(0, sf::Vector2f(30, window.getSize().y - 60), sf::Vector2f(70, 40), "Menu", vars.assets.font, vars.assets.btn_hover, vars.assets.btn_click, ""),
	playfield(vars.playfield_size),
	animator(playfield.events),
	curr_sim_step(0),
	stat_bar(vars.assets.font)
{
	btn_back.baseColor = { 0, 0, 0, 0 };
	btn_back.hlColor = { 0, 0, 0, 0 };
	btn_back.baseTextColor = { 0, 0, 80, 255 };
	btn_back.hlTextColor = { 100, 100, 200, 255 };

	sim_step.setFont(vars.assets.font);
	sim_step.setFillColor({ 0, 100, 0, 255 });
	sim_step.setOutlineColor(sf::Color::White);
	sim_step.setOutlineThickness(4);
	sim_step.setPosition({ 57, window.getSize().y * 0.85f });


	vars.assets.spaces_tex.loadFromFile("assets/spcs.mlg");
	vars.assets.playfield_tex.loadFromFile("assets/plbg.mlg");
	vars.assets.food_tex.loadFromFile("assets/fd.mlg");
	vars.assets.death_icons.loadFromFile("assets/ded.mlg");
	vars.assets.stat_bar.loadFromFile("assets/bar.mlg");

	stat_bar.Create(vars.assets.stat_bar, sf::IntRect( 0, 0, vars.assets.stat_bar.getSize().x, vars.assets.stat_bar.getSize().y ), window.getSize() , sf::Vector2u(vars.assets.stat_bar.getSize().x, vars.assets.stat_bar.getSize().y));

	playfield_bg.setTexture(vars.assets.playfield_tex);

	int bacteria_to_place = vars.num_of_bacteria;
	int algae_to_place = vars.num_of_algae;
	int shrooms_to_place = vars.num_of_shrooms;

	round_length = 1500.0f;
	anim_length = 450.0f;

	//
	// Placing down starting germs.
	//
	while (algae_to_place)
	{
		if( playfield.AddGermRandom(eObjType::Algae, 20, 100, 100, 100, 100) == true)
			algae_to_place--;
	}
	while (bacteria_to_place)
	{
		if (playfield.AddGermRandom(eObjType::Bacteria, 100, 100, 100, 100, 100) == true)
			bacteria_to_place--;
	}
	while (shrooms_to_place)
	{
		if (playfield.AddGermRandom(eObjType::Shroom, 100, 100, 100, 100, 100) == true)
			shrooms_to_place--;
	}

}

void StatePlayfield::Step(float dt)
{
	round_current += dt;
	if (round_current > round_length) // Basically every 1 second do all the moves and stuff.
	{
		controller.CheckForDead(playfield);
		controller.ResetAnimPositions(playfield);
		controller.EnableAI(playfield);

		for (int x = 0; x < playfield.GetSize(); x++)
		{
			for (int y = 0; y < playfield.GetSize(); y++)
			{
				controller.Decide({ x, y }, playfield);
			}
		}

		round_current = 0;
		curr_sim_step++;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		selected = std::static_pointer_cast<Germ>(GetObjUnder(sf::Mouse::getPosition(window)));
	}
	if (selected != nullptr)
	{
		if (selected->type == eObjType::Algae)
			stat_bar.SetStats(selected->sprite, selected->current_age, selected->max_health, selected->current_health, selected->max_food, selected->current_food, 10, 10, "Glonik");
		else if (selected->type == eObjType::Shroom)
			stat_bar.SetStats(selected->sprite, selected->current_age, selected->max_health, selected->current_health, selected->max_food, selected->current_food, 10, 10, "Grzybek");
		else if (selected->type == eObjType::Bacteria)
			stat_bar.SetStats(selected->sprite, selected->current_age, selected->max_health, selected->current_health, selected->max_food, selected->current_food, 10, 10, "Bakteryjka");
		
		if (selected->dead)
		{
			selected = nullptr;
		}
	}

	stat_bar.Step(dt);

	btn_back.Update(dt, sf::Mouse::getPosition(window));
	if (btn_back.CheckAndUnclick())
	{
		vars.next_state = eState::menu;
	}

	while (playfield.events.AreStillDeaths())
	{
		DeathData ded = playfield.events.GetDeath();
		{
			if (ded.cause == eDeathType::old_age)
				animator.AddAnimation(std::make_shared<PopUp>(PopUp(vars.assets.death_icons, { 64, 64, 64, 64 }, GetPositionByGrid(ded.dead->start_pos), GetScaleByGrid(sf::Vector2f(64, 64)), anim_length * 3)));
			if (ded.cause == eDeathType::starved)
				animator.AddAnimation(std::make_shared<PopUp>(PopUp(vars.assets.death_icons, { 0, 0, 64, 64 }, GetPositionByGrid(ded.dead->start_pos), GetScaleByGrid(sf::Vector2f(64, 64)), anim_length * 3)));
			if (ded.cause == eDeathType::eaten)
			{
				if (ded.killer->type == eObjType::Bacteria)
					animator.AddAnimation(std::make_shared<PopUp>(PopUp(vars.assets.death_icons, { 64, 0, 64, 64 }, GetPositionByGrid(ded.dead->start_pos), GetScaleByGrid(sf::Vector2f(64, 64)), anim_length * 3)));
				if (ded.killer->type == eObjType::Shroom)
					animator.AddAnimation(std::make_shared<PopUp>(PopUp(vars.assets.death_icons, { 0, 64, 64, 64 }, GetPositionByGrid(ded.dead->start_pos), GetScaleByGrid(sf::Vector2f(64, 64)), anim_length * 3)));

				sf::IntRect body_rect = ded.dead->sprite.getTextureRect();

				if (ded.dead->type == eObjType::Food)
					animator.AddAnimation(std::make_shared<DeathAnim>(DeathAnim(vars.assets.food_tex, body_rect, GetPositionByGrid(ded.dead->start_pos), GetPositionByGrid(ded.killer->start_pos), GetScaleByGrid(ded.dead->sprite.getTextureRect().getSize()), anim_length)));
				else
					animator.AddAnimation(std::make_shared<DeathAnim>(DeathAnim(vars.assets.microbe_tex, body_rect, GetPositionByGrid(ded.dead->start_pos), GetPositionByGrid(ded.killer->start_pos), GetScaleByGrid(ded.dead->sprite.getTextureRect().getSize()), anim_length)));
			}
				
		}
		playfield.events.RemoveLastDeath();
	}
	animator.StepAnimations(dt);
	animator.DeleteDoneAnimations();
	
}

void StatePlayfield::Draw()
{
	window.clear({255, 255, 220, 255});
	window.draw(playfield_bg);

	sf::Sprite bg_decoration;
	bg_decoration.setTexture(vars.assets.spaces_tex);

	for (int x = 0; x < playfield.GetSize(); x++)
	{
		for (int y = 0; y < playfield.GetSize(); y++)
		{
			bg_decoration.setTextureRect(playfield.GetRekt(x, y));
			bg_decoration.setPosition((575 / (float)vars.playfield_size) * x + 57, (575 / (float)vars.playfield_size) * y + 13);
			bg_decoration.setScale((575 / (float)vars.playfield_size) / 64, (575 / (float)vars.playfield_size) / 64);
			window.draw(bg_decoration);
		}
	}


	for (int x = 0; x < playfield.GetSize(); x++)
	{
		for (int y = 0; y < playfield.GetSize(); y++)
		{
			if (playfield.GetObj(x, y)->type != eObjType::EmptySpace)
			{
				if (playfield.GetObj(x, y)->type == eObjType::Algae || playfield.GetObj(x, y)->type == eObjType::Bacteria || playfield.GetObj(x, y)->type == eObjType::Shroom)
					playfield.GetObj(x, y)->sprite.setTexture(vars.assets.microbe_tex);
				if (playfield.GetObj(x, y)->type == eObjType::Food)
					playfield.GetObj(x, y)->sprite.setTexture(vars.assets.food_tex);
					
				float shown_x = lerp(playfield.GetObj(x, y)->start_pos.x, playfield.GetObj(x, y)->end_pos.x, round_current / anim_length);
				float shown_y = lerp(playfield.GetObj(x, y)->start_pos.y, playfield.GetObj(x, y)->end_pos.y, round_current / anim_length);

				playfield.GetObj(x, y)->sprite.setPosition(GetPositionByGrid<float>({ shown_x, shown_y }));
				playfield.GetObj(x, y)->sprite.setScale(GetScaleByGrid(playfield.GetObj(x, y)->sprite.getTextureRect().getSize()));

				window.draw(playfield.GetObj(x, y)->sprite);
			}
		}
	}

	animator.DrawAnimations(window);

	sim_step.setString("Krok symulacji: " + std::to_string(curr_sim_step));
	window.draw(sim_step);

	if (selected != nullptr)
	{
		stat_bar.Draw(window);
	}
	btn_back.Draw(window);
	window.display();
}
