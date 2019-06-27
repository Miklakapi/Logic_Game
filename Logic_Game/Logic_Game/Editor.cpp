#include "Editor.hpp"

void Editor::save() {
	fstream stream("New Level.txt", ios::out);
	for (int i = 0; i < 198; i++) {
		if ((screen + 0)->getMapS(i) == Square2::MapStage::Wall) {
			stream << "#";
		}
		else {
			stream << "-";
		}
	}
	stream.close();

	stream.open("New LevelB.txt", ios::out);


	//Start / Win Position
	int startNumber(0), stopNumber(0);
	for (int i = 0; i < 198; i++) {
		if ((screen + 1)->getTargetS(i) == Square2::TargetStage::Start) {
			startNumber = i;
			if (stopNumber != 0) break;
		}
		else if ((screen + i)->getTargetS(i) == Square2::TargetStage::Win) {
			stopNumber = i;
			if (startNumber != 0) break;
		}
	}
	stream << startNumber << endl << stopNumber << endl;

	//Teleports Positions
	int teleportNumber(0);
	for (int i = 0; i < 198; i++) {
		if ((screen + 2)->getBlockS(i) == Square2::BlockStage::TeleportOn || (screen + 2)->getBlockS(i) == Square2::BlockStage::TeleportOff) {
			teleportNumber++;
		}
	}

	int tele(0);
	int* teleportPosition = new int[teleportNumber];
	bool* teleportOn = new bool[teleportNumber];
	for (int i = 0; i < 198; i++) {
		if ((screen + 2)->getBlockS(i) == Square2::BlockStage::TeleportOn) {
			*(teleportPosition + tele) = i;
			*(teleportOn) = true;
			tele++;
		}
		else if ((screen + 2)->getBlockS(i) == Square2::BlockStage::TeleportOff) {
			*(teleportPosition + tele) = i;
			*(teleportOn) = false;
			tele++;
		}
	}

	///////
	/////// Zrobic to jedna petla
	///////
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
		else if (Mouse::isButtonPressed(Mouse::Right)) { ///////////////////////Do poprawy/////////////////////////////
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
	else if (stage == Screen::Stage::SaveS) {

	}
}

Editor::~Editor(){
	delete [] screen;
}