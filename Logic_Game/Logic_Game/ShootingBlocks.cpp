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

void ShootingBlocks::setDelay(int number, float delay) {
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

void ShootingBlocks::run(Map& map, Door* door, int number, SlidingBlock* block, int number2, Mirror* mirror, int number3, LaserMachine* machine, int number4, LaserReceiver* receiver, int number5) {
	for (int i = 0; i < this->number; i++) {
		(this->block + i)->run();

		ShootingBlock::Type type = (this->block + i)->getType();
		Mine* mine = (this->block + i)->getMine();

		for (int j = 0; j < (this->block + i)->getMinerNr(); j++) {
			if (!(mine + j)->getExist()) continue;

			VectorConverter vec((mine + j)->getPosition());

			if ((mine + j)->getMoveNr() == 9) {
				if ((mine + j)->getDirection() == Mine::Up || (mine + j)->getDirection() == Mine::Left) {
					if (map.getType(vec.asNumber()) == Square::Wall) {
						(mine + j)->setExist(false);
					}
				}
				else if ((mine + j)->getDirection() == Mine::Direction::Right) {
					VectorConverter vec2(vec.asXY().x + 1, vec.asXY().y);
					if (map.getType(vec2.asNumber()) == Square::Wall) {
						(mine + j)->setExist(false);
					}
				}
				else {
					VectorConverter vec2(vec.asXY().x, vec.asXY().y + 1);
					if (map.getType(vec2.asNumber()) == Square::Wall) {
						(mine + j)->setExist(false);
					}
				}

				for (int k = 0; k < number4; k++) {
					if (vec.asVector2f().x + 12 > (machine + k)->getPosition().x &&
						vec.asVector2f().x < (machine + k)->getPosition().x + 80 &&
						vec.asVector2f().y + 12 >(machine + k)->getPosition().y &&
						vec.asVector2f().y < (machine + k)->getPosition().y + 80) {
						(mine + j)->setExist(false);
					}
				}

				for (int k = 0; k < number5; k++) {
					if (vec.asVector2f().x + 12 > (receiver + k)->getPosition().x &&
						vec.asVector2f().x < (receiver + k)->getPosition().x + 80 &&
						vec.asVector2f().y + 12 >(receiver + k)->getPosition().y &&
						vec.asVector2f().y < (receiver + k)->getPosition().y + 80) {
						(mine + j)->setExist(false);
					}
				}

				for (int k = 0; k < number; k++) {
					if (vec.asVector2f().x + 12 > (this->block + k)->getPosition().x &&
						vec.asVector2f().x < (this->block + k)->getPosition().x + 80 &&
						vec.asVector2f().y + 12 >(this->block + k)->getPosition().y &&
						vec.asVector2f().y < (this->block + k)->getPosition().y + 80) {
						(mine + j)->setExist(false);
					}
				}
			}

			for (int k = 0; k < number; k++) {
				if ((door + k)->isOpen()) continue;
				if (vec.asVector2f().x + 12 > (door + k)->getPosition().x &&
					vec.asVector2f().x < (door + k)->getPosition().x + 80 &&
					vec.asVector2f().y + 12 >(door + k)->getPosition().y &&
					vec.asVector2f().y < (door + k)->getPosition().y + 80) {
					(mine + j)->setExist(false);
				}
			}

			for (int k = 0; k < number2; k++) {
				if (!(block + k)->getExist()) continue;
				if (vec.asVector2f().x + 12 > (block + k)->getPosition().x &&
					vec.asVector2f().x < (block + k)->getPosition().x + 80 &&
					vec.asVector2f().y + 12 >(block + k)->getPosition().y &&
					vec.asVector2f().y < (block + k)->getPosition().y + 80) {
					(mine + j)->setExist(false);
				}
			}

			for (int k = 0; k < number3; k++) {
				if (!(mirror + k)->getExist()) continue;
				if (vec.asVector2f().x + 12 > (mirror + k)->getPosition().x &&
					vec.asVector2f().x < (mirror + k)->getPosition().x + 80 &&
					vec.asVector2f().y + 12 >(mirror + k)->getPosition().y &&
					vec.asVector2f().y < (mirror + k)->getPosition().y + 80) {
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