#include "Play.hpp"

Play::HelpClass::HelpClass() {
	deviceNumber = 0;
	deviceName = new string[0];
	deviceID = new int[0];
	on = new bool[0];
}

void Play::HelpClass::setDeviceNumber(int number) {
	this->deviceNumber = number;
	delete [] deviceName;
	delete [] deviceID;
	delete [] on;
	deviceName = new string[number];
	deviceID = new int[number];
	on = new bool[number];
}

int Play::HelpClass::getDeviceNumber() {
	return deviceNumber;
}

void Play::HelpClass::setDeviceName(int nr, string name) {
	*(this->deviceName + nr) = name;
}

string Play::HelpClass::getDeviceName(int nr) {
	return *(deviceName + nr);
}

void Play::HelpClass::setDeviceID(int nr, int id) {
	*(deviceID + nr) = id;
}

int Play::HelpClass::getDeviceID(int nr) {
	return *(deviceID + nr);
}

void Play::HelpClass::setOn(int nr, bool on) {
	*(this->on + nr) = on;
}

bool Play::HelpClass::getOn(int nr) {
	return *(on + nr);
}

Play::HelpClass::~HelpClass() {
	delete [] deviceName;
	delete [] deviceID;
	delete [] on;
}

////////////////
////////////////
////////////////

Play::Play(int lv, string loseTexture, string winTexture, string fontFile) : startPosition(0), winPosition(0) {
	Square::setTextureFile();
	setLv(lv);
	this->loseTexture.loadFromFile(loseTexture);
	this->winTexture.loadFromFile(winTexture);
	screen.setSize(Vector2f{ 1440,880 });
	screen.setPosition(Vector2f{ 0,0 });
	win = false;
	//
	font.loadFromFile(fontFile);

	winTime.setCharacterSize(80);
	winTime.setFont(font);
	winTime.setFillColor(Color::White);
	winTime.setLetterSpacing(1);
	winTime.setStyle(Text::Bold);
	winTime.setPosition(Vector2f{ 685,520 });
}

void Play::setLv(int lv) {

	menuBar = new MenuBar;
	map = new Map;
	player = new Player;

	int* number = new int[9]; //ilosc urzadzen

	int* teleportPosition;
	int* teleportPlace;
	bool* teleportOpen;

	int* trapPosition;
	bool* trapOn;

	int* slidingPosition;

	int* platePosition;

	int* doorPosition;
	bool* doorOn;

	int* sblockPosition;
	ShootingBlock::Type* sblockType;
	int* sblockDelay;
	bool* sblockOn;

	int* laserPosition;
	LaserMachine::Type* laserType;
	bool* laserOn;

	int* mirrorPosition;
	Mirror::Type* mirrorType;

	int* receiverPosition;
	LaserReceiver::Type* receiverType;

	string file = "Lvs/Lv" + to_string(lv) + "b.txt";
	fstream stream(file, ios::in);
	
	if (!stream.is_open()) {
		stream.open("error.txt", ios::out);
		stream << "File " << "Lv" << to_string(lv) << "b.txt is not exist.\n";
		exit(0);
	}

	string line;

	//1
	getline(stream, line);
	startPosition = VectorConverter{ int(atoi(line.c_str())) };

	//2
	getline(stream, line);
	winPosition = VectorConverter{ int(atoi(line.c_str())) };

	//Teleports
	getline(stream, line);
	*(number) = atoi(line.c_str());
	teleportPosition = new int[*number];
	teleportPlace = new int[*number];
	teleportOpen = new bool[*number];

	for (int i = 0; i < *number; i++) {
		getline(stream, line);
		*(teleportPosition + i) = atoi(line.c_str());
		getline(stream, line);
		*(teleportPlace + i) = atoi(line.c_str());
		getline(stream, line);
		*(teleportOpen + i) = atoi(line.c_str());
	}

	//Traps
	getline(stream, line);
	*(number + 1) = atoi(line.c_str());
	trapPosition = new int[*(number + 1)];
	trapOn = new bool[*(number + 1)];

	for (int i = 0; i < *(number + 1); i++) {
		getline(stream, line);
		*(trapPosition + i) = atoi(line.c_str());
		getline(stream, line);
		*(trapOn + i) = atoi(line.c_str());
	}

	//Sliding Blocks
	getline(stream, line);
	*(number + 2) = atoi(line.c_str());
	slidingPosition = new int[*(number + 2)];
	
	for (int i = 0; i < *(number + 2); i++) {
		getline(stream, line);
		*(slidingPosition + i) = atoi(line.c_str());
	}

	//Plates
	getline(stream, line);
	*(number + 3) = atoi(line.c_str());
	platePosition = new int[*(number + 3)];
	plateC = new HelpClass[*(number + 3)];

	for (int i = 0; i < *(number + 3); i++) {
		getline(stream, line);
		*(platePosition + i) = atoi(line.c_str());
		getline(stream, line);
		(plateC + i)->setDeviceNumber(atoi(line.c_str()));
		for (int j = 0; j < (plateC + i)->getDeviceNumber(); j++) {
			getline(stream, line);
			(plateC + i)->setDeviceName(j, line);
			getline(stream, line);
			(plateC + i)->setDeviceID(j, atoi(line.c_str()));
			getline(stream, line);
			(plateC + i)->setOn(j, atoi(line.c_str()));
		}
	}

	//Doors
	getline(stream, line);
	*(number + 4) = atoi(line.c_str());
	doorPosition = new int[*(number + 4)];
	doorOn = new bool[*(number + 4)];
	
	for (int i = 0; i < *(number + 4); i++) {
		getline(stream, line);
		*(doorPosition + i) = atoi(line.c_str());
		getline(stream, line);
		*(doorOn + i) = atoi(line.c_str());
	}

	//Shooting Blocks
	getline(stream, line);
	*(number + 5) = atoi(line.c_str());
	sblockPosition = new int[*(number + 5)];
	sblockType = new ShootingBlock::Type[*(number + 5)];
	sblockDelay = new int[*(number + 5)];
	sblockOn = new bool[*(number + 5)];

	for (int i = 0; i < *(number + 5); i++) {
		getline(stream, line);
		*(sblockPosition + i) = atoi(line.c_str());
		getline(stream, line);
		int a = atoi(line.c_str());
		switch (a) {
		case 1:
			*(sblockType + i) = ShootingBlock::A1;
			break;
		case 2:
			*(sblockType + i) = ShootingBlock::A2;
			break;
		case 3:
			*(sblockType + i) = ShootingBlock::A3;
			break;
		case 4:
			*(sblockType + i) = ShootingBlock::A4;
			break;
		case 5:
			*(sblockType + i) = ShootingBlock::B1;
			break;
		case 6:
			*(sblockType + i) = ShootingBlock::B2;
			break;
		case 7:
			*(sblockType + i) = ShootingBlock::B3;
			break;
		case 8:
			*(sblockType + i) = ShootingBlock::B4;
			break;
		case 9:
			*(sblockType + i) = ShootingBlock::B5;
			break;
		case 10:
			*(sblockType + i) = ShootingBlock::B6;
			break;
		case 11:
			*(sblockType + i) = ShootingBlock::C1;
			break;
		case 12:
			*(sblockType + i) = ShootingBlock::C2;
			break;
		case 13:
			*(sblockType + i) = ShootingBlock::C3;
			break;
		case 14:
			*(sblockType + i) = ShootingBlock::C4;
			break;
		case 15:
			*(sblockType + i) = ShootingBlock::D1;
			break;
		}
		getline(stream, line);
		*(sblockDelay + i) = int(atoi(line.c_str()) / 1000);
		getline(stream, line);
		*(sblockOn + i) = atoi(line.c_str());
	}

	//Laser Block
	getline(stream, line);
	*(number + 6) = atoi(line.c_str());
	laserPosition = new int[*(number + 6)];
	laserType = new LaserMachine::Type[*(number + 6)];
	laserOn = new bool[*(number + 6)];

	for (int i = 0; i < *(number + 6); i++) {
		getline(stream, line);
		*(laserPosition + i) = atoi(line.c_str());
		getline(stream, line);
		int a = atoi(line.c_str());
		switch (a) {
		case 1:
			*(laserType + i) = LaserMachine::A1;
			break;
		case 2:
			*(laserType + i) = LaserMachine::A2;
			break;
		case 3:
			*(laserType + i) = LaserMachine::A3;
			break;
		case 4:
			*(laserType + i) = LaserMachine::A4;
			break;
		case 5:
			*(laserType + i) = LaserMachine::B1;
			break;
		case 6:
			*(laserType + i) = LaserMachine::B2;
			break;
		case 7:
			*(laserType + i) = LaserMachine::B3;
			break;
		case 8:
			*(laserType + i) = LaserMachine::B4;
			break;
		case 9:
			*(laserType + i) = LaserMachine::B5;
			break;
		case 10:
			*(laserType + i) = LaserMachine::B6;
			break;
		case 11:
			*(laserType + i) = LaserMachine::C1;
			break;
		case 12:
			*(laserType + i) = LaserMachine::C2;
			break;
		case 13:
			*(laserType + i) = LaserMachine::C3;
			break;
		case 14:
			*(laserType + i) = LaserMachine::C4;
			break;
		case 15:
			*(laserType + i) = LaserMachine::D1;
			break;
		}
		getline(stream, line);
		*(laserOn + i) = atoi(line.c_str());
	}

	//Mirror
	getline(stream, line);
	*(number + 7) = atoi(line.c_str());
	mirrorPosition = new int[*(number + 7)];
	mirrorType = new Mirror::Type[*(number + 7)];

	for (int i = 0; i < *(number + 7); i++) {
		getline(stream, line);
		*(mirrorPosition + i) = atoi(line.c_str());
		getline(stream, line);
		int a = atoi(line.c_str());
		switch (a) {
		case 1:
			*(mirrorType + i) = Mirror::A1;
			break;
		case 2:
			*(mirrorType + i) = Mirror::A2;
			break;
		case 3:
			*(mirrorType + i) = Mirror::A3;
			break;
		case 4:
			*(mirrorType + i) = Mirror::A4;
			break;
		case 5:
			*(mirrorType + i) = Mirror::B1;
			break;
		case 6:
			*(mirrorType + i) = Mirror::B2;
			break;
		case 7:
			*(mirrorType + i) = Mirror::B3;
			break;
		case 8:
			*(mirrorType + i) = Mirror::B4;
			break;
		case 9:
			*(mirrorType + i) = Mirror::C1;
			break;
		}
	}

	//Laser Receiver
	getline(stream, line);
	*(number + 8) = atoi(line.c_str());
	receiverPosition = new int[*(number + 8)];
	receiverType = new LaserReceiver::Type[*(number + 8)];
	receiverC = new HelpClass[*(number + 8)];

	for (int i = 0; i < *(number + 8); i++) {
		getline(stream, line);
		*(receiverPosition + i) = atoi(line.c_str());
		getline(stream, line);
		int a = atoi(line.c_str());
		switch (a) {
		case 1:
			*(receiverType + i) = LaserReceiver::A1;
			break;
		case 2:
			*(receiverType + i) = LaserReceiver::A2;
			break;
		case 3:
			*(receiverType + i) = LaserReceiver::A3;
			break;
		case 4:
			*(receiverType + i) = LaserReceiver::A4;
			break;
		case 5:
			*(receiverType + i) = LaserReceiver::B1;
			break;
		case 6:
			*(receiverType + i) = LaserReceiver::B2;
			break;
		case 7:
			*(receiverType + i) = LaserReceiver::B3;
			break;
		case 8:
			*(receiverType + i) = LaserReceiver::B4;
			break;
		case 9:
			*(receiverType + i) = LaserReceiver::B5;
			break;
		case 10:
			*(receiverType + i) = LaserReceiver::B6;
			break;
		case 11:
			*(receiverType + i) = LaserReceiver::C1;
			break;
		case 12:
			*(receiverType + i) = LaserReceiver::C2;
			break;
		case 13:
			*(receiverType + i) = LaserReceiver::C3;
			break;
		case 14:
			*(receiverType + i) = LaserReceiver::C4;
			break;
		case 15:
			*(receiverType + i) = LaserReceiver::D1;
			break;
		}
		getline(stream, line);
		(receiverC + i)->setDeviceNumber(atoi(line.c_str()));
		for (int j = 0; j < (receiverC + i)->getDeviceNumber(); j++) {
			getline(stream, line);
			(receiverC + i)->setDeviceName(j, line);
			getline(stream, line);
			(receiverC + i)->setDeviceID(j, atoi(line.c_str()));
			getline(stream, line);
			(receiverC + i)->setOn(j, atoi(line.c_str()));
		}
	}

	stream.close();

	teleports = new TeleportFields((*(number + 0) + 1));
	traps = new Traps(*(number + 1));
	blocks = new SlidingBlocks(*(number + 2));
	plates = new Plates(*(number + 3));
	doors = new Doors(*(number + 4));
	blockS = new ShootingBlocks(*(number + 5));
	machines = new LaserMachines(*(number + 6));
	mirrors = new Mirrors(*(number + 7));
	receivers = new LaserReceivers(*(number + 8));

	menuBar->setLV(lv);
	map->renderLV(lv);

	player->setPosition(startPosition.asVector2f());

	for (int i = 0; i < *(number + 3); i++) {
		plates->setPlatePosition(i, VectorConverter::convert(*(platePosition + i)).asVector2f());
	}

	for (int i = 0; i < *(number + 1); i++) {
		traps->setSpikesPosition(i, VectorConverter::convert(*(trapPosition + i)).asVector2f());
		traps->setOn(i, *(trapOn + i));
	}

	for (int i = 0; i < *(number + 2); i++) {
		blocks->setBlockPosition(i, VectorConverter::convert(*(slidingPosition + i)).asVector2f());
	}

	for (int i = 0; i < *(number + 5); i++) {
		blockS->setPosition(i, VectorConverter::convert(*(sblockPosition + i)).asVector2f());
		blockS->setType(i, *(sblockType + i));
		blockS->setDelay(i, *(sblockDelay + i));
		blockS->setOn(i, *(sblockOn + i));
	}

	for (int i = 0; i < *(number + 8); i++) {
		receivers->setType(i, *(receiverType + i));
		receivers->setPosition(i, VectorConverter::convert(*(receiverPosition + i)).asVector2f());
	}

	for (int i = 0; i < *(number + 6); i++) {
		machines->setPosition(i, VectorConverter::convert(*(laserPosition + i)).asVector2f());
		machines->setType(i, *(laserType + i), *map, blockS->getBlock(), blockS->getNumber(), receivers->getReceiver(), receivers->getNumber());
		machines->setOn(i, *(laserOn + i));
	}

	for (int i = 0; i < *(number + 7); i++) {
		mirrors->setPosition(i, VectorConverter::convert(*(mirrorPosition + i)).asVector2f());
		mirrors->setType(i, *(mirrorType + i), *map, blockS->getBlock(), blockS->getNumber(), machines->getMachine(), machines->getNumber(), receivers->getReceiver(), receivers->getNumber());
	}

	for (int i = 0; i < *(number + 4); i++) {
		doors->setDoorPosition(i, VectorConverter::convert(*(doorPosition + i)).asVector2f());
		doors->setOpen(i, *(doorOn + i), *player, blocks->getBlock(), blocks->getNumber(), mirrors->getMirror(), mirrors->getNumber());
	}

	teleports->setTeleportPosition(0, winPosition.asVector2f());
	teleports->setTeleportPlace(0, startPosition.asVector2f());
	teleports->setOpen(0, true);

	for (int i = 1; i < (*(number)+1); i++) {
		teleports->setTeleportPosition(i, VectorConverter::convert(*(teleportPosition + i - 1)).asVector2f());
		teleports->setTeleportPlace(i, VectorConverter::convert(*(teleportPlace + i - 1)).asVector2f());
		teleports->setOpen(i, *(teleportOpen + i - 1));
	}

	delete [] number;

	delete [] teleportPlace;
	delete [] teleportPosition;
	delete [] teleportOpen;

	delete [] trapPosition;
	delete [] trapOn;

	delete [] slidingPosition;

	delete [] platePosition;

	delete [] doorPosition;
	delete [] doorOn;

	delete [] sblockPosition;
	delete [] sblockType;
	delete [] sblockDelay;
	delete [] sblockOn;

	delete [] laserPosition;
	delete [] laserType;
	delete [] laserOn;

	delete [] mirrorPosition;
	delete [] mirrorType;

	delete [] receiverPosition;
	delete [] receiverType;
}

int Play::run() {
	
	if (!win && winPosition.asVector2f() == player->getPosition() && teleports->isOpen(0)) {
		win = true;
		screen.setTexture(&winTexture);
		winClock.restart();
		minutes = menuBar->getData().asMinutes();
		seconds = menuBar->getData().asSeconds();
		//

		string minutesS;
		if (minutes < 10) minutesS = "0" + to_string(minutes);
		else minutesS = to_string(minutes);

		string secondsS;
		if (seconds < 10) secondsS = "0" + to_string(seconds);
		else secondsS = to_string(seconds);

		string clockString;

		clockString = minutesS + " : " + secondsS;

		winTime.setString(clockString);
	}

	::HelpClass::runAll(*menuBar, *map, *teleports, *plates, *traps, *player, *blocks, *mirrors, *doors, *blockS, *machines, *receivers);

	//

	for (int i = 0; i < plates->getNumber(); i++) {

		for (int j = 0; j < (plateC + i)->getDeviceNumber(); j++) {

			if ((plateC + i)->getDeviceName(j) == "teleport") {

				if ((plateC + i)->getOn(j) == true) {
					teleports->setOpen((plateC + i)->getDeviceID(j) + 1, plates->isPressed(i));
				}
				else {
					teleports->setOpen((plateC + i)->getDeviceID(j) + 1, !(plates->isPressed(i)));
				}
			}
			else if ((plateC + i)->getDeviceName(j) == "trap") {
				if ((plateC + i)->getOn(j) == true) {
					traps->setOn((plateC + i)->getDeviceID(j), plates->isPressed(i));
				}
				else {
					traps->setOn((plateC + i)->getDeviceID(j), !(plates->isPressed(i)));
				}
			}
			else if ((plateC + i)->getDeviceName(j) == "door") {
				if ((plateC + i)->getOn(j) == true) {
					doors->setOpen((plateC + i)->getDeviceID(j), plates->isPressed(i), *player, blocks->getBlock(), blocks->getNumber(), mirrors->getMirror(), mirrors->getNumber());
				}
				else {
					doors->setOpen((plateC + i)->getDeviceID(j), !(plates->isPressed(i)), *player, blocks->getBlock(), blocks->getNumber(), mirrors->getMirror(), mirrors->getNumber());
				}
			}
			else if ((plateC + i)->getDeviceName(j) == "sblock") {
				if ((plateC + i)->getOn(j) == true) {
					blockS->setOn((plateC + i)->getDeviceID(j), plates->isPressed(i));
				}
				else {
					blockS->setOn((plateC + i)->getDeviceID(j), !(plates->isPressed(i)));
				}
			}
			else if ((plateC + i)->getDeviceName(j) == "lmachine") {
				if ((plateC + i)->getOn(j) == true) {
					machines->setOn((plateC + i)->getDeviceID(j), plates->isPressed(i));
				}
				else {
					machines->setOn((plateC + i)->getDeviceID(j), !(plates->isPressed(i)));
				}
			}
		}
	}

	for (int i = 0; i < receivers->getNumber(); i++) {

		for (int j = 0; j < (receiverC + i)->getDeviceNumber(); j++) {

			if ((receiverC + i)->getDeviceName(j) == "teleport") {

				if ((receiverC + i)->getOn(j) == true) {
					teleports->setOpen((receiverC + i)->getDeviceID(j) + 1, receivers->getOn(i));
				}
				else {
					teleports->setOpen((receiverC + i)->getDeviceID(j) + 1, !(receivers->getOn(i)));
				}
			}
			else if ((receiverC + i)->getDeviceName(j) == "trap") {
				if ((receiverC + i)->getOn(j) == true) {
					traps->setOn((receiverC + i)->getDeviceID(j), receivers->getOn(i));
				}
				else {
					traps->setOn((receiverC + i)->getDeviceID(j), !(receivers->getOn(i)));
				}
			}
			else if ((receiverC + i)->getDeviceName(j) == "door") {
				if ((receiverC + i)->getOn(j) == true) {
					doors->setOpen((receiverC + i)->getDeviceID(j), receivers->getOn(i), *player, blocks->getBlock(), blocks->getNumber(), mirrors->getMirror(), mirrors->getNumber());
				}
				else {
					doors->setOpen((receiverC + i)->getDeviceID(j), !(receivers->getOn(i)), *player, blocks->getBlock(), blocks->getNumber(), mirrors->getMirror(), mirrors->getNumber());
				}
			}
			else if ((receiverC + i)->getDeviceName(j) == "sblock") {
				if ((receiverC + i)->getOn(j) == true) {
					blockS->setOn((receiverC + i)->getDeviceID(j), receivers->getOn(i));
				}
				else {
					blockS->setOn((receiverC + i)->getDeviceID(j), !(receivers->getOn(i)));
				}
			}
			else if ((receiverC + i)->getDeviceName(j) == "lmachine") {
				if ((receiverC + i)->getOn(j) == true) {
					machines->setOn((receiverC + i)->getDeviceID(j), receivers->getOn(i));
				}
				else {
					machines->setOn((receiverC + i)->getDeviceID(j), !(receivers->getOn(i)));
				}
			}
		}
	}

	::HelpClass::move(*player, *map, blocks->getBlock(), blocks->getNumber(), mirrors->getMirror(), mirrors->getNumber(),
		doors->getDoor(), doors->getNumber(), blockS->getBlock(), blockS->getNumber(), machines->getMachine(), machines->getNumber(), receivers->getReceiver(), receivers->getNumber());

	if (player->getLive() == false && player->getClock().getElapsedTime().asSeconds() > 0.5) {

		if (menuBar->getData().asHealth() > 1) {
			menuBar->setHealth(menuBar->getData().asHealth() - 1);
			player->setPosition(startPosition.asVector2f());
			player->reset();
		}
		else if (menuBar->getData().asHealth() == 1) {
			menuBar->setHealth(menuBar->getData().asHealth() - 1);
			screen.setTexture(&loseTexture);
		}
	}

	if (menuBar->getData().asHealth() <= 0 && player->getClock().getElapsedTime().asSeconds() >= 1.5) {
		return 0; // death
	}

	if (win && winClock.getElapsedTime().asSeconds() >= 1.5) {
		return menuBar->getData().asLV(); // win
	}

	return -1; // normal
}

void Play::draw(RenderWindow& window) {
	if (menuBar->getData().asHealth() > 0 && win == false) {
		::HelpClass::drawAll(window, *menuBar, *map, *teleports, *plates, *traps, *player, *blocks, *mirrors, *doors, *blockS, *machines, *receivers);
		menuBar->draw(window);
	}
	else {
		window.draw(screen);
		if (win) {
			window.draw(winTime);
		}
	}
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