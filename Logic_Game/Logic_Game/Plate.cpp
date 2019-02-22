#include "Plate.hpp"

Texture* Plate::texture;

Plate::Plate(){
	setTexture(texture);
	background.setFillColor(Color::Red);
	setPlatePosition(Vector2f{ 0,0 });
	setPlateSize(Vector2f{ 80,80 });
	reset();
}

void Plate::setPlateTexture(string textureFile) {
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		a++;
	}
	texture->loadFromFile(textureFile);
}

void Plate::setPlatePosition(Vector2f position) {
	setPosition(position);
	background.setPosition(position);
}

void Plate::setPlateSize(Vector2f size) {
	setSize(size);
	background.setSize(size);
}

bool Plate::isPressed() {
	return pressed;
}

void Plate::setPressure(bool pressed) {
	if (pressed && pressed != this->pressed) {
		background.setFillColor(Color::Green);
	}
	else if ((!pressed) && pressed != this->pressed) {
		background.setFillColor(Color::Red);
	}
	else {
		return;
	}
	this->pressed = pressed;
}

void Plate::draw(RenderWindow& window) {
	window.draw(background);
	window.draw(*this);
}

bool Plate::run(Player& player) {
	setPressure(false);
	if (player.getPosition().x < getPosition().x + 80 && player.getPosition().x + 80 > getPosition().x &&
		player.getPosition().y < getPosition().y + 80 && player.getPosition().y + 80 > getPosition().y) {
		setPressure(true);
		return true;
	}
	return false;
}

bool Plate::run(SlidingBlock* block, int number) {
	setPressure(false);
	for (int i = 0; i < number; i++) {
		if (!(block + i)->getExist()) continue;
		if ((block + i)->getPosition().x < getPosition().x + 80 && (block + i)->getPosition().x + 80 > getPosition().x &&
			(block + i)->getPosition().y < getPosition().y + 80 && (block + i)->getPosition().y + 80 > getPosition().y) {
			setPressure(true);
			return true;
		}
	}
	return false;
}

bool Plate::run(Mirror* mirror, int number) {
	setPressure(false);
	for (int i = 0; i < number; i++) {
		if (!(mirror + i)->getExist()) continue;
		if ((mirror + i)->getPosition().x < getPosition().x + 80 && (mirror + i)->getPosition().x + 80 > getPosition().x &&
			(mirror + i)->getPosition().y < getPosition().y + 80 && (mirror + i)->getPosition().y + 80 > getPosition().y) {
			setPressure(true);
			return true;
		}
	}
	return false;
}

void Plate::reset() {
	setPressure(false);
}