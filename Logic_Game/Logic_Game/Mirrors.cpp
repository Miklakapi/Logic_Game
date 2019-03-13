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
	
	Laser* laser = (mirror + number)->getLaser();
	
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
		(laser + 0)->setPosition(vec.asVector2f(), Laser::Up, up);
		(laser + 1)->setPosition(vec.asVector2f(), Laser::Right, right);
		(laser + 2)->setPosition(vec.asVector2f(), Laser::Down, down);
		(laser + 3)->setPosition(vec.asVector2f(), Laser::Left, left);	
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
		
		if ((mirror + i)->isOnNewPosition()) {
			setType(i, (mirror + i)->getType(), map, blockS, number3, machine, number4);
			(mirror + i)->setOnNewPosition(false);
		}
		
		(mirror + i)->setOn(false);

		bool wallUp(false);
		bool wallDown(false);
		bool wallLeft(false);
		bool wallRight(false);

		bool boolUp(false);
		bool boolDown(false);
		bool boolLeft(false);
		bool boolRight(false);
		
		Vector2f position = (mirror + i)->getPosition();
		VectorConverter position2 = VectorConverter{ position };

		Vector2f vecUp = VectorConverter::convert(position2.asXY().x, position2.asXY().y - 1).asVector2f();
		Vector2f vecDown = VectorConverter::convert(position2.asXY().x, position2.asXY().y + 1).asVector2f();
		Vector2f vecLeft = VectorConverter::convert(position2.asXY().x - 1, position2.asXY().y).asVector2f();
		Vector2f vecRight = VectorConverter::convert(position2.asXY().x + 1, position2.asXY().y).asVector2f();
		
		if (map.getType(VectorConverter::convert(vecUp).asNumber()) == Square::Type::Wall) wallUp = true;
		if (map.getType(VectorConverter::convert(vecDown).asNumber()) == Square::Type::Wall) wallDown = true;
		if (map.getType(VectorConverter::convert(vecLeft).asNumber()) == Square::Type::Wall) wallLeft = true;
		if (map.getType(VectorConverter::convert(vecRight).asNumber()) == Square::Type::Wall) wallRight = true;
		
		for (int j = 0; j < number4; j++) {
			
			if (!(machine + j)->isOn()) continue;
			
			if (vecUp == (machine + j)->getPosition()) boolUp = true;
			else if (vecDown == (machine + j)->getPosition()) boolDown = true;
			else if (vecLeft == (machine + j)->getPosition()) boolLeft = true;
			else if (vecRight == (machine + j)->getPosition()) boolRight = true;

			Laser* laser = (machine + j)->getLaser();

			for (int k = 0; k < (machine + j)->getLaserNr(); k++) {

				SimpleLaser* simLaser = (laser + k)->getSimpleLaser();

				for (int l = 0; l < (laser + k)->getLaserNr(); l++) {
					
					if (!(simLaser + l)->getExist()) continue;
				
					if (!boolUp && !wallUp) {
						if ((simLaser + l)->getPosition() == vecUp &&
							(simLaser + l)->getDirection() == SimpleLaser::Vertical) {
							boolUp = true;
						}
					}
					if (!boolDown && !wallDown) {
						if ((simLaser + l)->getPosition() == vecDown &&
							(simLaser + l)->getDirection() == SimpleLaser::Vertical) {
							boolDown = true;
						}
					}
					if (!boolLeft && !wallLeft) {
						if ((simLaser + l)->getPosition() == vecLeft &&
							(simLaser + l)->getDirection() == SimpleLaser::Horizontal) {
							boolLeft = true;
						}
					}
					if (!boolRight && !wallRight) {
						if ((simLaser + l)->getPosition() == vecRight &&
							(simLaser + l)->getDirection() == SimpleLaser::Horizontal) {
							boolRight = true;
						}
					}
				}
			}
		}

		for (int j = 0; j < this->number; j++) {
			
			if (j == i)continue;
			if (!(mirror + j)->isOn()) continue;

			Mirror::Type type = (mirror + j)->getType();

			if (vecUp == (mirror + j)->getPosition() && 
				(type == 1 || type == 2 || type == 5 || type == 6 || type == 7 || type == 8)) boolUp = true;
			if (vecDown == (mirror + j)->getPosition() &&
				(type == 0 || type == 3 || type == 4 || type == 5 || type == 7 || type == 8)) boolDown = true;
			if (vecLeft == (mirror + j)->getPosition() &&
				(type == 0 || type == 1 || type == 4 || type == 5 || type == 6 || type == 8)) boolLeft = true;
			if (vecRight == (mirror + j)->getPosition() &&
				(type == 2 || type == 3 || type == 4 || type == 6 || type == 7 || type == 8)) boolRight = true;

			Laser* laser = (mirror + j)->getLaser();

			for (int k = 0; k < (mirror + j)->getLaserNr(); k++) {

				SimpleLaser* simLaser = (laser + k)->getSimpleLaser();

				for (int l = 0; l < (laser + k)->getLaserNr(); l++) {

					if (!(simLaser + l)->getExist()) continue;

					if (!boolUp && !wallUp) {
						if ((simLaser + l)->getPosition() == vecUp &&
							(simLaser + l)->getDirection() == SimpleLaser::Vertical) {
							boolUp = true;
						}
					}
					if (!boolDown && !wallDown) {
						if ((simLaser + l)->getPosition() == vecDown &&
							(simLaser + l)->getDirection() == SimpleLaser::Vertical) {
							boolDown = true;
						}
					}
					if (!boolLeft && !wallLeft) {
						if ((simLaser + l)->getPosition() == vecLeft &&
							(simLaser + l)->getDirection() == SimpleLaser::Horizontal) {
							boolLeft = true;
						}
					}
					if (!boolRight && !wallRight) {
						if ((simLaser + l)->getPosition() == vecRight &&
							(simLaser + l)->getDirection() == SimpleLaser::Horizontal) {
							boolRight = true;
						}
					}
				}
			}
		}

		switch ((mirror+i)->getType()){
		case Mirror::A1:
			if (boolUp || boolRight) {
				(mirror + i)->setOn(true);
			}
			break;
		case Mirror::A2:
			if (boolDown || boolRight) {
				(mirror + i)->setOn(true);
			}
			break;
		case Mirror::A3:
			if (boolLeft || boolDown) {
				(mirror + i)->setOn(true);
			}
			break;
		case Mirror::A4:
			if (boolLeft || boolUp) {
				(mirror + i)->setOn(true);
			}
			break;
		case Mirror::B1:
			if (boolLeft || boolUp || boolRight) {
				(mirror + i)->setOn(true);
			}
			break;
		case Mirror::B2:
			if (boolUp || boolRight || boolDown) {
				(mirror + i)->setOn(true);
			}
			break;
		case Mirror::B3:
			if (boolRight || boolDown || boolLeft) {
				(mirror + i)->setOn(true);
			}
			break;
		case Mirror::B4:
			if (boolDown || boolLeft || boolUp) {
				(mirror + i)->setOn(true);
			}
			break;
		case Mirror::C1:
			if (boolUp || boolRight || boolLeft || boolDown) {
				(mirror + i)->setOn(true);
			}
			break;
		}
		
		boolDown = !boolDown;
		boolUp = !boolUp;
		boolRight = !boolRight;
		boolLeft = !boolLeft;

		//

		if (!(mirror + i)->isOn()) continue;

		Laser* laser = (mirror + i)->getLaser();

		for (int j = 0; j < (mirror + i)->getLaserNr(); j++) {
			(laser + j)->setOn(false);
		}

		Mirror::Type type = (mirror + i)->getType();

		switch (type) {
		case Mirror::A1:
			if (boolUp) (laser + 0)->setOn(true);
			else (laser + 0)->setOn(false);
			if (boolRight) (laser + 1)->setOn(true);
			else (laser + 1)->setOn(false);
			break;
		case Mirror::A2:
			if (boolRight) (laser + 0)->setOn(true);
			else (laser + 0)->setOn(false);
			if (boolDown) (laser + 1)->setOn(true);
			else (laser + 1)->setOn(false);
			break;
		case Mirror::A3:
			if (boolDown) (laser + 0)->setOn(true);
			else (laser + 0)->setOn(false);
			if (boolLeft) (laser + 1)->setOn(true);
			else (laser + 1)->setOn(false);
			break;
		case Mirror::A4:
			if (boolLeft) (laser + 0)->setOn(true);
			else (laser + 0)->setOn(false);
			if (boolUp) (laser + 1)->setOn(true);
			else (laser + 1)->setOn(false);
			break;
		case Mirror::B1:
			if (boolLeft) (laser + 0)->setOn(true);
			else (laser + 0)->setOn(false);
			if (boolUp) (laser + 1)->setOn(true);
			else (laser + 1)->setOn(false);
			if (boolRight) (laser + 2)->setOn(true);
			else (laser + 2)->setOn(false);
			break;
		case Mirror::B2:
			if (boolUp) (laser + 0)->setOn(true);
			else (laser + 0)->setOn(false);
			if (boolRight) (laser + 1)->setOn(true);
			else (laser + 1)->setOn(false);
			if (boolDown) (laser + 2)->setOn(true);
			else (laser + 2)->setOn(false);
			break;
		case Mirror::B3:
			if (boolRight) (laser + 0)->setOn(true);
			else (laser + 0)->setOn(false);
			if (boolDown) (laser + 1)->setOn(true);
			else (laser + 1)->setOn(false);
			if (boolLeft) (laser + 2)->setOn(true);
			else (laser + 2)->setOn(false);
			break;
		case Mirror::B4:
			if (boolDown) (laser + 0)->setOn(true);
			else (laser + 0)->setOn(false);
			if (boolLeft) (laser + 1)->setOn(true);
			else (laser + 1)->setOn(false);
			if (boolUp) (laser + 2)->setOn(true);
			else (laser + 2)->setOn(false);
			break;
		case Mirror::C1:
			if (boolUp) (laser + 0)->setOn(true);
			else (laser + 0)->setOn(false);
			if (boolRight) (laser + 1)->setOn(true);
			else (laser + 1)->setOn(false);
			if (boolDown) (laser + 2)->setOn(true);
			else (laser + 2)->setOn(false);
			if (boolLeft) (laser + 3)->setOn(true);
			else (laser + 3)->setOn(false);
			break;
		}

		//Laser
		for (int j = 0; j < (mirror + i)->getLaserNr(); j++) {
	
			if (!(laser + j)->isOn()) continue;

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

				for (int l = 0; l < this->number; l++) {
					if (!(mirror + l)->getExist() || l == i) continue;
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

				for (int l = 0; l < number2; l++) {
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