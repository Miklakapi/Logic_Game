#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "ShootingBlock.hpp"
#include "Map.hpp"
#include "MenuBar.hpp"
#include "VectorConverter.hpp"
#include "Plates.hpp"
#include "Doors.hpp"
#include "TeleportFields.hpp"
#include "Traps.hpp"
#include "FPS.hpp"
#include "Player.hpp"
#include "HelpClass.hpp"
#include "SlidingBLocks.hpp"
#include "ShootingBlocks.hpp"
#include "LaserMachines.hpp"
#include "Mirrors.hpp"

using namespace sf;
using namespace std;

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
	ShootingBlocks blockss(2);
	blockss.setPosition(0, VectorConverter::convert(1, 9).asVector2f());
	blockss.setType(0, ShootingBlock::B1);
	blockss.setDelay(0, 2);

	blockss.setPosition(1, VectorConverter::convert(2, 5).asVector2f());
	//-------
	LaserMachines machines(2);
	machines.setPosition(0, VectorConverter::convert(13, 2).asVector2f());
	machines.setPosition(1, VectorConverter::convert(12, 8).asVector2f());
	machines.setType(0, LaserMachine::D1, map, blockss.getBlock(), blockss.getNumber());
	machines.setType(1, LaserMachine::D1, map, blockss.getBlock(), blockss.getNumber());

	//-------
	Mirrors mirror(2);
	mirror.setPosition(0, VectorConverter::convert(6, 3).asVector2f());
	mirror.setPosition(1, VectorConverter::convert(4, 7).asVector2f());
	mirror.setType(0, Mirror::C1, map, blockss.getBlock(), blockss.getNumber(), machines.getMachine(),
		machines.getNumber());
	//-------
	TeleportFields teleports(1);
	teleports.setTeleportPosition(0,VectorConverter::convert(2, 4).asVector2f());
	teleports.setTeleportPlace(0,VectorConverter::convert(10, 3).asVector2f());

	//-------
	FPS fps;
	fps.setOn(true);
	doors.setOpen(1, true, player, blocks.getBlock(), blocks.getNumber(),
		mirror.getMirror(), mirror.getNumber());
	

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
					player.setPosition(VectorConverter::convert(2, 1).asVector2f());
					player.reset();
					break;
				case Keyboard::Space:
					doors.setOpen(1, !doors.isOpen(1), player, blocks.getBlock(), blocks.getNumber(),
						mirror.getMirror(), mirror.getNumber());
					machines.setOn(0, !machines.isOn(0));
					break;
				}
				break;
			}
		}

		HelpClass::runAll(menu, map, teleports, plates, traps, player, blocks, mirror, doors, blockss, machines);

		//-------
		
		if (plates.isPressed(0)) doors.setOpen(0, true, player, blocks.getBlock(), blocks.getNumber(),
			mirror.getMirror(), mirror.getNumber());
		else if (plates.isPressed(1)) doors.setOpen(0, true, player, blocks.getBlock(), blocks.getNumber(),
			mirror.getMirror(), mirror.getNumber());
		else doors.setOpen(0, false, player, blocks.getBlock(), blocks.getNumber(),
			mirror.getMirror(), mirror.getNumber());

		teleports.setOpen(0, plates.isPressed(0));
		blockss.setOn(0, plates.isPressed(0));
		blockss.setOn(1, plates.isPressed(0));
		
		HelpClass::move(player, map, blocks.getBlock(), blocks.getNumber(), mirror.getMirror(), mirror.getNumber(),
			doors.getDoor(), doors.getNumber(), blockss.getBlock(), blockss.getNumber(), machines.getMachine(), machines.getNumber());

		//-------

		app.clear();
		HelpClass::drawAll(app, menu, map, teleports, plates, traps, player, blocks, mirror, doors, blockss, machines);
		app.draw(fps);
		app.display();
	}
}