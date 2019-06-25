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
}

void Screen::setStage(Screen::Stage stage) {
	this->stage = stage;
	delete[] texture;

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
}

Screen::Stage Screen::getStage() {
	return stage;
}

void Screen::setContent(int number, Square2::MapStage content) {
	(squares + number)->setContent(content);
}

void Screen::setContent(int number, Square2::TargetStage content) {
	(squares + number)->setContent(content);
}

void Screen::setContent(int number, Square2::BlockStage content) {
	(squares + number)->setContent(content);
}

void Screen::setContent(int number, Square2::BlockStage content, ShootingBlock::Type type) {
	(squares + number)->setContent(content, type);
}

void Screen::setContent(int number, Square2::BlockStage content, LaserMachine::Type type) {
	(squares + number)->setContent(content, type);
}

void Screen::setContent(int number, Square2::BlockStage content, Mirror::Type type) {
	(squares + number)->setContent(content, type);
}

void Screen::setContent(int number, Square2::SwitchStage content, LaserReceiver::Type type) {
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

void Screen::draw(RenderWindow& window) {
	for (int i = 0; i < 198; i++) {
		window.draw(*(squares + i));
	}
}

Screen::~Screen() {
	delete[] squares;
	delete[] texture;
}