#include "TeleportField.hpp"

Texture* TeleportField::texture;

TeleportField::TeleportField(Vector2f position, Color color, string textureFile){
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		texture->loadFromFile(textureFile);
		a++;
	}
	setSize(Vector2f{ 80,80 });
	setPosition(position);
	setTexture(texture);

	background.setSize(Vector2f{ 80,80 });
	background.setPosition(position);
	background.setFillColor(color);

	this->color = color;

	reset();
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
		background.setFillColor(color);
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
}