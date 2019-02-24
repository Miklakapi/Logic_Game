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
#include "TeleportField.hpp"

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
	(pl + 1)->setPlatePosition(VectorConverter::convert(2, 3).asVector2f());
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

	ShootingBlock blockS[2];
	blockS[0].setBlockPosition(VectorConverter::convert(1, 9).asVector2f());
	blockS[0].setType(ShootingBlock::B1);
	blockS[0].setOn(true);
	blockS[0].setDelay(2);
	blockS[1].setBlockPosition(VectorConverter::convert(1, 5).asVector2f());

	//-------
	LaserMachine* machine = NULL;
	Mirror* mirror = NULL;

	//-------
	TeleportField::setTeleportTexture();
	TeleportField teleport;
	teleport.setTeleportPosition(VectorConverter::convert(2, 4).asVector2f());
	teleport.setTeleportPlace(VectorConverter::convert(10, 3).asVector2f());

	//-------
	FPS fps;
	fps.setOn(true);

	while (app.isOpen()) {

		fps.run();

		Event event;
		while (app.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				app.close();
				break;
			case Event::KeyPressed:
				switch (event.key.code) {
				case Keyboard::R:
					player.reset();
					break;
				}
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) player.movePlayer(Player::Up, map, blockS, 2, &door, 1, machine, 0, block, 2, mirror, 0);
		else if (Keyboard::isKeyPressed(Keyboard::A)) player.movePlayer(Player::Left, map, blockS, 2, &door, 1, machine, 0, block, 2, mirror, 0);
		else if (Keyboard::isKeyPressed(Keyboard::S)) player.movePlayer(Player::Down, map, blockS, 2, &door, 1, machine, 0, block, 2, mirror, 0);
		else if (Keyboard::isKeyPressed(Keyboard::D)) player.movePlayer(Player::Right, map, blockS, 2, &door, 1, machine, 0, block, 2, mirror, 0);

		//-------
		menu.run();
		player.run(&door,1, blockS, 2);
		//-------
		spikes.run(player, block, 2, mirror, 0);
		(plate + 0)->run(player, block, 2, mirror, 0);
		(plate + 1)->run(player, block, 2, mirror, 0);
		block[0].run(&door, 1, blockS, 2);
		block[1].run(&door, 1, blockS, 2);
		blockS[0].run(map, &door, 1, blockS, 2);
		blockS[1].run(map, &door, 1, blockS, 2);
		teleport.run(player, block, 2, mirror, 0);
		//-------

		if (plate->isPressed()) door.setOpen(true);
		else if((plate + 1)->isPressed()) door.setOpen(true);
		else door.setOpen(false);

		teleport.setOpen(plate->isPressed());
		blockS[0].setOn(plate->isPressed());
		blockS[1].setOn(plate->isPressed());
		
		//-------

		app.clear();
		map.draw(app);
		(plate + 0)->draw(app);
		(plate + 1)->draw(app);
		door.draw(app);
		spikes.draw(app);
		menu.draw(app);
		teleport.draw(app);
		blockS[0].draw(app);
		blockS[1].draw(app);
		block[0].draw(app);
		block[1].draw(app);
		player.draw(app);
		app.draw(fps);
		app.display();
	}
}