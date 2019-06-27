#include "LaserReceiver.hpp"

Texture* LaserReceiver::texture;
IntRect* LaserReceiver::rect;

LaserReceiver::LaserReceiver(){
	on = false;
	setSize({ 80,80 });
	setTexture(texture);
	setType(A1);
}

void LaserReceiver::setReceiverTexture(string textureFile) {
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		rect = new IntRect[30];
		*(rect + 0) = { 0, 0, 80, 80 };
		*(rect + 1) = { 80, 0, 80, 80 };
		*(rect + 2) = { 160, 0, 80, 80 };
		*(rect + 3) = { 240, 0, 80, 80 };

		*(rect + 4) = { 0, 80, 80, 80 };
		*(rect + 5) = { 80, 80, 80, 80 };
		*(rect + 6) = { 160, 80, 80, 80 };
		*(rect + 7) = { 240, 80, 80, 80 };
		*(rect + 8) = { 320, 80, 80, 80 };
		*(rect + 9) = { 400, 80, 80, 80 };

		*(rect + 10) = { 0, 160, 80, 80 };
		*(rect + 11) = { 80, 160, 80, 80 };
		*(rect + 12) = { 160, 160, 80, 80 };
		*(rect + 13) = { 240, 160, 80, 80 };

		*(rect + 14) = { 0, 240, 80, 80 };

		*(rect + 15) = { 480, 0, 80, 80 };
		*(rect + 16) = { 560, 0, 80, 80 };
		*(rect + 17) = { 640, 0, 80, 80 };
		*(rect + 18) = { 720, 0, 80, 80 };

		*(rect + 19) = { 480, 80, 80, 80 };
		*(rect + 20) = { 560, 80, 80, 80 };
		*(rect + 21) = { 640, 80, 80, 80 };
		*(rect + 22) = { 720, 80, 80, 80 };
		*(rect + 23) = { 800, 80, 80, 80 };
		*(rect + 24) = { 880, 80, 80, 80 };

		*(rect + 25) = { 480, 160, 80, 80 };
		*(rect + 26) = { 560, 160, 80, 80 };
		*(rect + 27) = { 640, 160, 80, 80 };
		*(rect + 28) = { 720, 160, 80, 80 };

		*(rect + 29) = { 480, 240, 80, 80 };
		a++;
	}
	texture->loadFromFile(textureFile);
}

LaserReceiver::Type LaserReceiver::getType() {
	return type;
}

void LaserReceiver::setType(Type type) {
	this->type = type;
	setTextureRect(*(rect + type));
}

bool LaserReceiver::getOn() {
	return on;
}

void LaserReceiver::setOn(bool on) {
	if (this->on == on) return;
	this->on = on;
	if (!on) setTextureRect(*(rect + type));
	else setTextureRect(*(rect + type + 15));
}

void LaserReceiver::draw(RenderWindow& window) {
	window.draw(*this);
}

void LaserReceiver::reset() {
	on = false;
}