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

			/////////////////////////////

		}

		switch ((receiver + i)->getType()) {
		case LaserReceiver::A1:


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