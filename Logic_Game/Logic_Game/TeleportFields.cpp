#include "TeleportFields.hpp"

TeleportFields::TeleportFields(int number, string textureFile){
	TeleportField::setTeleportTexture(textureFile);
	this->number = number;
	field = new TeleportField[number];
}

void TeleportFields::setTeleportPosition(int number, Vector2f position) {
	(field + number)->setTeleportPosition(position);
}

void TeleportFields::setTeleportSize(int number, Vector2f size) {
	(field + number)->setTeleportSize(size);
}

void TeleportFields::setTeleportPlace(int number, Vector2f position) {
	(field + number)->setTeleportPlace(position);
}

Vector2f TeleportFields::getTeleportPlace(int number) {
	return (field + number)->getTeleportPlace();
}

bool TeleportFields::isOpen(int number) {
	return (field + number)->isOpen();
}

void TeleportFields::setOpen(int number, bool open) {
	(field + number)->setOpen(open);
}

TeleportField* TeleportFields::getTeleportField() {
	return field;
}

int TeleportFields::getNumber() {
	return number;
}

void TeleportFields::draw(RenderWindow& window) {
	for (int i = 0; i < number; i++) {
		(field + i)->draw(window);
	}
}

void TeleportFields::run(Player& player, SlidingBlock* block, int number, Mirror* mirror, int number2) {
	for (int i = 0; i < this->number; i++) {
		if (player.getPosition() == (field + i)->getPosition()) {
			if (!(field + i)->isOpen()) continue;
			for (int j = 0; j < number; j++) {
				if (!(block + j)->getExist()) continue;
				if ((block + j)->getPosition() == (field + i)->getTeleportPlace()) return;
			}
			for (int j = 0; j < number2; j++) {
				if (!(mirror + j)->getExist()) continue;
				if ((mirror + j)->getPosition() == (field + i)->getTeleportPlace()) return;
			}
			player.setPosition((field + i)->getTeleportPlace());
		}
	}
}

void TeleportFields::reset(int number) {
	(field + number)->reset();
}

void TeleportFields::reset() {
	for (int i = 0; i < number; i++) {
		(field + number)->reset();
	}
}

TeleportFields::~TeleportFields() {
	delete [] field;
}