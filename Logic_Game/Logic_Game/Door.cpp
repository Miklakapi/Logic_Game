#include "Door.hpp"

Texture* Door::texture;

Door::Door(Vector2f position, Color color, string textureFile) {
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

bool Door::isOpen() {
	return open;
}

void Door::setOpen(bool open) {
	if (open && open != this->open) {
		background.setFillColor(Color::Green);
		clock.restart();
	}
	else if ((!open) && open != this->open) {
		background.setFillColor(color);
	}
	else {
		return;
	}
	this->open = open;
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