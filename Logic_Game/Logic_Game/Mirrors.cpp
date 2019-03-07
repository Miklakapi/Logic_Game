#include "Mirrors.hpp"

Mirrors::Mirrors(int number, string textureFile){
	Mirror::setBlockTexture(textureFile);
	mirror = new Mirror[number];
	this->number = number;
}

void Mirrors::setPosition(int number, Vector2f position) {
	(mirror + number)->setPosition(position);
}

void Mirrors::setSize(int number, Vector2f size) {
	(mirror + number)->setSize(size);
}

Laser* Mirrors::getLaser(int number) {
	return (mirror + number)->getLaser();
}

int Mirrors::getLaserNr(int number) {
	return (mirror + number)->getLaserNr();
}

void Mirrors::setType(int number, Mirror::Type type, Map& map, ShootingBlock* blocks, int number2, LaserMachine* machine, int number3) {
	
	VectorConverter vec((mirror + number)->getPosition());
	VectorConverter vec2(vec);

	int up(0);
	int down(0);
	int left(0);
	int right(0);

	//UP
	bool wall(false);
	do {
		vec2 = { vec2.asXY().x,vec2.asXY().y - 1 };
		if (map.getType(vec2.asNumber()) == Square::Wall) {
			wall = true;
			break;
		}
		for (int i = 0; i < number2; i++) {
			if (VectorConverter::convert((blocks + i)->getPosition()).asNumber() == vec2.asNumber()) {
				wall = true;
				break;
			}
		}
		if (wall) break;
		for (int i = 0; i < number3; i++) {
			if (VectorConverter::convert((machine + i)->getPosition()).asNumber() == vec2.asNumber()) {
				wall = true;
				break;
			}
		}
		if (wall) break;
		up++;
	} while (!wall);

	wall = false;
	vec2 = { vec };
	//Down
	do {
		vec2 = { vec2.asXY().x,vec2.asXY().y + 1 };
		if (map.getType(vec2.asNumber()) == Square::Wall) {
			wall = true;
			break;
		}
		for (int i = 0; i < number2; i++) {
			if (VectorConverter::convert((blocks + i)->getPosition()).asNumber() == vec2.asNumber()) {
				wall = true;
				break;
			}
		}
		if (wall) break;
		for (int i = 0; i < number3; i++) {
			if (VectorConverter::convert((machine + i)->getPosition()).asNumber() == vec2.asNumber()) {
				wall = true;
				break;
			}
		}
		if (wall) break;
		down++;
	} while (!wall);

	wall = false;
	vec2 = { vec };
	//Left
	do {
		vec2 = { vec2.asXY().x - 1,vec2.asXY().y };
		if (map.getType(vec2.asNumber()) == Square::Wall) {
			wall = true;
			break;
		}
		for (int i = 0; i < number2; i++) {
			if (VectorConverter::convert((blocks + i)->getPosition()).asNumber() == vec2.asNumber()) {
				wall = true;
				break;
			}
		}
		if (wall) break;
		for (int i = 0; i < number3; i++) {
			if (VectorConverter::convert((machine + i)->getPosition()).asNumber() == vec2.asNumber()) {
				wall = true;
				break;
			}
		}
		if (wall) break;
		left++;
	} while (!wall);

	wall = false;
	vec2 = { vec };
	//Right
	do {
		vec2 = { vec2.asXY().x + 1,vec2.asXY().y };
		if (map.getType(vec2.asNumber()) == Square::Wall) {
			wall = true;
			break;
		}
		for (int i = 0; i < number2; i++) {
			if (VectorConverter::convert((blocks + i)->getPosition()).asNumber() == vec2.asNumber()) {
				wall = true;
				break;
			}
		}
		if (wall) break;
		for (int i = 0; i < number3; i++) {
			if (VectorConverter::convert((machine + i)->getPosition()).asNumber() == vec2.asNumber()) {
				wall = true;
				break;
			}
		}
		if (wall) break;
		right++;
	} while (!wall);

	(mirror + number)->setType(type);

	Laser* laser = (machine + number)->getLaser();

	if (type < 4) {
		switch (type) {
		case 0:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Up, up);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Right, right);
			break;
		case 1:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Right, right);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Down, down);
			break;
		case 2:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Down, down);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Left, left);
			break;
		case 3:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Left, left);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Up, up);
			break;
		}
	}
	else if (type < 8 && type > 3) {
		switch (type) {
		case 4:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Left, left);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Up, up);
			(laser + 2)->setPosition(vec.asVector2f(), Laser::Right, right);
			break;
		case 5:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Up, up);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Right, right);
			(laser + 2)->setPosition(vec.asVector2f(), Laser::Down, down);
			break;
		case 6:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Right, right);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Down, down);
			(laser + 2)->setPosition(vec.asVector2f(), Laser::Left, left);
			break;
		case 7:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Down, down);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Left, left);
			(laser + 2)->setPosition(vec.asVector2f(), Laser::Up, up);
			break;
		}
	}
	else if (type == 8) {
		(laser + 0)->setPosition(vec.asVector2f(), Laser::Down, down);
		(laser + 1)->setPosition(vec.asVector2f(), Laser::Left, left);
		(laser + 2)->setPosition(vec.asVector2f(), Laser::Up, up);
		(laser + 3)->setPosition(vec.asVector2f(), Laser::Right, right);
	}
}

Mirror::Type Mirrors::getType(int number) {
	return (mirror + number)->getType();
}

bool Mirrors::isOn(int number) {
	return (mirror + number)->isOn();
}

int Mirrors::getMoveNumber(int number) {
	return (mirror + number)->getMoveNumber();
}

void Mirrors::destroy(int number) {
	(mirror + number)->destroy();
}

bool Mirrors::getExist(int number) {
	return (mirror + number)->getExist();
}

bool Mirrors::push(int number, Mirror::Direction direction, Map& map, SlidingBlock* block, int number2, Door* door, int number3,
	ShootingBlock* blockS, int number4, LaserMachine* machine, int number5) {

	if (!(mirror + number)->getExist() || (mirror + number)->getMoveNumber() != 10) return false;
	if (direction == Mirror::Direction::None) return false;

	VectorConverter vec((mirror + number)->getPosition());
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
		if ((mirror + i)->getExist() && (mirror + i)->getPosition() == vec.asVector2f()) return false;
	}

	for (int i = 0; i < number2; i++) {
		if ((block + i)->getExist() && (block + i)->getPosition() == vec.asVector2f()) return false;
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

	(mirror + number)->push(direction);
	return true;
}

Mirror* Mirrors::getMirror() {
	return mirror;
}

int Mirrors::getNumber() {
	return number;
}

void Mirrors::draw(RenderWindow& window) {
	for (int i = 0; i < number; i++) {
		(mirror + i)->draw(window);
	}
}

void Mirrors::run(Map& map, SlidingBlock* block, int number, Door* door, int number2, ShootingBlock* blockS, int number3,
	LaserMachine* machine, int number4) {

	//Mirror
	for (int i = 0; i < this->number; i++) {

		(mirror + i)->run();

		if ((mirror + i)->getMoveNumber() != 10 || !(mirror + i)->getExist()) continue;
				
		for (int j = 0; j < number4; j++) {


		}

		if (!(mirror + i)->isOn()) continue;

		if ((mirror + i)->isOnNewPosition()) {
			setType(i, (mirror + i)->getType(), map, blockS, number3, machine, number4);
		}

		Laser* laser = (mirror + i)->getLaser();
		Mirror::Type type = (mirror + i)->getType();

		int nr = (mirror+i)->getLaserNr();

		//Laser
		for (int j = 0; j < nr; j++) {

			(laser + j)->on();
			SimpleLaser* simLaser = (laser + j)->getSimpleLaser();
			bool wall(false);

			//Simple Laser
			for (int k = 0; k < (laser + j)->getLaserNr(); k++) {
				











			}
		}
	}
}

void Mirrors::reset(int number) {
	(mirror + number)->reset();
}

void Mirrors::reset() {
	for (int i = 0; i < number; i++) {
		(mirror + i)->reset();
	}
}

Mirrors::~Mirrors(){
	delete [] mirror;
}