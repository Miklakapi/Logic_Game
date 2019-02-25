#include "Doors.hpp"

Doors::Doors(int number, string textureFile){
	Door::setDoorTexture(textureFile);
	this->number = number;
	door = new Door[number];
}

void Doors::setDoorPosition(int number, Vector2f position) {
	(door + number)->setDoorPosition(position);
}

void Doors::setDoorSize(int number, Vector2f size) {
	(door + number)->setDoorSize(size);
}

bool Doors::isOpen(int number) {
	return (door + number)->isOpen();
}

void Doors::setOpen(int number, bool open, Player& player, SlidingBlock* block, int number2, Mirror* mirror, int number3) {
	if (!open) {
		if (player.getLive() && player.getPosition().x < (door + number)->getPosition().x + 80 && player.getPosition().x + 80 >(door + number)->getPosition().x &&
			player.getPosition().y < (door + number)->getPosition().y + 80 && player.getPosition().y + 80 >(door + number)->getPosition().y) {
			return;
		}
		for (int i = 0; i < number2; i++) {
			if ((block + i)->getExist() &&
				(block + i)->getPosition().x < (door + number)->getPosition().x + 80 && (block + i)->getPosition().x + 80 >(door + number)->getPosition().x &&
				(block + i)->getPosition().y < (door + number)->getPosition().y + 80 && (block + i)->getPosition().y + 80 >(door + number)->getPosition().y) {
				return;
			}
		}
		for (int i = 0; i < number3; i++) {
			if ((mirror + i)->getExist() &&
				(mirror + i)->getPosition().x < (door + number)->getPosition().x + 80 && (mirror + i)->getPosition().x + 80 >(door + number)->getPosition().x &&
				(mirror + i)->getPosition().y < (door + number)->getPosition().y + 80 && (mirror + i)->getPosition().y + 80 >(door + number)->getPosition().y) {
				return;
			}
		}
	}
	(door + number)->setOpen(open);
}

Door* Doors::getDoor() {
	return door;
}

int Doors::getNumber() {
	return number;
}

void Doors::draw(RenderWindow& window) {
	for (int i = 0; i < number; i++) {
		(door + i)->draw(window);
	}
}

void Doors::reset(int number) {
	(door + number)->reset();
}

void Doors::reset() {
	for (int i = 0; i < number; i++) {
		(door + i)->reset();
	}
}

Doors::~Doors() {
	delete [] door;
}