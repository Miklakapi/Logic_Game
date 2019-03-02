#include "ShootingBlocks.hpp"

ShootingBlocks::ShootingBlocks(int number, string textureFile, string textureFIle2){
	ShootingBlock::setBlockTexture(textureFile);
	Mine::setMineTexture(textureFIle2);
	this->number = number;
	block = new ShootingBlock[number];
}

void ShootingBlocks::setPosition(int number, Vector2f position) {
	(block + number)->setBlockPosition(position);
}

void ShootingBlocks::setSize(int number, Vector2f size) {
	(block + number)->setSize(size);
}

void ShootingBlocks::setDelay(int number, int delay) {
	(block + number)->setDelay(delay);
}

int ShootingBlocks::getDelay(int number) {
	return (block + number)->getDelay();
}

void ShootingBlocks::setType(int number, ShootingBlock::Type type) {
	(block + number)->setType(type);
}

ShootingBlock::Type ShootingBlocks::getType(int number) {
	return (block + number)->getType();
}

int ShootingBlocks::getMinerNr(int number) {
	return (block + number)->getMinerNr();
}

void ShootingBlocks::setOn(int number, bool on) {
	(block + number)->setOn(on);
}

bool ShootingBlocks::isOn(int number) {
	return (block + number)->isOn();
}

ShootingBlock* ShootingBlocks::getBlock() {
	return block;
}

int ShootingBlocks::getNumber() {
	return number;
}

void ShootingBlocks::draw(RenderWindow& window) {
	for (int i = 0; i < number; i++) {
		(block + i)->draw(window);
	}
}

void ShootingBlocks::run(Map& map, Door* door, int number, SlidingBlock* block, int number2, Mirror* mirror, int number3, LaserMachine* machine, int number4) {
	for (int i = 0; i < this->number; i++) {
		(this->block + i)->run();

		ShootingBlock::Type type = (this->block + i)->getType();
		Mine* mine = (this->block + i)->getMine();

		for (int j = 0; j < (this->block + i)->getMinerNr(); j++) {
			if (!(mine + j)->getExist()) continue;

			if ((mine + j)->getMoveNr() == 9) {
				if ((mine + j)->getDirection() == Mine::Up || (mine + j)->getDirection() == Mine::Left) {
					if (map.getType(VectorConverter::convert((mine + j)->getPosition()).asNumber()) == Square::Wall) {
						(mine + j)->setExist(false);
					}

					for (int k = 0; k < number4; k++) {
						if ((mine + j)->getPosition().x + 12 > (machine + k)->getPosition().x &&
							(mine + j)->getPosition().x < (machine + k)->getPosition().x + 80 &&
							(mine + j)->getPosition().y + 12 >(machine + k)->getPosition().y &&
							(mine + j)->getPosition().y < (machine + k)->getPosition().y + 80) {
							(mine + j)->setExist(false);
						}
					}

					for (int k = 0; k < number; k++) {
						if ((mine + j)->getPosition().x + 12 > (this->block + k)->getPosition().x &&
							(mine + j)->getPosition().x < (this->block + k)->getPosition().x + 80 &&
							(mine + j)->getPosition().y + 12 >(this->block + k)->getPosition().y &&
							(mine + j)->getPosition().y < (this->block + k)->getPosition().y + 80) {
							(mine + j)->setExist(false);
						}
					}
				}
				else {



				}
			}

			for (int k = 0; k < number; k++) {
				if ((door + k)->isOpen()) continue;
				if ((mine + j)->getPosition().x + 12 > (door + k)->getPosition().x &&
					(mine + j)->getPosition().x < (door + k)->getPosition().x + 80 &&
					(mine + j)->getPosition().y + 12 >(door + k)->getPosition().y &&
					(mine + j)->getPosition().y < (door + k)->getPosition().y + 80) {
					(mine + j)->setExist(false);
				}
			}

			for (int k = 0; k < number2; k++) {
				if (!(block + k)->getExist()) continue;
				if ((mine + j)->getPosition().x + 12 > (block + k)->getPosition().x &&
					(mine + j)->getPosition().x < (block + k)->getPosition().x + 80 &&
					(mine + j)->getPosition().y + 12 >(block + k)->getPosition().y &&
					(mine + j)->getPosition().y < (block + k)->getPosition().y + 80) {
					(mine + j)->setExist(false);
				}
			}

			for (int k = 0; k < number3; k++) {
				if (!(mirror + k)->getExist()) continue;
				if ((mine + j)->getPosition().x + 12 > (mirror + k)->getPosition().x &&
					(mine + j)->getPosition().x < (mirror + k)->getPosition().x + 80 &&
					(mine + j)->getPosition().y + 12 >(mirror + k)->getPosition().y &&
					(mine + j)->getPosition().y < (mirror + k)->getPosition().y + 80) {
					(mine + j)->setExist(false);
				}
			}
		}
	}
}

void ShootingBlocks::reset(int number) {
	(block + number)->reset();
}

void ShootingBlocks::reset() {
	for (int i = 0; i < number; i++) {
		(block + i)->reset();
	}
}





















ShootingBlocks::~ShootingBlocks(){
	delete [] block;
}




/*
int Mine::run(bool on, Map& map, Door* door, int number) {
	if (on == false && exist == false) return -1;
	if (on == true && exist == false) {
		VectorConverter vec(getPosition());
		if (map.getType(vec.asNumber()) == Square::Wall) return -1;
		exist = true;
	}
	if (clock.getElapsedTime().asSeconds() < 0.03 || exist == false) return -1;
	clock.restart();
	VectorConverter vec(getPosition());
	for (int i = 0; i < number; i++) {
		if ((door + i)->isOpen()) continue;
		if ((door + i)->getPosition() == VectorConverter::convert(vec.asXY().x, vec.asXY().y).asVector2f()) {
			reset();
			return -1;
		}
	}
	if (moveNr == 8) {
		switch (direction) {
		case Up:
			if (map.getType(vec.asNumber() - 18) == Square::Wall) {
				reset();
				return -1;
			}
			for (int i = 0; i < number; i++) {
				if ((door + i)->isOpen()) continue;
				if ((door + i)->getPosition() == VectorConverter::convert(vec.asXY().x, vec.asXY().y - 1).asVector2f()) {
					reset();
					return -1;
				}
			}
			break;
		case Down:
			if (map.getType(vec.asNumber() + 18) == Square::Wall) {
				reset();
				return -1;
			}
			for (int i = 0; i < number; i++) {
				if ((door + i)->isOpen()) continue;
				if ((door + i)->getPosition() == VectorConverter::convert(vec.asXY().x, vec.asXY().y + 1).asVector2f()) {
					reset();
					return -1;
				}
			}
			break;
		case Left:
			if (map.getType(vec.asNumber() - 1) == Square::Wall) {
				reset();
				return -1;
			}
			for (int i = 0; i < number; i++) {
				if ((door + i)->isOpen()) continue;
				if ((door + i)->getPosition() == VectorConverter::convert(vec.asXY().x - 1, vec.asXY().y).asVector2f()) {
					reset();
					return -1;
				}
			}
			break;
		case Right:
			if (map.getType(vec.asNumber() + 1) == Square::Wall) {
				reset();
				return -1;
			}
			for (int i = 0; i < number; i++) {
				if ((door + i)->isOpen()) continue;
				if ((door + i)->getPosition() == VectorConverter::convert(vec.asXY().x + 1, vec.asXY().y).asVector2f()) {
					reset();
					return -1;
				}
			}
			break;
		}
	}
	switch (direction) {
	case Direction::Up:
		move(Vector2f{ 0, -8 });
		break;
	case Direction::Down:
		move(Vector2f{ 0, 8 });
		break;
	case Direction::Left:
		move(Vector2f{ -8, 0 });
		break;
	case Direction::Right:
		move(Vector2f{ 8, 0 });
		break;
	}
	moveNr++;
	if (moveNr == 10) moveNr = 0;
	return moveNr;
}
*/