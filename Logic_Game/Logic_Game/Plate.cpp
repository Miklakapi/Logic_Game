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

void Plate::reset() {
	setPressure(false);
}