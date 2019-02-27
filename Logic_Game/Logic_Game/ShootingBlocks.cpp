#include "ShootingBlocks.hpp"

ShootingBlocks::ShootingBlocks(int number, string textureFile){
	ShootingBlock::setBlockTexture(textureFile);
	this->number = number;
	block = new ShootingBlock[number];
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