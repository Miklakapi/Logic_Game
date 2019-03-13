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

void LaserReceivers::draw(RenderWindow& window) {
	for (int i = 0; i < number; i++) {
		window.draw(*(receiver + i));
	}
}

void LaserReceivers::run(Mirror* mirror, int number, LaserMachine* machine, int number2) {
	for (int i = 0; i < this->number; i++) {

		Vector2f vUp = VectorConverter::convert((receiver + i)->getPosition().x, (receiver + i)->getPosition().y - 1).asVector2f();
		Vector2f vDown = VectorConverter::convert((receiver + i)->getPosition().x, (receiver + i)->getPosition().y + 1).asVector2f();
		Vector2f vLeft = VectorConverter::convert((receiver + i)->getPosition().x - 1, (receiver + i)->getPosition().y).asVector2f();
		Vector2f vRight = VectorConverter::convert((receiver + i)->getPosition().x + 1, (receiver + i)->getPosition().y).asVector2f();

		bool up(false);
		bool down(false);
		bool left(false);
		bool right(false);

		//Mirror
		for (int j = 0; j < number; j++) {
			
			Laser* laser = (mirror + j)->getLaser();

			//Laser
			for (int k = 0; k < (mirror + j)->getLaserNr(); k++) {

				SimpleLaser* sLaser = (laser + k)->getSimpleLaser();
				
				//for(int l=0;l<(sLaser +)) /*           ??????Szukac w Mirror??????                     */
				if (sLaser->getPosition() == vUp && !up) {
					up = true;
					break;
				}
				if (sLaser->getPosition() == vDown && !down) {
					down = true;
					break;
				}
				if (sLaser->getPosition() == vLeft && sLaser->getDirection() == SimpleLaser::Horizontal && !left) {
					left = true;
					break;
				}
				if (sLaser->getPosition() == vRight && !right) {
					right = true;
					break;
				}

			}

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