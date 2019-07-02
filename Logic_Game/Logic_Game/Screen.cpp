#include "Screen.hpp"

Screen::Screen() {
	squares = new Square2[198];
	stage = Screen::Stage::NoneS;
	texture = new Texture[0];
	int nr(0);
	for (int y = 0; y < 11; y++) {
		for (int x = 0; x < 18; x++) {
			(squares + nr)->setPosition(Vector2f{ float(80 * x),float(80 * y) });
			nr++;
		}
	}
	startPosition = 0;
	winPosition = 0;
	teleportNumber = 0;
	trapNumber = 0;
	slidingNumber = 0;
	plateNumber = 0;
	doorNumber = 0;
	shootingNumber = 0;
	emiterNumber = 0;
	mirrorNumber = 0;
	receiverNumber = 0;
}

void Screen::setStage(Screen::Stage stage) {
	delete[] texture;
	if (this->stage == Connection && stage != Connection) {
		delete [] shapes;
		delete [] shapes2;
	}
	this->stage = stage;

	if (stage == Screen::Stage::MapS) {
		texture = new Texture[1];
		texture->loadFromFile("Img/Square.png");
		for (int i = 0; i < 198; i++) {
			(squares + i)->setTexture(texture);
			if ((i >= 0 && i <= 17) || (i >= 180 && i <= 197) || (i % 18 == 0) || ((i + 1) % 18 == 0)) {
				(squares + i)->setContent(Square2::MapStage::Wall);
			}
			else {
				(squares + i)->setContent(Square2::MapStage::Floor);
			}
		}
	}
	else if (stage == Screen::Stage::TargetS) {
		texture = new Texture[1];
		texture->loadFromFile("Img/TargetStage.png");
		for (int i = 0; i < 198; i++) {
			(squares + i)->setTexture(texture);
			(squares + i)->setContent(Square2::TargetStage::NoneT);
		}
	}
	else if (stage == Screen::Stage::BlocksS) {
		texture = new Texture[4];
		(texture + 0)->loadFromFile("Img/BlockStage.png");
		(texture + 1)->loadFromFile("Img/ShootingBlockS.png");
		(texture + 2)->loadFromFile("Img/LaserMachineS.png");
		(texture + 3)->loadFromFile("Img/Mirror.png");
		for (int i = 0; i < 198; i++) {
			(squares + i)->setTexture(texture);
			(squares + i)->setContent(Square2::BlockStage::NoneB);
		}
	}
	else if (stage == Screen::Stage::SwitchS) {
		texture = new Texture[2];
		(texture + 0)->loadFromFile("Img/LaserReceiver.png");
		(texture + 1)->loadFromFile("Img/Plate.png");
		for (int i = 0; i < 198; i++) {
			(squares + i)->setTexture((texture + 1));
			(squares + i)->setContent(Square2::SwitchStage::NoneSw);
		}
	}
	else if (stage == Screen::Stage::Connection) {
		texture = new Texture[0];
		delete [] squares;
		shapes = new CircleShape[198];
		shapes2 = new CircleShape[198];
		int nr(0);
		for (int y = 0; y < 11; y++) {
			for (int x = 0; x < 18; x++) {
				(shapes + nr)->setRadius(20);
				(shapes + nr)->setOutlineColor(Color::Black);
				(shapes + nr)->setOutlineThickness(1);
				(shapes + nr)->setFillColor(Color::Transparent);
				(shapes + nr)->setOrigin(Vector2f{ -20,-20 });
				(shapes + nr)->setPosition(Vector2f{ float(80 * x),float(80 * y) });
				(shapes2 + nr)->setRadius(10);
				(shapes2 + nr)->setOutlineColor(Color::Black);
				(shapes2 + nr)->setOutlineThickness(1);
				(shapes2 + nr)->setFillColor(Color::Transparent);
				(shapes2 + nr)->setPosition(Vector2f{ float(80 * x),float(80 * y) });
				nr++;
			}
		}
	}
	else if (stage == Screen::Stage::SaveS) {
		texture = new Texture[0];
	}
	startPosition = 0;
	winPosition = 0;
	teleportNumber = 0;
	trapNumber = 0;
	slidingNumber = 0;
	plateNumber = 0;
	doorNumber = 0;
	shootingNumber = 0;
	emiterNumber = 0;
	mirrorNumber = 0;
	receiverNumber = 0;
}

Screen::Stage Screen::getStage() {
	return stage;
}

void Screen::setContent(int number, Square2::MapStage content) {
	(squares + number)->setContent(content);
}

void Screen::setContent(int number, Square2::TargetStage content) {
	(squares + number)->setContent(content);
	if (content == Square2::TargetStage::Start) startPosition = number;
	else if (content == Square2::TargetStage::Win) winPosition = number;
}

void Screen::setContent(int number, Square2::BlockStage content) {

	if (content == Square2::BlockStage::TeleportOff || content == Square2::BlockStage::TeleportOn) {
		if ((squares + number)->getBlockS() != Square2::BlockStage::TeleportOff && (squares + number)->getBlockS() != Square2::BlockStage::TeleportOn) {
			teleportNumber++;
		}
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::TeleportOff || (squares + number)->getBlockS() == Square2::BlockStage::TeleportOn) {
		teleportNumber--;
	}
	
	if (content == Square2::BlockStage::TrapOff || content == Square2::BlockStage::TrapOn) {
		if ((squares + number)->getBlockS() != Square2::BlockStage::TrapOff && (squares + number)->getBlockS() != Square2::BlockStage::TrapOn) {
			trapNumber++;
		}
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::TrapOff || (squares + number)->getBlockS() == Square2::BlockStage::TrapOn) {
		trapNumber--;
	}
	
	if (content == Square2::BlockStage::SlidingBlock) {
		if ((squares + number)->getBlockS() != Square2::BlockStage::SlidingBlock) {
			slidingNumber++;
		}
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::SlidingBlock) {
		slidingNumber--;
	}
	
	if (content == Square2::BlockStage::DoorOff || content == Square2::BlockStage::DoorOn) {
		if ((squares + number)->getBlockS() != Square2::BlockStage::DoorOn && (squares + number)->getBlockS() != Square2::BlockStage::DoorOff) {
			doorNumber++;
		}
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::DoorOff || (squares + number)->getBlockS() == Square2::BlockStage::DoorOn) {
		doorNumber--;
	}

	if ((squares + number)->getBlockS() == Square2::BlockStage::ShootingBlockOn || (squares + number)->getBlockS() == Square2::BlockStage::ShootingBlockOff) {
		if (content != Square2::BlockStage::ShootingBlockOn && content != Square2::BlockStage::ShootingBlockOff) shootingNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::EmiterOff || (squares + number)->getBlockS() == Square2::BlockStage::EmiterOn) {
		if (content != Square2::BlockStage::EmiterOff && content != Square2::BlockStage::EmiterOn) emiterNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::Mirror) {
		if (content != Square2::BlockStage::Mirror) mirrorNumber--;
	}

	(squares + number)->setTexture((texture + 0));
	(squares + number)->setContent(content);
}

void Screen::setContent(int number, Square2::BlockStage content, ShootingBlock::Type type) {
	if ((squares + number)->getBlockS() == Square2::BlockStage::TeleportOff || (squares + number)->getBlockS() == Square2::BlockStage::TeleportOn) {
		teleportNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::TrapOff || (squares + number)->getBlockS() == Square2::BlockStage::TrapOn) {
		trapNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::SlidingBlock) {
		slidingNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::DoorOff || (squares + number)->getBlockS() == Square2::BlockStage::DoorOn) {
		doorNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::EmiterOff || (squares + number)->getBlockS() == Square2::BlockStage::EmiterOn) {
		emiterNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::Mirror) {
		mirrorNumber--;
	}

	if ((squares + number)->getBlockS() != Square2::BlockStage::ShootingBlockOn && (squares + number)->getBlockS() != Square2::BlockStage::ShootingBlockOff) {
		shootingNumber++;
	}
	(squares + number)->setTexture((texture + 1));
	(squares + number)->setContent(content, type);
}

void Screen::setContent(int number, Square2::BlockStage content, LaserMachine::Type type) {
	if ((squares + number)->getBlockS() == Square2::BlockStage::TeleportOff || (squares + number)->getBlockS() == Square2::BlockStage::TeleportOn) {
		teleportNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::TrapOff || (squares + number)->getBlockS() == Square2::BlockStage::TrapOn) {
		trapNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::SlidingBlock) {
		slidingNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::DoorOff || (squares + number)->getBlockS() == Square2::BlockStage::DoorOn) {
		doorNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::ShootingBlockOn || (squares + number)->getBlockS() == Square2::BlockStage::ShootingBlockOff) {
		shootingNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::Mirror) {
		mirrorNumber--;
	}

	if ((squares + number)->getBlockS() != Square2::BlockStage::EmiterOff && (squares + number)->getBlockS() != Square2::BlockStage::EmiterOn) {
		emiterNumber++;
	}
	(squares + number)->setTexture((texture + 2));
	(squares + number)->setContent(content, type);
}

void Screen::setContent(int number, Square2::BlockStage content, Mirror::Type type) {
	if ((squares + number)->getBlockS() == Square2::BlockStage::TeleportOff || (squares + number)->getBlockS() == Square2::BlockStage::TeleportOn) {
		teleportNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::TrapOff || (squares + number)->getBlockS() == Square2::BlockStage::TrapOn) {
		trapNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::SlidingBlock) {
		slidingNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::DoorOff || (squares + number)->getBlockS() == Square2::BlockStage::DoorOn) {
		doorNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::ShootingBlockOn || (squares + number)->getBlockS() == Square2::BlockStage::ShootingBlockOff) {
		shootingNumber--;
	}
	else if ((squares + number)->getBlockS() == Square2::BlockStage::EmiterOff || (squares + number)->getBlockS() == Square2::BlockStage::EmiterOn) {
		emiterNumber--;
	}

	if ((squares + number)->getBlockS() != Square2::BlockStage::Mirror) {
		mirrorNumber++;
	}
	(squares + number)->setTexture((texture + 3));
	(squares + number)->setContent(content, type);
}

void Screen::setContent(int number, Square2::SwitchStage content, LaserReceiver::Type type) {
	if (content == Square2::SwitchStage::NoneSw || content == Square2::SwitchStage::Plate) {
		(squares + number)->setTexture((texture + 1));
	}
	else {
		(squares + number)->setTexture((texture + 0));
	}
	
	if (content == Square2::SwitchStage::Plate) {
		if((squares + number)->getSwitchS() != Square2::SwitchStage::Plate) {
			plateNumber++;
		}
	}
	else if ((squares + number)->getSwitchS() == Square2::SwitchStage::Plate) {
		plateNumber--;
	}
	
	if (content == Square2::SwitchStage::Receiver) {
		if ((squares + number)->getSwitchS() != Square2::SwitchStage::Receiver) {
			receiverNumber++;
		}
	}
	else if ((squares + number)->getSwitchS() == Square2::SwitchStage::Receiver) {
		receiverNumber--;
	}

	(squares + number)->setContent(content, type);
}

Square2::MapStage Screen::getMapS(int number) {
	return (squares + number)->getMapS();
}

Square2::TargetStage Screen::getTargetS(int number) {
	return (squares + number)->getTargetS();
}

Square2::BlockStage Screen::getBlockS(int number) {
	return (squares + number)->getBlockS();
}

ShootingBlock::Type Screen::getShootingType(int number) {
	return (squares + number)->getShootingType();
}

LaserMachine::Type Screen::getLaserType(int number) {
	return (squares + number)->getLaserType();
}

Mirror::Type Screen::getMirrorType(int number) {
	return (squares + number)->getMirrorType();
}

Square2::SwitchStage Screen::getSwitchS(int number) {
	return (squares + number)->getSwitchS();
}

LaserReceiver::Type Screen::getReceiverType(int number) {
	return (squares + number)->getReceiverType();
}

void Screen::setNewColor(int nr, Click clickType) {
	if (clickType != NoneC) {
		bool other(false);
		bool r(false), g(false), b(false);
		bool rc(false), gc(false), bc(false);
		int re(0), gr(0), bl(0);

		while (!other) {
			if (!r) {
				re = rand() % 256;
				r = true;
			}
			if (!g) {
				gr = rand() % 256;
				g = true;
			}
			if (!b) {
				bl = rand() % 256;
				b = true;
			}

			for (int i = 17; i < 179; i++) {
				if (i % 18 != 0 && (i + 1) % 18 != 0) {
					Color color;
					if (clickType == Device) color = (shapes + i)->getFillColor();
					else color = (shapes2 + i)->getFillColor();
					if (r && !rc) {
						if (color.r == re) {
							r = false;
						}
					}
					if (g && !gc) {
						if (color.g == gr) {
							g = false;
						}
					}
					if (b && !bc) {
						if (color.b == bl) {
							b = false;
						}
					}
					if (!r && !g && !b) break;
					else if (rc && !g && !b) break;
					else if (rc && gc && !b) break;
					else if (rc && !g && bc) break;
					else if (!r && gc && !b) break;
					else if (!r && gc && bc) break;
					else if (!r && !g && bc) break;
				}
			}

			if (r) rc = true;
			if (g) gc = true;
			if (b) bc = true;
			if (rc && gc && bc) other = true;
		}

		if (clickType == Device) (shapes + nr)->setFillColor(Color::Color(re, gr, bl, 180));
		else (shapes2 + nr)->setFillColor(Color::Color(re, gr, bl, 180));
	}
}

void Screen::setColor(int number, Color color, Click clickType) {
	if (clickType == Device) (shapes + number)->setFillColor(color);
	else if(clickType == Teleport) (shapes2 + number)->setFillColor(color);
}

Color Screen::getColor(int number, Click clickType) {
	if (clickType == Device) return (shapes + number)->getFillColor();
	else if (clickType == Teleport) return (shapes2 + number)->getFillColor();
	else return Color::Transparent;
}

bool Screen::findColor(Color color, Click clickType) {
	int a = 0;
	for (int i = 19; i <= 178; i++) {
		if (i % 18 != 0 && (i + 1) % 18 != 0) {
			if (clickType == Teleport) {
				if ((shapes2 + i)->getFillColor() == color) {
					a++;
					if (a > 1) return true;
				}
			}
			else if (clickType == Device) {
				if ((shapes + i)->getFillColor() == color) {
					a++;
					if (a > 1) return true;
				}
			}
		}
	}
	return false;
}

void Screen::clearColor(Color color, Click clickType) {
	for (int i = 19; i <= 178; i++) {
		if (i % 18 != 0 && (i + 1) % 18 != 0) {
			if (clickType == Teleport) {
				if ((shapes2 + i)->getFillColor() == color) {
					(shapes2 + i)->setFillColor(Color::Transparent);
				}
			}
			else if (clickType == Device) {
				if ((shapes + i)->getFillColor() == color) {
					(shapes + i)->setFillColor(Color::Transparent);
				}
			}
		}
	}
}

int Screen::getStartPosition() {
	return startPosition;
}

int Screen::getWinPosition() {
	return winPosition;
}

int Screen::getTeleportNumber() {
	return teleportNumber;
}

int Screen::getTrapNumber() {
	return trapNumber;
}

int Screen::getSlidingNumber() {
	return slidingNumber;
}

int Screen::getPlateNumber() {
	return plateNumber;
}

int Screen::getDoorNumber() {
	return doorNumber;
}

int Screen::getShootingNumber() {
	return shootingNumber;
}

int Screen::getEmiterNumber() {
	return emiterNumber;
}

int Screen::getMirrorNumber() {
	return mirrorNumber;
}

int Screen::getReceiverNumber() {
	return receiverNumber;
}

void Screen::draw(RenderWindow& window) {
	if (stage != Connection) {
		for (int i = 0; i < 198; i++) {
			window.draw(*(squares + i));
		}
	}
	else {
		for (int i = 19; i <= 178; i++) {
			if (i % 18 != 0 && (i + 1) % 18 != 0) {
				window.draw(*(shapes + i));
				window.draw(*(shapes2 + i));
			}
		}
		window.draw(*(shapes + 17));
		window.draw(*(shapes2 + 17));
	}
}

Screen::~Screen() {
	if (stage != Connection) {
		delete[] squares;	
	}
	else {
		delete [] shapes;
		delete [] shapes2;
	}
	delete[] texture;
}