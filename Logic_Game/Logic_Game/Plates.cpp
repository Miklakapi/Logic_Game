#include "Plates.hpp"

Plates::Plates(int number, string textureFile){
	Plate::setPlateTexture(textureFile);
	this->number = number;
	plate = new Plate[number];
}

void Plates::setPlatePosition(int number, Vector2f position) {
	(plate + number)->setPlatePosition(position);
}

void Plates::setPlateSize(int number, Vector2f size) {
	(plate + number)->setPlateSize(size);
}

bool Plates::isPressed(int number) {
	return (plate + number)->isPressed();
}

void Plates::setPressure(int number, bool pressed) {
	(plate + number)->setPressure(pressed);
}

void Plates::draw(RenderWindow& window) {
	for (int i = 0; i < number; i++) {
		(plate + i)->draw(window);
	}
}

void Plates::run(Player& player, SlidingBlock* block, int number, Mirror* mirror, int number2) {
	for (int i = 0; i < number; i++) {
		(plate + i)->setPressure(false);
		if (player.getLive() && 
			player.getPosition().x < (plate + i)->getPosition().x + 80 && player.getPosition().x + 80 > (plate + i)->getPosition().x &&
			player.getPosition().y < (plate + i)->getPosition().y + 80 && player.getPosition().y + 80 > (plate + i)->getPosition().y) {
			(plate + i)->setPressure(true);
			continue;
		}
		int a = 0;
		for (int j = 0; j < number; j++) {
			if (!(block + j)->getExist()) continue;
			if ((block + j)->getPosition().x < (plate + i)->getPosition().x + 80 && (block + j)->getPosition().x + 80 > (plate + i)->getPosition().x &&
				(block + j)->getPosition().y < (plate + i)->getPosition().y + 80 && (block + j)->getPosition().y + 80 > (plate + i)->getPosition().y) {
				(plate + i)->setPressure(true);
				a++;
				break;
			}
		}
		if (a == 1) continue;
		for (int j = 0; j < number2; j++) {
			if (!(mirror + j)->getExist()) continue;
			if ((mirror + j)->getPosition().x < (plate + i)->getPosition().x + 80 && (mirror + j)->getPosition().x + 80 > (plate + i)->getPosition().x &&
				(mirror + j)->getPosition().y < (plate + i)->getPosition().y + 80 && (mirror + j)->getPosition().y + 80 > (plate + i)->getPosition().y) {
				(plate + i)->setPressure(true);
				break;
			}
		}
	}
}

void Plates::reset(int number) {
	(plate + number)->reset();
}

void Plates::reset() {
	for (int i = 0; i < number; i++) {
		(plate + i)->reset();
	}
}

Plates::~Plates(){
	delete [] plate;
}