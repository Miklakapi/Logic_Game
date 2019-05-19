#include "LaserReceivers.hpp"

LaserReceivers::LaserReceivers(int number, string textureFile){
	LaserReceiver::setReceiverTexture(textureFile);
	receiver = new LaserReceiver[number];
	this->number = number;
}

void LaserReceivers::setPosition(int number, Vector2f position) {
	(receiver + number)->setPosition(position);
}

void LaserReceivers::setSize(int number, Vector2f size) {
	(receiver + number)->setSize(size);
}

LaserReceiver::Type LaserReceivers::getType(int number) {
	return (receiver + number)->getType();
}

void LaserReceivers::setType(int number, LaserReceiver::Type type) {
	(receiver + number)->setType(type);
}

bool LaserReceivers::getOn(int number) {
	return (receiver + number)->getOn();
}

void LaserReceivers::setOn(int number, bool on) {
	(receiver + number)->setOn(on);
}

LaserReceiver* LaserReceivers::getReceiver() {
	return receiver;
}

int LaserReceivers::getNumber() {
	return number;
}

void LaserReceivers::draw(RenderWindow& window) {
	for (int i = 0; i < number; i++) {
		window.draw(*(receiver + i));
	}
}

void LaserReceivers::run(Mirror* mirror, int number, LaserMachine* machine, int number2) {

	//LaserReceiver
	for (int i = 0; i < this->number; i++) {

		(receiver + i)->setOn(false);

		bool up(false);
		bool down(false);
		bool left(false);
		bool right(false);

		Vector2f position = (receiver + i)->getPosition();
		VectorConverter position2 = VectorConverter{ position };

		Vector2f vUp = VectorConverter::convert(position2.asXY().x, position2.asXY().y - 1).asVector2f();
		Vector2f vDown = VectorConverter::convert(position2.asXY().x, position2.asXY().y + 1).asVector2f();
		Vector2f vLeft = VectorConverter::convert(position2.asXY().x - 1, position2.asXY().y).asVector2f();
		Vector2f vRight = VectorConverter::convert(position2.asXY().x + 1, position2.asXY().y).asVector2f();

		//Mirror
		for (int j = 0; j < number; j++) {
			
			if (!(mirror + j)->isOn()) continue;

			Mirror::Type type = (mirror + j)->getType();

			if (vUp == (mirror + j)->getPosition() &&
				(type == 1 || type == 2 || type == 5 || type == 6 || type == 7 || type == 8)) up = true;
			if (vDown == (mirror + j)->getPosition() &&
				(type == 0 || type == 3 || type == 4 || type == 5 || type == 7 || type == 8)) down = true;
			if (vLeft == (mirror + j)->getPosition() &&
				(type == 0 || type == 1 || type == 4 || type == 5 || type == 6 || type == 8)) left = true;
			if (vRight == (mirror + j)->getPosition() &&
				(type == 2 || type == 3 || type == 4 || type == 6 || type == 7 || type == 8)) right = true;

			Laser* laser = (mirror + j)->getLaser();

			//Laser
			for (int k = 0; k < (mirror + j)->getLaserNr(); k++) {

				SimpleLaser* sLaser = (laser + k)->getSimpleLaser();

				for (int l = 0; l < (laser + k)->getLaserNr(); l++) {

					if (!(sLaser + l)->getExist()) continue;

					if (!up) {
						if ((sLaser + l)->getPosition() == vUp &&
							(sLaser + l)->getDirection() == SimpleLaser::Vertical) {
							up = true;
						}
					}
					if (!down) {
						if ((sLaser + l)->getPosition() == vDown &&
							(sLaser + l)->getDirection() == SimpleLaser::Vertical) {
							down = true;
						}
					}
					if (!left) {
						if ((sLaser + l)->getPosition() == vLeft &&
							(sLaser + l)->getDirection() == SimpleLaser::Horizontal) {
							left = true;
						}
					}
					if (!right) {
						if ((sLaser + l)->getPosition() == vRight &&
							(sLaser + l)->getDirection() == SimpleLaser::Horizontal) {
							right = true;
						}
					}
				}
			}
		}

		for (int j = 0; j < number2; j++) {

			if (!(machine + j)->isOn()) continue;

			if (vUp == (machine + j)->getPosition()) up = true;
			else if (vDown == (machine + j)->getPosition()) down = true;
			else if (vLeft == (machine + j)->getPosition()) left = true;
			else if (vRight == (machine + j)->getPosition()) right = true;

			Laser* laser = (machine + j)->getLaser();

			for (int k = 0; k < (machine + j)->getLaserNr(); k++) {

				SimpleLaser* simLaser = (laser + k)->getSimpleLaser();

				for (int l = 0; l < (laser + k)->getLaserNr(); l++) {

					if (!(simLaser + l)->getExist()) continue;

					if (!up) {
						if ((simLaser + l)->getPosition() == vUp &&
							(simLaser + l)->getDirection() == SimpleLaser::Vertical) {
							up = true;
						}
					}
					if (!down) {
						if ((simLaser + l)->getPosition() == vDown &&
							(simLaser + l)->getDirection() == SimpleLaser::Vertical) {
							down = true;
						}
					}
					if (!left) {
						if ((simLaser + l)->getPosition() == vLeft &&
							(simLaser + l)->getDirection() == SimpleLaser::Horizontal) {
							left = true;
						}
					}
					if (!right) {
						if ((simLaser + l)->getPosition() == vRight &&
							(simLaser + l)->getDirection() == SimpleLaser::Horizontal) {
							right = true;
						}
					}
				}
			}
		}

		switch ((receiver + i)->getType()) {
		case LaserReceiver::A1:
			if (up) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::A2:
			if (right) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::A3:
			if (down) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::A4:
			if (left) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::B1:
			if (up && right) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::B2:
			if (down && right) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::B3:
			if (down && left) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::B4:
			if (up && left) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::B5:
			if (down && up) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::B6:
			if (right && left) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::C1:
			if (right && left && up) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::C2:
			if (down && right && up) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::C3:
			if (down && left && right) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::C4:
			if (down && left && up) {
				(receiver + i)->setOn(true);
			}
			break;
		case LaserReceiver::D1:
			if (down && left && up && right) {
				(receiver + i)->setOn(true);
			}
			break;
		}

	}
}

void LaserReceivers::reset(int number) {
	(receiver + number)->reset();
}

void LaserReceivers::reset() {
	for (int i = 0; i < number; i++) {
		(receiver + i)->reset();
	}
}

LaserReceivers::~LaserReceivers(){
	delete [] receiver;
}