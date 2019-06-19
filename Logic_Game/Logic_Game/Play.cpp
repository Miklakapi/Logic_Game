#include "Play.hpp"

Play::Play(int lv) : startPosition(0){
	Square::setTextureFile();
	setLv(lv);
}

bool Play::setLv(int lv) {
	
	menuBar = new MenuBar;
	map = new Map;
	player = new Player;
	//
	teleports = new TeleportFields(1);
	traps = new Traps(6);
	blocks = new SlidingBlocks(2);
	plates = new Plates(2);
	doors = new Doors(2);
	blockS = new ShootingBlocks(2);
	machines = new LaserMachines(1);
	mirrors = new Mirrors(3);
	receivers = new LaserReceivers(2);

	plates->setPlatePosition(0, VectorConverter::convert(4, 9).asVector2f());
	plates->setPlatePosition(1, VectorConverter::convert(8, 5).asVector2f());
	
	doors->setDoorPosition(0, VectorConverter::convert(6, 5).asVector2f());
	doors->setDoorPosition(1, VectorConverter::convert(16, 2).asVector2f());
	
	traps->setSpikesPosition(0, VectorConverter::convert(2, 8).asVector2f());
	traps->setOn(0, true);
	traps->setSpikesPosition(1, VectorConverter::convert(1, 7).asVector2f());
	traps->setOn(1, true);
	traps->setSpikesPosition(2, VectorConverter::convert(4, 4).asVector2f());
	traps->setOn(2, true);
	traps->setSpikesPosition(3, VectorConverter::convert(5, 1).asVector2f());
	traps->setOn(3, true);
	traps->setSpikesPosition(4, VectorConverter::convert(6, 2).asVector2f());
	traps->setOn(4, true);
	traps->setSpikesPosition(5, VectorConverter::convert(7, 1).asVector2f());
	traps->setOn(5, true);
	
	startPosition = { 1,9 };
	player->setPosition(startPosition.asVector2f());
	
	blocks->setBlockPosition(0, VectorConverter::convert(3, 7).asVector2f());
	blocks->setBlockPosition(1, VectorConverter::convert(5, 4).asVector2f());
	
	blockS->setPosition(0, VectorConverter::convert(2, 5).asVector2f());
	blockS->setType(0, ShootingBlock::A1);
	blockS->setDelay(0, 1.5);
	blockS->setPosition(1, VectorConverter::convert(1, 4).asVector2f());
	blockS->setType(1, ShootingBlock::A2);
	blockS->setDelay(1, 1.5);
	
	receivers->setType(0, LaserReceiver::Type::B1);
	receivers->setPosition(0, VectorConverter::convert(8, 9).asVector2f());
	receivers->setType(1, LaserReceiver::Type::A4);
	receivers->setPosition(1, VectorConverter::convert(16, 5).asVector2f());

	machines->setPosition(0, VectorConverter::convert(12, 1).asVector2f());
	machines->setType(0, LaserMachine::A3, *map, blockS->getBlock(), blockS->getNumber(), receivers->getReceiver(), receivers->getNumber());
	
	mirrors->setPosition(0, VectorConverter::convert(12, 6).asVector2f());
	mirrors->setType(0, Mirror::A2, *map, blockS->getBlock(), blockS->getNumber(), machines->getMachine(), machines->getNumber(), receivers->getReceiver(), receivers->getNumber());
	mirrors->setPosition(1, VectorConverter::convert(13, 3).asVector2f());
	mirrors->setType(1, Mirror::C1, *map, blockS->getBlock(), blockS->getNumber(), machines->getMachine(), machines->getNumber(), receivers->getReceiver(), receivers->getNumber());
	mirrors->setPosition(2, VectorConverter::convert(14, 7).asVector2f());
	mirrors->setType(2, Mirror::A4, *map, blockS->getBlock(), blockS->getNumber(), machines->getMachine(), machines->getNumber(), receivers->getReceiver(), receivers->getNumber());
	
	teleports->setTeleportPosition(0, VectorConverter::convert(16, 1).asVector2f());
	teleports->setTeleportPlace(0, VectorConverter::convert(1, 9).asVector2f());

	return false; // zwarcanie wykrycia poziomu ??
}

void Play::run() {
	
	HelpClass::runAll(*menuBar, *map, *teleports, *plates, *traps, *player, *blocks, *mirrors, *doors, *blockS, *machines, *receivers);

	if (plates->isPressed(0)) doors->setOpen(0, true, *player, blocks->getBlock(), blocks->getNumber(), mirrors->getMirror(), mirrors->getNumber());
	else doors->setOpen(0, false, *player, blocks->getBlock(), blocks->getNumber(), mirrors->getMirror(), mirrors->getNumber());

	machines->setOn(0, plates->isPressed(1));
	
	if (receivers->getOn(0) && receivers->getOn(1)) {
		teleports->setOpen(0, true);
		doors->setOpen(1, true, *player, blocks->getBlock(), blocks->getNumber(), mirrors->getMirror(), mirrors->getNumber());
	}
	else {
		teleports->setOpen(0, false);
		doors->setOpen(1, false, *player, blocks->getBlock(), blocks->getNumber(), mirrors->getMirror(), mirrors->getNumber());
	}
	
	blockS->setOn(0, plates->isPressed(0));
	blockS->setOn(1, plates->isPressed(0));

	HelpClass::move(*player, *map, blocks->getBlock(), blocks->getNumber(), mirrors->getMirror(), mirrors->getNumber(),
		doors->getDoor(), doors->getNumber(), blockS->getBlock(), blockS->getNumber(), machines->getMachine(), machines->getNumber(), receivers->getReceiver(), receivers->getNumber());

	if (menuBar->getData().asHealth() == 0) return;

	if (player->getLive() == false) {
		menuBar->setHealth(menuBar->getData().asHealth() - 1);
		player->setPosition(startPosition.asVector2f());
		player->reset();
	}
}

void Play::draw(RenderWindow& window) {
	HelpClass::drawAll(window, *menuBar, *map, *teleports, *plates, *traps, *player, *blocks, *mirrors, *doors, *blockS, *machines, *receivers);
	menuBar->draw(window);
}

Play::~Play(){
	delete menuBar;
	delete map;
	delete player;
	delete teleports;
	delete traps;
	delete blocks;
	delete plates;
	delete doors;
	delete blockS;
	delete machines;
	delete mirrors;
	delete receivers;
}