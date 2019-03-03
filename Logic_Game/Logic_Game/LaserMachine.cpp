#include "LaserMachine.hpp"

Texture* LaserMachine::texture;

IntRect* LaserMachine::rect;

LaserMachine::LaserMachine(){
	laser = new Laser[1];
	laserNr = 1;
	setSize({ 80,80 });
	background.setSize({ 80,80 });
	setTexture(texture);
	setType(Type::A1);
	setOn(false);
}

void LaserMachine::setMachineTexture(string textureFile) {
	static int a = 0;
	if (a == 0) {
		rect = new IntRect[15];
		*(rect + 0) = { 0,0,80,80 };
		*(rect + 1) = { 80,0,80,80 };
		*(rect + 2) = { 160,0,80,80 };
		*(rect + 3) = { 240,0,80,80 };
		*(rect + 4) = { 0,80,80,80 };
		*(rect + 5) = { 80,80,80,80 };
		*(rect + 6) = { 160,80,80,80 };
		*(rect + 7) = { 240,80,80,80 };
		*(rect + 8) = { 320,80,80,80 };
		*(rect + 9) = { 400,80,80,80 };
		*(rect + 10) = { 0,160,80,80 };
		*(rect + 11) = { 80,160,80,80 };
		*(rect + 12) = { 160,160,80,80 };
		*(rect + 13) = { 240,160,80,80 };
		*(rect + 14) = { 0,240,80,80 };
		texture = new Texture;
		a++;
	}
	texture->loadFromFile(textureFile);
}

void LaserMachine::setMachinePosition(Vector2f position) {
	setPosition(position);
	background.setPosition(position);
}

void LaserMachine::setMachineSize(Vector2f size) {
	setSize(size);
	background.setSize(size);
}

Laser* LaserMachine::getLaser() {
	return laser;
}

int LaserMachine::getLaserNr() {
	return laserNr;
}

void LaserMachine::setType(Type type) {
	delete [] laser;
	this->type = type;
	setTextureRect(*(rect + type));
	if (type < 4) {
		laser = new Laser[1];
		laserNr = 1;
	}
	else if (type < 10 && type >3) {
		laser = new Laser[2];
		laserNr = 2;
	}
	else if (type < 14 && type > 9) {
		laser = new Laser[3];
		laserNr = 3;
	}
	else if (type == 14) {
		laser = new Laser[4];
		laserNr = 4;
	}
}

LaserMachine::Type LaserMachine::getType() {
	return type;
}

void LaserMachine::setOn(bool on) {
	if (this->on == on) return;
	this->on = on;
	if (on) background.setFillColor(Color::Green);
	else background.setFillColor(Color::Red);
}

bool LaserMachine::isOn() {
	return on;
}

void LaserMachine::draw(RenderWindow& window) {
	window.draw(background);
	window.draw(*this);
	for (int i = 0; i < laserNr; i++) {
		(laser + i)->draw(window);
	}
}

void LaserMachine::reset() {
	setOn(false);
	for (int i = 0; i < laserNr; i++) {
		(laser + i)->reset();
	}
}