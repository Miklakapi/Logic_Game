#include "Laser.hpp"

Texture* SimpleLaser::texture;

IntRect* SimpleLaser::rect;

SimpleLaser::SimpleLaser(){
	setSize(Vector2f{ 80,80 });
	setPosition(Vector2f{ 0,0 });
	setTexture(texture);
	setDirection(Vertical);
	reset();
}

void SimpleLaser::setLaserTexture(string textureFile) {
	static int a = 0;
	if (a == 0) {
		rect = new IntRect[2];
		*(rect + 0) = { 0,0,80,80 };
		*(rect + 1) = { 80,0,80,80 };
		texture = new Texture;
		a++;
	}
	texture->loadFromFile(textureFile);
}

void SimpleLaser::setDirection(Direction direction) {
	this->direction = direction;
	switch (direction) {
	case Vertical:
		setTextureRect(*(rect + 0));
		break;
	case Horizontal:
		setTextureRect(*(rect + 1));
		break;
	}
}

SimpleLaser::Direction SimpleLaser::getDirection() {
	return direction;
}

void SimpleLaser::setExist(bool exist) {
	this->exist = exist;
}

bool SimpleLaser::getExist() {
	return exist;
}

void SimpleLaser::draw(RenderWindow& window) {
	if (exist) window.draw(*this);
}

void SimpleLaser::reset() {
	exist = false;
}

////////////////////////////////////////////
////////////////////////////////////////////

Laser::Laser() {
	laser = new SimpleLaser[1];
}

void Laser::setPosition(Vector2f position, Direction direction, int laserNr) {
	delete [] laser;
	laser = new SimpleLaser[laserNr];
	this->laserNr = laserNr;
	this->direction = direction;

	SimpleLaser::Direction direction2;
	if (direction == Up || direction == Down) direction2 = SimpleLaser::Vertical;
	else direction2 = SimpleLaser::Horizontal;

	VectorConverter vec(position);
	int x(0), y(0);

	switch (direction) {
	case Up:
		x = 0;
		y = -1;
		vec = { vec.asXY().x, vec.asXY().y - 1 };
		break;
	case Down:
		x = 0;
		y = 1;
		vec = { vec.asXY().x, vec.asXY().y + 1 };
		break;
	case Left:
		x = -1;
		y = 0;
		vec = { vec.asXY().x - 1, vec.asXY().y };
		break;
	case Right:
		x = 1;
		y = 0;
		vec = { vec.asXY().x + 1, vec.asXY().y };
		break;
	}
	for (int i = 0; i < laserNr; i++) {
		(laser + i)->setDirection(direction2);
		(laser + i)->setPosition(VectorConverter::convert(vec.asXY().x + x * i, vec.asXY().y + y * i).asVector2f());
	}
}

SimpleLaser* Laser::getSimpleLaser() {
	return laser;
}

Laser::Direction Laser::getDirection() {
	return direction;
}

int Laser::getLaserNr() {
	return laserNr;
}

void Laser::draw(RenderWindow& window) {
	for (int i = 0; i < laserNr; i++) {
		(laser + i)->draw(window);
	}
}

void Laser::setOn(bool on) {
	if (on) {
		for (int i = 0; i < laserNr; i++) {
			(laser + i)->setExist(true);
		}
	}
	else {
		for (int i = 0; i < laserNr; i++) {
			(laser + i)->setExist(false);
		}
	}
	this->on = on;
}

bool Laser::isOn() {
	return on;
}

void Laser::reset() {
	for (int i = 0; i < laserNr; i++) {
		(laser + i)->reset();
	}
}

Laser::~Laser() {
	delete [] laser;
}