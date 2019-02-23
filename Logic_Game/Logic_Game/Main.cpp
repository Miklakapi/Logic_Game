#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Map.hpp"
#include "MenuBar.hpp"
#include "Plate.hpp"
#include "VectorConverter.hpp"
#include "Door.hpp"
#include "Spikes.hpp"
#include "Player.hpp"
#include "Mirror.hpp"
#include "SlidingBLock.hpp"
#include "FPS.hpp"


using namespace sf;

int main() {
	RenderWindow app(VideoMode{ 1440,880 }, "Logic_Game", Style::Close);
	app.setFramerateLimit(144);
	//-------
	Map::setSquareTexture();

	Map map;
	//-------


	MenuBar menu;
	//-------	
	Plate::setPlateTexture();

	Plate plate[2];
	Plate* pl = plate;
	(pl + 0)->setPlatePosition(VectorConverter::convert(1, 1).asVector2f());
	(pl + 1)->setPlatePosition(VectorConverter::convert(2, 2).asVector2f());
	//-------
	Door::setDoorTexture();

	Door door;
	door.setDoorPosition(VectorConverter::convert(1, 2).asVector2f());
	//-------
	Spikes::loadSpikesTexture();

	Spikes spikes;
	spikes.setPosition(VectorConverter::convert(1, 3).asVector2f());
	spikes.setOn(true);
	//-------
	Player player;
	player.setPosition(VectorConverter::convert(2, 1).asVector2f());
	//-------
	SlidingBlock::setBlockTexture();

	SlidingBlock block[2];
	block[0].setPosition(VectorConverter::convert(5, 5).asVector2f());
	block[1].setPosition(VectorConverter::convert(5, 6).asVector2f());

	//-------
	Mine::setMineTexture();
	ShootingBlock::setBlockTexture();

	ShootingBlock blockS;
	blockS.setBlockPosition(VectorConverter::convert(7, 9).asVector2f());

	//-------
	LaserMachine* machine = NULL;
	Mirror* mirror = NULL;

	//-------
	FPS fps;

	while (app.isOpen()) {

		fps.run();

		Event event;
		while (app.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				app.close();
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) player.movePlayer(Player::Up, map, &blockS, 1, &door, 1, machine, 0, block, 2, mirror, 0);
		else if (Keyboard::isKeyPressed(Keyboard::A)) player.movePlayer(Player::Left, map, &blockS, 1, &door, 1, machine, 0, block, 2, mirror, 0);
		else if (Keyboard::isKeyPressed(Keyboard::S)) player.movePlayer(Player::Down, map, &blockS, 1, &door, 1, machine, 0, block, 2, mirror, 0);
		else if (Keyboard::isKeyPressed(Keyboard::D)) player.movePlayer(Player::Right, map, &blockS, 1, &door, 1, machine, 0, block, 2, mirror, 0);

		//-------
		menu.run();
		player.run(&door,1);
		//-------
		spikes.run(player, block, 2, mirror, 0);
		(plate + 0)->run(player, block, 2, mirror, 0);
		(plate + 1)->run(player, block, 2, mirror, 0);
		block[0].run(&door, 1);
		block[1].run(&door, 1);
		blockS.run(map, &door, 1);
		//-------

		if (plate->isPressed()) door.setOpen(true);
		else if((plate + 1)->isPressed()) door.setOpen(true);
		else door.setOpen(false);
		
		//-------

		app.clear();
		map.draw(app);
		(plate + 0)->draw(app);
		(plate + 1)->draw(app);
		door.draw(app);
		spikes.draw(app);
		menu.draw(app);
		block[0].draw(app);
		block[1].draw(app);
		blockS.draw(app);
		player.draw(app);
		app.draw(fps);
		app.display();
	}
}