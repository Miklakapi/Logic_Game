#include "Plate.hpp"

Texture* Plate::texture;

Plate::Plate(Vector2f position, Color color, string textureFile){
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		texture->loadFromFile(textureFile);
		a++;
	}
	setSize(Vector2f{80,80});
	setPosition(position);
	setTexture(texture);

	background.setSize(Vector2f{ 80,80 });
	background.setPosition(position);
	background.setFillColor(color);

	this->color = color;

	reset();
}

bool Plate::isPressed() {
	return pressed;
}

void Plate::setPressure(bool pressed) {
	if (pressed && pressed != this->pressed) {
		background.setFillColor(Color::Green);
	}
	else if ((!pressed) && pressed != this->pressed) {
		background.setFillColor(color);
	}
	else {
		return;
	}
	this->pressed = pressed;
}

void Plate::setColor(Color color) {
	background.setFillColor(color);
}

void Plate::draw(RenderWindow& window) {
	window.draw(background);
	window.draw(*this);
}

void Plate::reset() {
	setPressure(false);
}