#include "Play.hpp"

Play::Play(int lv) : startPosition(0){
	Square::setTextureFile();
	setLv(lv);
}

bool Play::setLv(int lv) {
	menuBar = new MenuBar;
	map = new Map;
	player = new Player;
	teleports = new TeleportFields(1);
	traps = new Traps(1);
	blocks = new SlidingBlocks(2);
	plates = new Plates(2);
	doors = new Doors(2);
	blockS = new ShootingBlocks(2);
	machines = new LaserMachines(2);
	mirrors = new Mirrors(2);

	plates->setPlatePosition(0, VectorConverter::convert(1, 1).asVector2f());
	plates->setPlatePosition(1, VectorConverter::convert(2, 3).asVector2f());

	doors->setDoorPosition(0, VectorConverter::convert(1, 2).asVector2f());
	doors->setDoorPosition(1, VectorConverter::convert(2, 2).asVector2f());

	traps->setSpikesPosition(0, VectorConverter::convert(1, 3).asVector2f());
	traps->setOn(0, true);

	startPosition = { 2,1 };
	player->setPosition(startPosition.asVector2f());

	blocks->setBlockPosition(0, VectorConverter::convert(5, 5).asVector2f());
	blocks->setBlockPosition(1, VectorConverter::convert(5, 6).asVector2f());

	blockS->setPosition(0, VectorConverter::convert(1, 9).asVector2f());
	blockS->setType(0, ShootingBlock::B1);
	blockS->setDelay(0, 2);
	blockS->setPosition(1, VectorConverter::convert(2, 5).asVector2f());

	machines->setPosition(0, VectorConverter::convert(13, 2).asVector2f());
	machines->setPosition(1, VectorConverter::convert(12, 8).asVector2f());
	machines->setType(0, LaserMachine::D1, *map, blockS->getBlock(), blockS->getNumber());
	machines->setType(1, LaserMachine::D1, *map, blockS->getBlock(), blockS->getNumber());

	mirrors->setPosition(0, VectorConverter::convert(6, 3).asVector2f());
	mirrors->setPosition(1, VectorConverter::convert(4, 7).asVector2f());
	mirrors->setType(0, Mirror::C1, *map, blockS->getBlock(), blockS->getNumber(), machines->getMachine(), machines->getNumber());

	teleports->setTeleportPosition(0, VectorConverter::convert(2, 4).asVector2f());
	teleports->setTeleportPlace(0, VectorConverter::convert(10, 3).asVector2f());

	return false;
}

void Play::run() {
	
	HelpClass::runAll(*menuBar, *map, *teleports, *plates, *traps, *player, *blocks, *mirrors, *doors, *blockS, *machines);

	if (plates->isPressed(0)) doors->setOpen(0, true, *player, blocks->getBlock(), blocks->getNumber(),
		mirrors->getMirror(), mirrors->getNumber());
	else if (plates->isPressed(1)) doors->setOpen(0, true, *player, blocks->getBlock(), blocks->getNumber(),
		mirrors->getMirror(), mirrors->getNumber());
	else doors->setOpen(0, false, *player, blocks->getBlock(), blocks->getNumber(),
		mirrors->getMirror(), mirrors->getNumber());

	teleports->setOpen(0, plates->isPressed(0));
	blockS->setOn(0, plates->isPressed(0));
	blockS->setOn(1, plates->isPressed(0));

	HelpClass::move(*player, *map, blocks->getBlock(), blocks->getNumber(), mirrors->getMirror(), mirrors->getNumber(),
		doors->getDoor(), doors->getNumber(), blockS->getBlock(), blockS->getNumber(), machines->getMachine(), machines->getNumber());

	if (menuBar->getData().asHealth() == 0) return;

	if (player->getLive() == false) {
		menuBar->setHealth(menuBar->getData().asHealth() - 1);
		player->setPosition(startPosition.asVector2f());
		player->reset();
	}
}

void Play::draw(RenderWindow& window) {
	HelpClass::drawAll(window, *menuBar, *map, *teleports, *plates, *traps, *player, *blocks, *mirrors, *doors, *blockS, *machines);
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
}