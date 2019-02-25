#include "TeleportField.hpp"

Texture* TeleportField::texture;

TeleportField::TeleportField(Vector2f position){
	setTeleportPosition(Vector2f{ 0,0 });
	setTeleportSize(Vector2f{ 80,80 });
	setTexture(texture);
	background.setFillColor(Color::Red);
	reset();
}

void TeleportField::setTeleportTexture(string textureFile) {
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		a++;
	}
	texture->loadFromFile(textureFile);
}

void TeleportField::setTeleportPosition(Vector2f position) {
	setPosition(position);
	background.setPosition(position);
}

void TeleportField::setTeleportSize(Vector2f size) {
	setSize(size);
	background.setSize(size);
}

void TeleportField::setTeleportPlace(Vector2f place) {
	teleportPlace = place;
}

Vector2f TeleportField::getTeleportPlace() {
	return teleportPlace;
}

bool TeleportField::isOpen() {
	return open;
}

void TeleportField::setOpen(bool open) {
	if (open && open != this->open) {
		background.setFillColor(Color::Green);
	}
	else if ((!open) && open != this->open) {
		background.setFillColor(Color::Red);
	}
	else {
		return;
	}
	this->open = open;
}

void TeleportField::draw(RenderWindow& window) {
	window.draw(background);
	window.draw(*this);
}

void TeleportField::reset() {
	setOpen(false);
	teleportPlace = { 0,0 };
}