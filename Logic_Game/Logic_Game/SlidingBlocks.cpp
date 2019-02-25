#include "SlidingBlocks.hpp"

SlidingBlocks::SlidingBlocks(int number, string textureFile){
	SlidingBlock::setBlockTexture(textureFile);
	this->number = number;
	block = new SlidingBlock[number];
}

void SlidingBlocks::setBlockPosition(int number, Vector2f position) {
	(block + number)->setPosition(position);
}

void SlidingBlocks::setBlockSize(int number, Vector2f size) {
	(block + number)->setSize(size);
}

void SlidingBlocks::destroy(int number) {
	(block + number)->destroy();
}

bool SlidingBlocks::getExist(int number) {
	return (block + number)->getExist();
}

bool SlidingBlocks::push(int number, SlidingBlock::Direction direction, Map& map, Mirror* mirror, int number2, Door* door, int number3, 
	ShootingBlock* blockS, int number4, LaserMachine* machine, int number5) {

	if (!(block + number)->getExist() || (block + number)->getMoveNumber() != 10) return false;
	if (direction == SlidingBlock::Direction::None) return false;

	VectorConverter vec((block + number)->getPosition());
	switch (direction) {
	case SlidingBlock::Up:
		vec = vec.convert(vec.asXY().x, vec.asXY().y - 1);
		break;
	case SlidingBlock::Down:
		vec = vec.convert(vec.asXY().x, vec.asXY().y + 1);
		break;
	case SlidingBlock::Left:
		vec = vec.convert(vec.asXY().x - 1, vec.asXY().y);
		break;
	case SlidingBlock::Right:
		vec = vec.convert(vec.asXY().x + 1, vec.asXY().y);
		break;
	}
	
	if (map.getType(vec.asNumber()) == Square::Type::Wall) return false;

	for (int i = 0; i < this->number; i++) {
		if (i == number) continue;
		if ((block + i)->getExist() && (block + i)->getPosition() == vec.asVector2f()) return false;
	}

	for (int i = 0; i < number2; i++) {
		if ((mirror + i)->getExist() && (mirror + i)->getPosition() == vec.asVector2f()) return false;
	}

	for (int i = 0; i < number3; i++) {
		if (!(door + i)->isOpen() && (door + i)->getPosition() == vec.asVector2f()) return false;
	}

	for (int i = 0; i < number4; i++) {
		if ((blockS + i)->getPosition() == vec.asVector2f()) return false;
	}

	for (int i = 0; i < number5; i++) {
		if ((machine + i)->getPosition() == vec.asVector2f()) return false;
	}

	(block + number)->push(direction);
	return true;
}

SlidingBlock* SlidingBlocks::getBlock() {
	return block;
}

int SlidingBlocks::getNumber() {
	return number;
}

void SlidingBlocks::run() {
	for (int i = 0; i < number; i++) {
		(block + i)->run();
	}
}

void SlidingBlocks::draw(RenderWindow& window) {
	for (int i = 0; i < number; i++) {
		(block + i)->draw(window);
	}
}

void SlidingBlocks::reset(int number) {
	(block + number)->reset();
}

void SlidingBlocks::reset() {
	for (int i = 0; i < number; i++) {
		(block + i)->reset();
	}
}

SlidingBlocks::~SlidingBlocks(){
	delete [] block;
}