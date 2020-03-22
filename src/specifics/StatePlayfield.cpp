#include "StatePlayfield.h"

StatePlayfield::StatePlayfield(Vars& vars_, sf::RenderWindow& window_)
	:State(vars_, window_),
	btn_back(0, sf::Vector2f(30, window.getSize().y - 60), sf::Vector2f(70, 40), "Menu", vars.assets.font, vars.assets.btn_hover, vars.assets.btn_click, "")
{
	btn_back.baseColor = { 0, 0, 0, 0 };
	btn_back.hlColor = { 0, 0, 0, 0 };
	btn_back.baseTextColor = { 0, 0, 80, 255 };
	btn_back.hlTextColor = { 100, 100, 200, 255 };


	vars.assets.spaces_tex.loadFromFile("assets/spcs.mlg");
	vars.assets.playfield_tex.loadFromFile("assets/plbg.mlg");

	playfield_bg.setTexture(vars.assets.playfield_tex);

	int bacteria_to_place = vars.num_of_bacteria;
	int algae_to_place = vars.num_of_algae;
	int shrooms_to_place = vars.num_of_shrooms;

	//
	// Creating playfield.
	//

	vars.playfield_size = 20; // TO CHANGE!
	int pf_size = vars.playfield_size; // playfield size. default 10x10.


	for (int x = 0; x < pf_size; x++)
	{
		objects.push_back(std::vector<std::shared_ptr<Object>>());
		for (int y = 0; y < pf_size; y++)
		{
			if (rand()%8 == 0) // Making more grass spaces than others.
				objects[x].push_back(std::make_shared<EmptySpace>(EmptySpace({ x, y }, vars.assets.spaces_tex, { (rand() % 4) * 64, (rand() % 4) * 64, 64, 64 })));
			else
				objects[x].push_back(std::make_shared<EmptySpace>(EmptySpace({ x, y }, vars.assets.spaces_tex, { (rand() % 4) * 64, 192, 64, 64 })));
		}
	}

	//
	// Placing down starting germs.
	//
	while (algae_to_place)
	{
		int x = rand() % pf_size;
		int y = rand() % pf_size;
		if (objects[x][y]->type == eObjType::Space)
		{
			objects[x][y] = std::make_shared<Algae>(Algae( { x, y }, vars.assets.microbe_tex, { (rand() % 3) * 64, 0, 64, 64}, 100, 100, 100 ));
			algae_to_place--;
		}
	}
	while (bacteria_to_place)
	{
		int x = rand() % pf_size;
		int y = rand() % pf_size;
		if (objects[x][y]->type == eObjType::Space)
		{
			objects[x][y] = std::make_shared<Bacteria>(Bacteria({ x, y }, vars.assets.microbe_tex, {(rand() % 3) * 64, 64, 64, 64 }, 100, 100, 100));
			bacteria_to_place--;
		}
	}
	while (shrooms_to_place)
	{
		int x = rand() % pf_size;
		int y = rand() % pf_size;
		if (objects[x][y]->type == eObjType::Space)
		{
			objects[x][y] = std::make_shared<Shroom>(Shroom({ x, y }, vars.assets.microbe_tex, {(rand() % 3) * 64, 128, 64, 64 }, 100, 100, 100));
			shrooms_to_place--;
		}
	}

}

void StatePlayfield::Step(float dt)
{
	btn_back.Update(dt, sf::Mouse::getPosition(window));
	if (btn_back.CheckAndUnclick())
	{
		vars.next_state = eState::menu;
	}
	for (int x = 0; x < objects.size(); x++)
	{
		for (int y = 0; y < objects[x].size(); y++)
		{
			
		}
	}
}

void StatePlayfield::Draw()
{
	window.clear({255, 255, 220, 255});
	window.draw(playfield_bg);

	for (int x = 0; x < objects.size(); x++)
	{
		for (int y = 0; y < objects[x].size(); y++)
		{
			objects[x][y]->sprite.setPosition((575 / (float)vars.playfield_size) * x + 57, (575 / (float)vars.playfield_size) * y + 13);
			objects[x][y]->sprite.setScale((575 / (float)vars.playfield_size) / 64, (575 / (float)vars.playfield_size) / 64);
			window.draw(objects[x][y]->sprite);
		}
	}
	btn_back.Draw(window);
	window.display();
}
