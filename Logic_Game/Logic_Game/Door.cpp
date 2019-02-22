#include "Door.hpp"

Texture* Door::texture;

Door::Door() {
	setDoorPosition(Vector2f{ 0,0 });
	setDoorSize(Vector2f{ 80,80 });
	setTexture(texture);
	background.setFillColor(Color::Red);
	reset();
}

void Door::setDoorTexture(string textureFile) {
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		a++;
	}
	texture->loadFromFile(textureFile);
}

void Door::setDoorPosition(Vector2f position) {
	setPosition(position);
	background.setPosition(position);
}

void Door::setDoorSize(Vector2f size) {
	setSize(size);
	background.setSize(size);
}

bool Door::isOpen() {
	return open;
}

void Door::setOpen(bool open) {
	if (open && open != this->open) {
		background.setFillColor(Color::Green);
		clock.restart();
	}
	else if ((!open) && open != this->open) {
		background.setFillColor(Color::Red);
	}
	else {
		return;
	}
	this->open = open;
	return;
}

void Door::draw(RenderWindow& window) {
	if (!open || (open && clock.getElapsedTime().asSeconds() <= 0.7)) {
		window.draw(background);
		window.draw(*this);
	}
}

void Door::reset() {
	setOpen(false);
}