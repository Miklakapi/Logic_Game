#include "LaserMachines.hpp"

LaserMachines::LaserMachines(int number, string textureFile, string textureFile2){
	LaserMachine::setMachineTexture(textureFile);
	SimpleLaser::setLaserTexture(textureFile2);
	machine = new LaserMachine[number];
	this->number = number;
}

void LaserMachines::setPosition(int number, Vector2f position) {
	(machine + number)->setMachinePosition(position);
}

void LaserMachines::setSize(int number, Vector2f size) {
	(machine + number)->setMachineSize(size);
}

Laser* LaserMachines::getLaser(int number) {
	return 	(machine + number)->getLaser();
}

int LaserMachines::getLaserNr(int number) {
	return (machine + number)->getLaserNr();
}

void LaserMachines::setType(int number, LaserMachine::Type type, Map& map, 
	ShootingBlock* blocks, int number2) {

	VectorConverter vec((machine + number)->getPosition());
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
		for (int i = 0; i < this->number; i++) {
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
		vec2 = { vec2.asXY().x,vec2.asXY().y + 1};
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
		for (int i = 0; i < this->number; i++) {
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
		for (int i = 0; i < this->number; i++) {
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
		for (int i = 0; i < this->number; i++) {
			if (VectorConverter::convert((machine + i)->getPosition()).asNumber() == vec2.asNumber()) {
				wall = true;
				break;
			}
		}
		if (wall) break;
		right++;
	} while (!wall);

	(machine + number)->setType(type);
	
	Laser* laser = (machine + number)->getLaser();

	if (type < 4) {
		switch (type) {
		case 0:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Up, up);
			break;
		case 1:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Right, right);
			break;
		case 2:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Down, down);
			break;
		case 3:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Left, left);
			break;
		}
	}
	else if (type < 10 && type >3) {
		switch (type) {
		case 4:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Up, up);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Right, right);
			break;
		case 5:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Right, right);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Down, down);
			break;
		case 6:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Down, down);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Left, left);
			break;
		case 7:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Left, left);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Up, up);
			break;
		case 8:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Up, up);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Down, down);
			break;
		case 9:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Left, left);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Right, right);
			break;
		}
	}
	else if (type < 14 && type > 9) {
		switch (type) {
		case 10:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Left, left);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Up, up);
			(laser + 2)->setPosition(vec.asVector2f(), Laser::Right, right);
			break;
		case 11:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Up, up);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Right, right);
			(laser + 2)->setPosition(vec.asVector2f(), Laser::Down, down);
			break;
		case 12:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Right, right);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Down, down);
			(laser + 2)->setPosition(vec.asVector2f(), Laser::Left, left);
			break;
		case 13:
			(laser + 0)->setPosition(vec.asVector2f(), Laser::Down, down);
			(laser + 1)->setPosition(vec.asVector2f(), Laser::Left, left);
			(laser + 2)->setPosition(vec.asVector2f(), Laser::Up, up);
			break;
		}
	}
	else if (type == 14) {
		(laser + 0)->setPosition(vec.asVector2f(), Laser::Down, down);
		(laser + 1)->setPosition(vec.asVector2f(), Laser::Left, left);
		(laser + 2)->setPosition(vec.asVector2f(), Laser::Up, up);
		(laser + 3)->setPosition(vec.asVector2f(), Laser::Right, right);
	}
}

LaserMachine::Type LaserMachines::getType(int number) {
	return (machine + number)->getType();
}

void LaserMachines::setOn(int number, bool on) {
	(machine + number)->setOn(on);
}

bool LaserMachines::isOn(int number) {
	return (machine + number)->isOn();
}

LaserMachine* LaserMachines::getMachine() {
	return machine;
}

int LaserMachines::getNumber() {
	return number;
}

void LaserMachines::draw(RenderWindow& window) {
	for (int i = 0; i < number; i++) {
		(machine + i)->draw(window);
	}
}

void LaserMachines::run(SlidingBlock* block, int number, Mirror* mirror, int number2, Door* door, int number3) {

	//Machine
	for (int i = 0; i < this->number; i++) {
		if (!(machine + i)->isOn()) continue;

		Laser* laser = (machine + i)->getLaser();
		LaserMachine::Type type = (machine + i)->getType();

		int nr = 0;

		if (type < 4) nr = 1;
		else if (type < 10 && type > 3) nr = 2;
		else if (type < 14 && type > 9) nr = 3;
		else if (type == 14) nr = 4;

		//Laser
		for (int j = 0; j < nr; j++) {

			(laser + j)->setOn(true);
			SimpleLaser* simLaser = (laser + j)->getSimpleLaser();
			bool wall(false);

			//Simple Laser
			for (int k = 0; k < (laser + j)->getLaserNr(); k++) {
				
				if (wall) {
					(simLaser + k)->setExist(false);
					continue;
				}

				Vector2f vec = (simLaser + k)->getPosition();
				SimpleLaser::Direction direction = (simLaser + k)->getDirection();
				if (direction == SimpleLaser::Direction::Horizontal) {
					vec = Vector2f{ vec.x,vec.y + 35 };
				}
				else {
					vec = Vector2f{ vec.x + 35,vec.y };
				}

				for (int l = 0; l < number; l++) {
					if (!(block + l)->getExist()) continue;
					Vector2f vec2 = (block + l)->getPosition();
					if (direction == SimpleLaser::Direction::Horizontal) {
						if (vec.x + 80 > vec2.x && vec.x < vec2.x + 80 &&
							vec.y + 10 > vec2.y && vec.y < vec2.y + 80) {
							wall = true;
							(simLaser + k)->setExist(false);
							break;;
						}
					}
					else {
						if (vec.x + 10 > vec2.x && vec.x < vec2.x + 80 &&
							vec.y + 80 > vec2.y && vec.y < vec2.y + 80) {
							wall = true;
							(simLaser + k)->setExist(false);
							break;
						}
					}
				}
				if (wall) continue;

				for (int l = 0; l < number2; l++) {
					if (!(mirror + l)->getExist()) continue;
					Vector2f vec2 = (mirror + l)->getPosition();
					if (direction == SimpleLaser::Direction::Horizontal) {
						if (vec.x + 80 > vec2.x && vec.x < vec2.x + 80 &&
							vec.y + 10 > vec2.y && vec.y < vec2.y + 80) {
							wall = true;
							(simLaser + k)->setExist(false);
							break;;
						}
					}
					else {
						if (vec.x + 10 > vec2.x && vec.x < vec2.x + 80 &&
							vec.y + 80 > vec2.y && vec.y < vec2.y + 80) {
							wall = true;
							(simLaser + k)->setExist(false);
							break;
						}
					}
				}
				if (wall) continue;

				for (int l = 0; l < number3; l++) {
					if ((door + l)->isOpen()) continue;
					Vector2f vec2 = (door + l)->getPosition();
					if (direction == SimpleLaser::Direction::Horizontal) {
						if (vec.x + 80 > vec2.x && vec.x < vec2.x + 80 &&
							vec.y + 10 > vec2.y && vec.y < vec2.y + 80) {
							wall = true;
							(simLaser + k)->setExist(false);
							break;;
						}
					}
					else {
						if (vec.x + 10 > vec2.x && vec.x < vec2.x + 80 &&
							vec.y + 80 > vec2.y && vec.y < vec2.y + 80) {
							wall = true;
							(simLaser + k)->setExist(false);
							break;
						}
					}
				}
			}
		}
	}
}

void LaserMachines::reset(int number) {
	(machine + number)->reset();
}

void LaserMachines::reset() {
	for (int i = 0; i < number; i++) {
		(machine + i)->reset();
	}
}

LaserMachines::~LaserMachines(){
	delete [] machine;
}