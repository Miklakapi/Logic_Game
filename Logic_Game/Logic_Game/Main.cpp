#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Map.hpp"
#include "MenuBar.hpp"
#include "VectorConverter.hpp"
#include "Plates.hpp"
#include "Doors.hpp"
#include "TeleportFields.hpp"
#include "Traps.hpp"
#include "SlidingBLocks.hpp"
#include "FPS.hpp"


#include "Player.hpp"
#include "Mirror.hpp"




using namespace sf;

int main() {
	RenderWindow app(VideoMode{ 1440,880 }, "Logic_Game", Style::Close);
	app.setFramerateLimit(144);

	//-------
	Square::setTextureFile();
	Map map;
	//-------
	MenuBar menu;
	//-------	
	Plates plates(2);
	plates.setPlatePosition(0, VectorConverter::convert(1, 1).asVector2f());
	plates.setPlatePosition(1, VectorConverter::convert(2, 3).asVector2f());
	//-------
	Doors doors(2);
	doors.setDoorPosition(0, VectorConverter::convert(1, 2).asVector2f());
	doors.setDoorPosition(1, VectorConverter::convert(2, 2).asVector2f());
	//-------
	Traps traps(1);
	traps.setSpikesPosition(0, VectorConverter::convert(1, 3).asVector2f());
	traps.setOn(0, true);
	//-------
	Player player;
	player.setPosition(VectorConverter::convert(2, 1).asVector2f());
	//-------
	SlidingBlocks blocks(2);
	blocks.setBlockPosition(0, VectorConverter::convert(5, 5).asVector2f());
	blocks.setBlockPosition(1, VectorConverter::convert(5, 6).asVector2f());

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
	TeleportFields teleports(1);
	teleports.setTeleportPosition(0,VectorConverter::convert(2, 4).asVector2f());
	teleports.setTeleportPlace(0,VectorConverter::convert(10, 3).asVector2f());

	//-------
	FPS fps;
	fps.setOn(true);
	doors.setOpen(1, true, player, blocks.getBlock(), blocks.getNumber(), mirror, 0);
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
				case Keyboard::Space:
					doors.setOpen(1, !doors.isOpen(1), player, blocks.getBlock(), blocks.getNumber(), mirror, 0);
					break;
				}
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) player.movePlayer(Player::Up, map, blocks.getBlock(), blocks.getNumber(), mirror, 0, doors.getDoor(), doors.getNumber(), blockS, 2, machine, 0);
		else if (Keyboard::isKeyPressed(Keyboard::A)) player.movePlayer(Player::Left, map, blocks.getBlock(), blocks.getNumber(), mirror, 0, doors.getDoor(), doors.getNumber(), blockS, 2, machine, 0);
		else if (Keyboard::isKeyPressed(Keyboard::S)) player.movePlayer(Player::Down, map, blocks.getBlock(), blocks.getNumber(), mirror, 0, doors.getDoor(), doors.getNumber(), blockS, 2, machine, 0);
		else if (Keyboard::isKeyPressed(Keyboard::D)) player.movePlayer(Player::Right, map, blocks.getBlock(), blocks.getNumber(), mirror, 0, doors.getDoor(), doors.getNumber(), blockS, 2, machine, 0);

		if (Keyboard::isKeyPressed(Keyboard::W)) blocks.push(0, SlidingBlock::Up, map, mirror, 0, doors.getDoor(), doors.getNumber(), blockS, 2, machine, 0);
		else if (Keyboard::isKeyPressed(Keyboard::A)) blocks.push(0, SlidingBlock::Left, map, mirror, 0, doors.getDoor(), doors.getNumber(), blockS, 2, machine, 0);
		else if (Keyboard::isKeyPressed(Keyboard::S)) blocks.push(0, SlidingBlock::Down, map, mirror, 0, doors.getDoor(), doors.getNumber(), blockS, 2, machine, 0);
		else if (Keyboard::isKeyPressed(Keyboard::D)) blocks.push(0, SlidingBlock::Right, map, mirror, 0, doors.getDoor(), doors.getNumber(), blockS, 2, machine, 0);

		//-------
		menu.run();
		player.run(blockS, 2);
		//-------
		traps.run(player, blocks.getBlock(), blocks.getNumber(), mirror, 0);
		plates.run(player, blocks.getBlock(), blocks.getNumber(), mirror, 0);
		blocks.run();
		blockS[0].run(map, doors.getDoor(), doors.getNumber(), blockS, 2);
		blockS[1].run(map, doors.getDoor(), doors.getNumber(), blockS, 2);
		teleports.run(player, blocks.getBlock(), blocks.getNumber(), mirror, 0);
		//-------

		if (plates.isPressed(0)) doors.setOpen(0, true, player, blocks.getBlock(), blocks.getNumber(), mirror, 0);
		else if (plates.isPressed(1)) doors.setOpen(0, true, player, blocks.getBlock(), blocks.getNumber(), mirror, 0);
		else doors.setOpen(0, false, player, blocks.getBlock(), blocks.getNumber(), mirror, 0);

		teleports.setOpen(0, plates.isPressed(0));
		blockS[0].setOn(plates.isPressed(0));
		blockS[1].setOn(plates.isPressed(0));
		
		//-------

		app.clear();
		map.draw(app);
		plates.draw(app);
		doors.draw(app);
		traps.draw(app);
		menu.draw(app);
		teleports.draw(app);
		blockS[0].draw(app);
		blockS[1].draw(app);
		blocks.draw(app);
		player.draw(app);
		app.draw(fps);
		app.display();
	}
}