#include "Editor.hpp"

void Editor::save() {
	
	fstream stream("New Level.txt", ios::out);

	for (int i = 0; i < 198; i++) {
		//Map
		if ((screen + 0)->getMapS(i) == Square2::MapStage::Wall) {
			stream << "#";
		}
		else {
			stream << "-";
		}
		if ((i + 1) % 18 == 0) stream << endl;
	}
	stream.close();

	//
	int teleportNumber = (screen + 2)->getTeleportNumber();
	int* teleportPosition = new int[teleportNumber];
	int* teleportPlace = new int[teleportNumber];
	bool* teleportOn = new bool[teleportNumber];
	int teleportFlag = 0;
	//
	int trapNumber = (screen + 2)->getTrapNumber();
	int* trapPosition = new int[trapNumber];
	bool* trapOn = new bool[trapNumber];
	int trapFlag = 0;
	//
	int slidingNumber = (screen + 2)->getSlidingNumber();
	int* slidingPosition = new int[slidingNumber];
	int slidingFlag = 0;
	//
	int plateNumber = (screen + 3)->getPlateNumber();
	int* platePosition = new int[plateNumber];
	Play::HelpClass* plateC = new Play::HelpClass[plateNumber];
	int plateFlag = 0;
	//
	int doorNumber = (screen + 2)->getDoorNumber();
	int* doorPosition = new int[doorNumber];
	bool* doorOn = new bool[doorNumber];
	int doorFlag = 0;
	//
	int shootingNumber = (screen + 2)->getShootingNumber();
	int* shootingPosition = new int[shootingNumber];
	int* shootingType = new int[shootingNumber];
	bool* shootingOn = new bool[shootingNumber];
	int shootingFlag = 0;
	//
	int laserNumber = (screen + 2)->getEmiterNumber();
	int* laserPosition = new int[laserNumber];
	int* laserType = new int[laserNumber];
	bool* laserOn = new bool[laserNumber];
	int laserFlag = 0;
	//
	int mirrorNumber = (screen + 2)->getMirrorNumber();
	int* mirrorPosition = new int[mirrorNumber];
	int* mirrorType = new int[mirrorNumber];
	int mirrorFlag = 0;
	//
	int receiverNumber = (screen + 3)->getReceiverNumber();
	int* receiverPosition = new int[receiverNumber];
	int* receiverType = new int[receiverNumber];
	Play::HelpClass* receiverC = new Play::HelpClass[receiverNumber];
	int receiverFlag = 0;

	//

	for (int i = 19; i < 179; i++) {
		//
		if ((screen + 2)->getBlockS(i) == Square2::BlockStage::TeleportOff || (screen + 2)->getBlockS(i) == Square2::BlockStage::TeleportOn) {
			*(teleportPosition + teleportFlag) = i;
			if ((screen + 2)->getBlockS(i) == Square2::BlockStage::TeleportOff) *(teleportOn + teleportFlag) = false;
			else *(teleportOn + teleportFlag) = true;
			Color color = (screen + 4)->getColor(i, Screen::Click::Teleport);
			for (int j = 19; j < 179; j++) {
				if (j != i) {
					if (color == (screen + 4)->getColor(j, Screen::Click::Teleport)) {
						*(teleportPlace + teleportFlag) = j;
					}
				}
			}
			teleportFlag++;
		}
		//
		if ((screen + 2)->getBlockS(i) == Square2::BlockStage::TrapOff || (screen + 2)->getBlockS(i) == Square2::BlockStage::TrapOn) {
			*(trapPosition + trapFlag) = i;
			if ((screen + 2)->getBlockS(i) == Square2::BlockStage::TrapOn) *(trapOn + trapFlag) = true;
			else *(trapOn + trapFlag) = false;
			trapFlag++;
		}
		//
		if ((screen + 2)->getBlockS(i) == Square2::BlockStage::SlidingBlock) {
			*(slidingPosition + slidingFlag) = i;
			slidingFlag++;
		}
		//
		if ((screen + 3)->getSwitchS(i) == Square2::SwitchStage::Plate) {
			*(platePosition + plateFlag) = i;
			Color color = (screen + 4)->getColor(i, Screen::Click::Device);
			int nr = 0;
			for (int j = 19; j < 179; j++) {
				if (i != j && (screen + 4)->getColor(j, Screen::Device) == color) {
					nr++;
				}
			}
			(plateC + plateFlag)->setDeviceNumber(nr);
			
			nr = 0;

			for (int j = 19; j < 179; j++) {
				if (i != j && (screen + 4)->getColor(j, Screen::Device) == color) {

					string name = "error";
					bool on = true;
					int aNr = 0;
					int range = j;

					if ((screen + 2)->getBlockS(j) == Square2::BlockStage::TeleportOn) {
						on = false;
						name = "teleport";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::TeleportOff) {
						on = true;
						name = "teleport";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::TrapOn) {
						on = false;
						name = "trap";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::TrapOff) {
						on = true;
						name = "trap";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::DoorOff) {
						on = true;
						name = "door";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::DoorOn) {
						on = false;
						name = "door";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::ShootingBlockOff) {
						on = true;
						name = "sblock";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::ShootingBlockOn) {
						on = false;
						name = "sblock";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::EmiterOff) {
						on = true;
						name = "lmachine";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::EmiterOn) {
						on = false;
						name = "lmachine";
					}

					for (int k = 19; k < range; k++) {
						if (name == "teleport") {
							if ((screen + 2)->getBlockS(k) == Square2::BlockStage::TeleportOn || (screen + 2)->getBlockS(k) == Square2::BlockStage::TeleportOff) {
								aNr++;
							}
						}
						else if (name == "trap") {
							if ((screen + 2)->getBlockS(k) == Square2::BlockStage::TrapOff || (screen + 2)->getBlockS(k) == Square2::BlockStage::TrapOn) {
								aNr++;
							}
						}
						else if (name == "door") {
							if ((screen + 2)->getBlockS(k) == Square2::BlockStage::DoorOff || (screen + 2)->getBlockS(k) == Square2::BlockStage::DoorOn) {
								aNr++;
							}
						}
						else if (name == "sblock") {
							if ((screen + 2)->getBlockS(k) == Square2::BlockStage::ShootingBlockOff || (screen + 2)->getBlockS(k) == Square2::BlockStage::ShootingBlockOn) {
								aNr++;
							}
						}
						else if (name == "lmachine") {
							if ((screen + 2)->getBlockS(k) == Square2::BlockStage::EmiterOff || (screen + 2)->getBlockS(k) == Square2::BlockStage::EmiterOn) {
								aNr++;
							}
						}
					}

					(plateC + plateFlag)->setDeviceName(nr, name);
					(plateC + plateFlag)->setOn(nr, on);
					(plateC + plateFlag)->setDeviceID(nr, aNr);
					nr++;
				}
			}
			plateFlag++;
		}
		//
		if ((screen + 2)->getBlockS(i) == Square2::BlockStage::DoorOn || (screen + 2)->getBlockS(i) == Square2::BlockStage::DoorOff) {
			*(doorPosition + doorFlag) = i;
			if ((screen + 2)->getBlockS(i) == Square2::BlockStage::DoorOn)* (doorOn + doorFlag) = true;
			else *(doorOn + doorFlag) = false;
			doorFlag++;
		}
		//
		if ((screen + 2)->getBlockS(i) == Square2::BlockStage::ShootingBlockOff || (screen + 2)->getBlockS(i) == Square2::BlockStage::ShootingBlockOn) {
			*(shootingPosition + shootingFlag) = i;
			*(shootingType + shootingFlag) = int((screen + 2)->getShootingType(i)) + 1;
			if ((screen + 2)->getBlockS(i) == Square2::BlockStage::ShootingBlockOn)* (shootingOn + shootingFlag) = true;
			else *(shootingOn + shootingFlag) = false;
			shootingFlag++;
		}
		//
		if ((screen + 2)->getBlockS(i) == Square2::BlockStage::EmiterOff || (screen + 2)->getBlockS(i) == Square2::BlockStage::EmiterOn) {
			*(laserPosition + laserFlag) = i;
			*(laserType + laserFlag) = int((screen + 2)->getLaserType(i)) + 1;
			if ((screen + 2)->getBlockS(i) == Square2::BlockStage::EmiterOn)* (laserOn + laserFlag) = true;
			else *(laserOn + laserFlag) = false;
			laserFlag++;
		}
		//
		if ((screen + 2)->getBlockS(i) == Square2::BlockStage::Mirror) {
			*(mirrorPosition + mirrorFlag) = i;
			*(mirrorType + mirrorFlag) = int((screen + 2)->getMirrorType(i)) + 1;
			mirrorFlag++;
		}
		//
		if ((screen + 3)->getSwitchS(i) == Square2::SwitchStage::Receiver) {
			*(receiverPosition + receiverFlag) = i;
			*(receiverType + receiverFlag) = int((screen + 3)->getReceiverType(i)) + 1;
			Color color = (screen + 4)->getColor(i, Screen::Click::Device);
			int nr = 0;
			for (int j = 19; j < 179; j++) {
				if (i != j && (screen + 4)->getColor(j, Screen::Device) == color) {
					nr++;
				}
			}
			(receiverC + receiverFlag)->setDeviceNumber(nr);
			nr = 0;
			for (int j = 19; j < 179; j++) {
				if (i != j && (screen + 4)->getColor(j, Screen::Device) == color) {

					string name = "error";
					bool on = true;
					int aNr = 0;
					int range = j;

					if ((screen + 2)->getBlockS(j) == Square2::BlockStage::TeleportOn) {
						on = false;
						name = "teleport";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::TeleportOff) {
						on = true;
						name = "teleport";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::TrapOn) {
						on = false;
						name = "trap";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::TrapOff) {
						on = true;
						name = "trap";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::DoorOff) {
						on = true;
						name = "door";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::DoorOn) {
						on = false;
						name = "door";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::ShootingBlockOff) {
						on = true;
						name = "sblock";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::ShootingBlockOn) {
						on = false;
						name = "sblock";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::EmiterOff) {
						on = true;
						name = "lmachine";
					}
					else if ((screen + 2)->getBlockS(j) == Square2::BlockStage::EmiterOn) {
						on = false;
						name = "lmachine";
					}

					for (int k = 19; k < range; k++) {
						if (name == "teleport") {
							if ((screen + 2)->getBlockS(k) == Square2::BlockStage::TeleportOn || (screen + 2)->getBlockS(k) == Square2::BlockStage::TeleportOff) {
								aNr++;
							}
						}
						else if (name == "trap") {
							if ((screen + 2)->getBlockS(k) == Square2::BlockStage::TrapOff || (screen + 2)->getBlockS(k) == Square2::BlockStage::TrapOn) {
								aNr++;
							}
						}
						else if (name == "door") {
							if ((screen + 2)->getBlockS(k) == Square2::BlockStage::DoorOff || (screen + 2)->getBlockS(k) == Square2::BlockStage::DoorOn) {
								aNr++;
							}
						}
						else if (name == "sblock") {
							if ((screen + 2)->getBlockS(k) == Square2::BlockStage::ShootingBlockOff || (screen + 2)->getBlockS(k) == Square2::BlockStage::ShootingBlockOn) {
								aNr++;
							}
						}
						else if (name == "lmachine") {
							if ((screen + 2)->getBlockS(k) == Square2::BlockStage::EmiterOff || (screen + 2)->getBlockS(k) == Square2::BlockStage::EmiterOn) {
								aNr++;
							}
						}
					}

					(receiverC + receiverFlag)->setDeviceName(nr, name);
					(receiverC + receiverFlag)->setOn(nr, on);
					(receiverC + receiverFlag)->setDeviceID(nr, aNr);
					nr++;
				}
			}
			receiverFlag++;
		}
		//
	}
	
	stream.open("New Levelb.txt", ios::out);

	//startPosition  //winPosition
	stream << (screen + 1)->getStartPosition() << endl << (screen + 1)->getWinPosition() << endl;

	//Teleport
	stream << teleportNumber << endl;
	for (int i = 0; i < teleportNumber; i++) {
		stream << *(teleportPosition + i) << endl;
		stream << *(teleportPlace + i) << endl;
		stream << *(teleportOn + i) << endl;
	}

	//Trap
	stream << trapNumber << endl;
	for (int i = 0; i < trapNumber; i++) {
		stream << *(trapPosition + i) << endl;
		stream << *(trapOn + i) << endl;
	}

	//SlidingBlock
	stream << slidingNumber << endl;
	for (int i = 0; i < slidingNumber; i++) {
		stream << *(slidingPosition + i) << endl;
	}

	//Plate
	stream << plateNumber << endl;
	for (int i = 0; i < plateNumber; i++) {
		stream << *(platePosition + i) << endl;
		stream << (plateC + i)->getDeviceNumber() << endl;
		for (int j = 0; j < (plateC + i)->getDeviceNumber(); j++) {
			stream << (plateC + i)->getDeviceName(j) << endl;
			stream << (plateC + i)->getDeviceID(j) << endl;
			stream << (plateC + i)->getOn(j) << endl;
		}
	}

	//Door
	stream << doorNumber << endl;
	for (int i = 0; i < doorNumber; i++) {
		stream << *(doorPosition + i) << endl;
		stream << *(doorOn + i) << endl;
	}

	//ShootingBlock
	stream << shootingNumber << endl;
	for (int i = 0; i < shootingNumber; i++) {
		stream << *(shootingPosition + i) << endl;
		stream << *(shootingType + i) << endl;
		stream << "1500" << endl;
		stream << *(shootingOn + i) << endl;
	}

	//LaserMachine
	stream << laserNumber << endl;
	for (int i = 0; i < laserNumber; i++) {
		stream << *(laserPosition + i) << endl;
		stream << *(laserType + i) << endl;
		stream << *(laserOn + i) << endl;
	}

	//Mirror
	stream << mirrorNumber << endl;
	for (int i = 0; i < mirrorNumber; i++) {
		stream << *(mirrorPosition + i) << endl;
		stream << *(mirrorType + i) << endl;
	}

	//LaserReceiver
	stream << receiverNumber << endl;
	for (int i = 0; i < receiverNumber; i++) {
		stream << *(receiverPosition + i) << endl;
		stream << *(receiverType + i) << endl;
		stream << (receiverC + i)->getDeviceNumber() << endl;
		for (int j = 0; j < (receiverC + i)->getDeviceNumber(); j++) {
			stream << (receiverC + i)->getDeviceName(j) << endl;
			stream << (receiverC + i)->getDeviceID(j) << endl;
			stream << (receiverC + i)->getOn(j) << endl;
		}
	}

	stream.close();
}

Editor::Editor(){
	stage = Screen::Stage::MapS;
	screen = new Screen[5];
	(screen + 0)->setStage(Screen::Stage::MapS);
	(screen + 1)->setStage(Screen::Stage::TargetS);
	(screen + 2)->setStage(Screen::Stage::BlocksS);
	(screen + 3)->setStage(Screen::Stage::SwitchS);
	(screen + 4)->setStage(Screen::Stage::Connection);
	counterTexture.loadFromFile("Img/Stage.png");
	stageCounter.setSize({ 175,31 });
	stageCounter.setTexture(&counterTexture);
	stageCounter.setTextureRect({ 0,0,175,31 });
	stageCounter.setPosition({ 633,24 });
	start = false;
	stop = false;
	(screen + 2)->setContent(17, Square2::BlockStage::SlidingBlock);
	delayClock.restart();
}

Editor::Type Editor::run(RenderWindow& window) {

	if (delayClock.getElapsedTime().asSeconds() >= 0.2) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			return Type::Exit;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			delayClock.restart();
			if (stage == Screen::Stage::TargetS) {
				stage = Screen::Stage::MapS;
				(screen + 1)->setStage(Screen::Stage::TargetS);
				start = false;
				stop = false;
				stageCounter.setTextureRect({ 0,0,175,31 });
			}
			else if (stage == Screen::Stage::BlocksS) {
				stage = Screen::Stage::TargetS;
				(screen + 2)->setStage(Screen::Stage::BlocksS);
				stageCounter.setTextureRect({ 0,31,175,31 });
			}
			else if (stage == Screen::Stage::SwitchS) {
				stage = Screen::Stage::BlocksS;
				(screen + 3)->setStage(Screen::Stage::SwitchS);
				(screen + 2)->setContent(17, Square2::BlockStage::SlidingBlock);
				stageCounter.setTextureRect({ 0,62,175,31 });
			}
			else if (stage == Screen::Stage::Connection) {
				stage = Screen::Stage::SwitchS;
				(screen + 3)->setContent(17, Square2::SwitchStage::Plate);
				(screen + 4)->setStage(Screen::Stage::Connection);
				stageCounter.setTextureRect({ 0,93,175,31 });
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			delayClock.restart();
			if (stage == Screen::Stage::MapS) {
				stage = Screen::Stage::TargetS;
				stageCounter.setTextureRect({ 0,31,175,31 });
			}
			else if (stage == Screen::Stage::TargetS) {
				if (start && stop) {
					stage = Screen::Stage::BlocksS;
					(screen + 2)->setContent(17, Square2::BlockStage::SlidingBlock);
					stageCounter.setTextureRect({ 0,62,175,31 });
				}
			}
			else if (stage == Screen::Stage::BlocksS) {
				stage = Screen::Stage::SwitchS;
				(screen + 2)->setContent(17, Square2::BlockStage::NoneB);
				(screen + 3)->setContent(17, Square2::SwitchStage::Plate);
				stageCounter.setTextureRect({ 0,93,175,31 });
			}
			else if (stage == Screen::Stage::SwitchS) {
				stage = Screen::Stage::Connection;
				(screen + 3)->setContent(17, Square2::SwitchStage::NoneSw);
				stageCounter.setTextureRect({ 0,124,175,31 });
			}
			else if (stage == Screen::Stage::Connection) {
				stage = Screen::Stage::SaveS;
				stageCounter.setTextureRect({ 0,124,175,31 });
			}
		}
	}
	if (delayClock.getElapsedTime().asSeconds() < 0.15) return Type::None;

	if (stage == Screen::Stage::MapS) {

		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i vec = Mouse::getPosition(window);

			int number = VectorConverter::convert(vec).asNumber();
			if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {
				(screen + 0)->setContent(number, Square2::MapStage::Wall);
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Right)) {
			Vector2i vec = Mouse::getPosition(window);

			if (vec.x > 0 && vec.x < 1440 && vec.y > 0 && vec.y < 880) {

				int number = VectorConverter::convert(vec).asNumber();
				if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {
					(screen + 0)->setContent(number, Square2::MapStage::Floor);
				}
			}
		}
	}
	else if (stage == Screen::Stage::TargetS) {

		if (Mouse::isButtonPressed(Mouse::Left) && !start) {
			Vector2i vec = Mouse::getPosition(window);

			int number = VectorConverter::convert(vec).asNumber();
			if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {

				if ((screen + 0)->getMapS(number) == Square2::MapStage::Floor) {

					if ((screen + 1)->getTargetS(number) == Square2::TargetStage::Win) {
						stop = false;
					}

					(screen + 1)->setContent(number, Square2::TargetStage::Start);
					start = true;
				}
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Right) && !stop) {
			Vector2i vec = Mouse::getPosition(window);

			if (vec.x > 0 && vec.x < 1440 && vec.y > 0 && vec.y < 880) {

				int number = VectorConverter::convert(vec).asNumber();
				if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {

					if ((screen + 0)->getMapS(number) == Square2::MapStage::Floor) {

						if ((screen + 1)->getTargetS(number) == Square2::TargetStage::Start) {
							start = false;
						}

						(screen + 1)->setContent(number, Square2::TargetStage::Win);
						stop = true;
					}
				}
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Button::Middle)) {
			Vector2i vec = Mouse::getPosition(window);

			if (vec.x > 0 && vec.x < 1440 && vec.y > 0 && vec.y < 880) {

				int number = VectorConverter::convert(vec).asNumber();
				if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {

					if ((screen + 1)->getTargetS(number) == Square2::TargetStage::Start) {
						start = false;
					}
					else if ((screen + 1)->getTargetS(number) == Square2::TargetStage::Win) {
						stop = false;
					}

					(screen + 1)->setContent(number, Square2::TargetStage::NoneT);
				}
			}
		}
	}
	else if (stage == Screen::Stage::BlocksS) {

		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			Vector2i vec = Mouse::getPosition(window);

			if (vec.x > 0 && vec.x < 1440 && vec.y > 0 && vec.y < 880) {

				int number = VectorConverter::convert(vec).asNumber();

				if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {

					if ((screen + 0)->getMapS(number) == Square2::MapStage::Floor && (screen + 1)->getTargetS(number) == Square2::TargetStage::NoneT) {

						if ((screen + 2)->getBlockS(17) == Square2::BlockStage::SlidingBlock ||
							(screen + 2)->getBlockS(17) == Square2::BlockStage::TrapOn ||
							(screen + 2)->getBlockS(17) == Square2::BlockStage::DoorOn ||
							(screen + 2)->getBlockS(17) == Square2::BlockStage::TeleportOn) {

							(screen + 2)->setContent(number, (screen + 2)->getBlockS(17));
						}
						else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::ShootingBlockOn) {
							(screen + 2)->setContent(number, Square2::BlockStage::ShootingBlockOn, (screen + 2)->getShootingType(17));
						}
						else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::EmiterOn) {
							(screen + 2)->setContent(number, Square2::BlockStage::EmiterOn, (screen + 2)->getLaserType(17));
						}
						else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::Mirror) {
							(screen + 2)->setContent(number, Square2::BlockStage::Mirror, (screen + 2)->getMirrorType(17));
						}
					}
				}
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Button::Right)) {

			if ((screen + 2)->getBlockS(17) == Square2::BlockStage::Mirror || (screen + 2)->getBlockS(17) == Square2::BlockStage::SlidingBlock) return None;

			Vector2i vec = Mouse::getPosition(window);

			if (vec.x > 0 && vec.x < 1440 && vec.y > 0 && vec.y < 880) {

				int number = VectorConverter::convert(vec).asNumber();

				if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {

					if ((screen + 0)->getMapS(number) == Square2::MapStage::Floor && (screen + 1)->getTargetS(number) == Square2::TargetStage::NoneT) {

						if ((screen + 2)->getBlockS(17) == Square2::BlockStage::TrapOn) {
							(screen + 2)->setContent(number, Square2::BlockStage::TrapOff);
						}
						else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::DoorOn) {
							(screen + 2)->setContent(number, Square2::BlockStage::DoorOff);
						}
						else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::TeleportOn) {
							(screen + 2)->setContent(number, Square2::BlockStage::TeleportOff);
						}
						else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::ShootingBlockOn) {
							(screen + 2)->setContent(number, Square2::BlockStage::ShootingBlockOff, (screen + 2)->getShootingType(17));
						}
						else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::EmiterOn) {
							(screen + 2)->setContent(number, Square2::BlockStage::EmiterOff, (screen + 2)->getLaserType(17));
						}
					}
				}
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Button::Middle)) {
			Vector2i vec = Mouse::getPosition(window);

			if (vec.x > 0 && vec.x < 1440 && vec.y > 0 && vec.y < 880) {

				int number = VectorConverter::convert(vec).asNumber();

				if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {
					(screen + 2)->setContent(number, Square2::BlockStage::NoneB);
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::W)) {
			delayClock.restart();

			if ((screen + 2)->getBlockS(17) == Square2::BlockStage::SlidingBlock) {
				(screen + 2)->setContent(17, Square2::BlockStage::Mirror, Mirror::Type::C1);
			}
			else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::TrapOn) {
				(screen + 2)->setContent(17, Square2::BlockStage::SlidingBlock);
			}
			else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::DoorOn) {
				(screen + 2)->setContent(17, Square2::BlockStage::TrapOn);
			}
			else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::TeleportOn) {
				(screen + 2)->setContent(17, Square2::BlockStage::DoorOn);
			}
			else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::ShootingBlockOn) {
				if ((screen + 2)->getShootingType(17) == ShootingBlock::Type::A1) {
					(screen + 2)->setContent(17, Square2::BlockStage::TeleportOn);
				}
				else {
					ShootingBlock::Type type = (screen + 2)->getShootingType(17);
					type = ShootingBlock::Type(type - 1);
					(screen + 2)->setContent(17, Square2::BlockStage::ShootingBlockOn, type);
				}
			}
			else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::EmiterOn) {
				if ((screen + 2)->getLaserType(17) == LaserMachine::Type::A1) {
					(screen + 2)->setContent(17, Square2::BlockStage::ShootingBlockOn, ShootingBlock::Type::D1);
				}
				else {
					LaserMachine::Type type = (screen + 2)->getLaserType(17);
					type = LaserMachine::Type(type - 1);
					(screen + 2)->setContent(17, Square2::BlockStage::EmiterOn, type);
				}
			}
			else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::Mirror) {
				if ((screen + 2)->getMirrorType(17) == Mirror::Type::A1) {
					(screen + 2)->setContent(17, Square2::BlockStage::EmiterOn, LaserMachine::Type::D1);
				}
				else {
					Mirror::Type type = (screen + 2)->getMirrorType(17);
					type = Mirror::Type(type - 1);
					(screen + 2)->setContent(17, Square2::BlockStage::Mirror, type);
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			delayClock.restart();

			if ((screen + 2)->getBlockS(17) == Square2::BlockStage::SlidingBlock) {
				(screen + 2)->setContent(17, Square2::BlockStage::TrapOn);
			}
			else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::TrapOn) {
				(screen + 2)->setContent(17, Square2::BlockStage::DoorOn);
			}
			else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::DoorOn) {
				(screen + 2)->setContent(17, Square2::BlockStage::TeleportOn);
			}
			else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::TeleportOn) {
				(screen + 2)->setContent(17, Square2::BlockStage::ShootingBlockOn, ShootingBlock::Type::A1);
			}
			else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::ShootingBlockOn) {
				if ((screen + 2)->getShootingType(17) == ShootingBlock::Type::D1) {
					(screen + 2)->setContent(17, Square2::BlockStage::EmiterOn, LaserMachine::Type::A1);
				}
				else {
					ShootingBlock::Type type = (screen + 2)->getShootingType(17);
					type = ShootingBlock::Type(type + 1);
					(screen + 2)->setContent(17, Square2::BlockStage::ShootingBlockOn, type);
				}
			}
			else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::EmiterOn) {
				if ((screen + 2)->getLaserType(17) == LaserMachine::Type::D1) {
					(screen + 2)->setContent(17, Square2::BlockStage::Mirror, Mirror::Type::A1);
				}
				else {
					LaserMachine::Type type = (screen + 2)->getLaserType(17);
					type = LaserMachine::Type(type + 1);
					(screen + 2)->setContent(17, Square2::BlockStage::EmiterOn, type);
				}
			}
			else if ((screen + 2)->getBlockS(17) == Square2::BlockStage::Mirror) {
				if ((screen + 2)->getMirrorType(17) == Mirror::Type::C1) {
					(screen + 2)->setContent(17, Square2::BlockStage::SlidingBlock);
				}
				else {
					Mirror::Type type = (screen + 2)->getMirrorType(17);
					type = Mirror::Type(type + 1);
					(screen + 2)->setContent(17, Square2::BlockStage::Mirror, type);
				}
			}
		}
	}
	else if (stage == Screen::Stage::SwitchS) {

		if (Mouse::isButtonPressed(Mouse::Button::Left)) {

			Vector2i vec = Mouse::getPosition(window);

			if (vec.x > 0 && vec.x < 1440 && vec.y > 0 && vec.y < 880) {

				int number = VectorConverter::convert(vec).asNumber();

				if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {

					if ((screen + 0)->getMapS(number) == Square2::MapStage::Floor &&
						(screen + 1)->getTargetS(number) == Square2::TargetStage::NoneT &&
						(screen + 2)->getBlockS(number) == Square2::BlockStage::NoneB) {

						if ((screen + 3)->getSwitchS(17) == Square2::SwitchStage::Plate) {
							(screen + 3)->setContent(number, Square2::Plate);
						}
						else {
							(screen + 3)->setContent(number, Square2::SwitchStage::Receiver, (screen + 3)->getReceiverType(17));
						}
					}
				}
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Button::Middle)) {

			Vector2i vec = Mouse::getPosition(window);

			if (vec.x > 0 && vec.x < 1440 && vec.y > 0 && vec.y < 880) {

				int number = VectorConverter::convert(vec).asNumber();

				if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {
					(screen + 3)->setContent(number, Square2::SwitchStage::NoneSw);
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::W)) {
			delayClock.restart();

			if ((screen + 3)->getSwitchS(17) == Square2::SwitchStage::Plate) {
				(screen + 3)->setContent(17, Square2::SwitchStage::Receiver, LaserReceiver::Type::D1);
			}
			else {
				if ((screen + 3)->getReceiverType(17) == LaserReceiver::Type::A1) {
					(screen + 3)->setContent(17, Square2::SwitchStage::Plate);
				}
				else {
					LaserReceiver::Type type = (screen + 3)->getReceiverType(17);
					type = LaserReceiver::Type(type - 1);
					(screen + 3)->setContent(17, Square2::SwitchStage::Receiver, type);
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			delayClock.restart();
			
			if ((screen + 3)->getSwitchS(17) == Square2::SwitchStage::Plate) {
				(screen + 3)->setContent(17, Square2::SwitchStage::Receiver, LaserReceiver::Type::A1);
			}
			else {
				if ((screen + 3)->getReceiverType(17) == LaserReceiver::Type::D1) {
					(screen + 3)->setContent(17, Square2::SwitchStage::Plate);
				}
				else {
					LaserReceiver::Type type = (screen + 3)->getReceiverType(17);
					type = LaserReceiver::Type(type + 1);
					(screen + 3)->setContent(17, Square2::SwitchStage::Receiver, type);
				}
			}
		}
	}
	else if (stage == Screen::Stage::Connection) {

		if (Mouse::isButtonPressed(Mouse::Left)) {
			delayClock.restart();

			Vector2i vec = Mouse::getPosition(window);

			if (vec.x > 0 && vec.x < 1440 && vec.y > 0 && vec.y < 880) {

				int number = VectorConverter::convert(vec).asNumber();

				if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {

					if (clickType == Screen::Teleport) {

						if (((screen + 0)->getMapS(number) == Square2::MapStage::Floor && (screen + 2)->getBlockS(number) == Square2::BlockStage::NoneB && 
							(screen + 3)->getSwitchS(number) != Square2::SwitchStage::Receiver) ||
							(screen + 2)->getBlockS(number) == Square2::BlockStage::SlidingBlock ||
							(screen + 2)->getBlockS(number) == Square2::BlockStage::Mirror ||
							(screen + 2)->getBlockS(number) == Square2::BlockStage::TrapOff ||
							(screen + 2)->getBlockS(number) == Square2::BlockStage::TrapOn) {

							if ((screen + 4)->findColor((screen + 4)->getColor(17, Screen::Teleport), Screen::Teleport) == false) {
								(screen + 4)->setColor(number, (screen + 4)->getColor(17, Screen::Teleport), Screen::Teleport);
							}
						}
					}
					else if (clickType == Screen::Device) {

						if ((screen + 2)->getBlockS(number) != Square2::BlockStage::NoneB &&
							(screen + 2)->getBlockS(number) != Square2::BlockStage::SlidingBlock &&
							(screen + 2)->getBlockS(number) != Square2::BlockStage::Mirror) {

							(screen + 4)->setColor(number, (screen + 4)->getColor(17, Screen::Device), Screen::Device);
						}
					}
				}
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Right)) {
			delayClock.restart();

			Vector2i vec = Mouse::getPosition(window);

			if (vec.x > 0 && vec.x < 1440 && vec.y > 0 && vec.y < 880) {

				int number = VectorConverter::convert(vec).asNumber();

				if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {
					if ((screen + 3)->getSwitchS(number) != Square2::SwitchStage::NoneSw) {
						clickType = Screen::Click::Device;
						Color color = (screen + 4)->getColor(number, Screen::Device);
						if (color == Color::Transparent) {
							(screen + 4)->setNewColor(number, Screen::Device);
							(screen + 4)->setColor(17, (screen + 4)->getColor(number, Screen::Device), Screen::Device);
							(screen + 4)->setColor(17, Color::Transparent, Screen::Teleport);
						}
						else {
							(screen + 4)->setColor(17, color, Screen::Device);
						}
					}
					else if ((screen + 2)->getBlockS(number) == Square2::BlockStage::TeleportOn || (screen + 2)->getBlockS(number) == Square2::BlockStage::TeleportOff) {
						clickType = Screen::Click::Teleport;
						Color color = (screen + 4)->getColor(number, Screen::Teleport);
						if (color == Color::Transparent) {
							(screen + 4)->setNewColor(number, Screen::Teleport);
							(screen + 4)->setColor(17, (screen + 4)->getColor(number, Screen::Teleport), Screen::Teleport);
							(screen + 4)->setColor(17, Color::Transparent, Screen::Device);
						}
						else {
							(screen + 4)->setColor(17, color, Screen::Teleport);
						}
					}
				}
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Button::Middle)) {
			delayClock.restart();

			Vector2i vec = Mouse::getPosition(window);

			if (vec.x > 0 && vec.x < 1440 && vec.y > 0 && vec.y < 880) {

				int number = VectorConverter::convert(vec).asNumber();

				if (number >= 19 && number <= 178 && (number + 1) % 18 != 0 && number % 18 != 0) {

					if ((screen+2)->getBlockS(number) == Square2::BlockStage::TeleportOff || (screen + 2)->getBlockS(number) == Square2::BlockStage::TeleportOn) {
						(screen + 4)->clearColor((screen + 4)->getColor(number, Screen::Teleport), Screen::Teleport);
					}
					else if ((screen + 3)->getSwitchS(number) == Square2::SwitchStage::Plate || (screen + 3)->getSwitchS(number) == Square2::SwitchStage::Receiver) {
						(screen + 4)->clearColor((screen + 4)->getColor(number, Screen::Device), Screen::Device);
					}
					(screen + 4)->setColor(number, Color::Transparent, Screen::Device);
					(screen + 4)->setColor(number, Color::Transparent, Screen::Teleport);
					(screen + 4)->setColor(17, Color::Transparent, Screen::Device);
					(screen + 4)->setColor(17, Color::Transparent, Screen::Teleport);

					clickType = Screen::Click::NoneC;
				}
			}
		} 
	}
	else if (stage == Screen::Stage::SaveS) {
		save();
		return Type::Exit;
	}

	return Type::None;
}

void Editor::draw(RenderWindow& window) {
	if (stage == Screen::Stage::MapS) {
		(screen + 0)->draw(window);
		window.draw(stageCounter);
	}
	else if (stage == Screen::Stage::TargetS) {
		(screen + 0)->draw(window);
		(screen + 1)->draw(window);
		window.draw(stageCounter);
	}
	else if (stage == Screen::Stage::BlocksS) {
		(screen + 0)->draw(window);
		(screen + 1)->draw(window);
		(screen + 2)->draw(window);
		window.draw(stageCounter);
	}
	else if (stage == Screen::Stage::SwitchS) {
		(screen + 0)->draw(window);
		(screen + 1)->draw(window);
		(screen + 2)->draw(window);
		(screen + 3)->draw(window);
		window.draw(stageCounter);
	}
	else if (stage == Screen::Stage::Connection) {
		(screen + 0)->draw(window);
		(screen + 1)->draw(window);
		(screen + 2)->draw(window);
		(screen + 3)->draw(window);
		(screen + 4)->draw(window);
		window.draw(stageCounter);
	}
}

Editor::~Editor(){
	delete [] screen;
}