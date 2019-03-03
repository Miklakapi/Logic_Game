#include "Laser.hpp"

Texture* SimpleLaser::texture;

IntRect* SimpleLaser::rect;

SimpleLaser::SimpleLaser(){
	setSize(Vector2f{ 80,80 });
	setPosition(Vector2f{ 0,0 });
	setTexture(texture);
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
	laserNr = 1;
	reset();
}

void Laser::setPosition(Vector2f position, Direction direction, int laserNr) {
	VectorConverter vec(position);
	this->laserNr = laserNr;
	delete [] laser;
	laser = new SimpleLaser[laserNr];
	int a = 1;
	switch (direction) {
	case Up:
		
		for (int i = 0; i < laserNr; i++) {
			(laser + i)->setPosition(VectorConverter::convert(vec.asXY().x, vec.asXY().y - a).asVector2f());
			a++;
		}
		break;
	case Down:
		for (int i = 0; i < laserNr; i++) {
			(laser + i)->setPosition(VectorConverter::convert(vec.asXY().x, vec.asXY().y + a).asVector2f());
			a++;
		}
		break;
	case Left:
		for (int i = 0; i < laserNr; i++) {
			(laser + i)->setPosition(VectorConverter::convert(vec.asXY().x - a, vec.asXY().y).asVector2f());
			a++;
		}
		break;
	case Right:
		for (int i = 0; i < laserNr; i++) {
			(laser + i)->setPosition(VectorConverter::convert(vec.asXY().x + a, vec.asXY().y).asVector2f());
			a++;
		}
		break;
	}
}

void Laser::draw(RenderWindow& window) {
	for (int i = 0; i < laserNr; i++) {
		laser->draw(window);
	}
}

void Laser::run(bool on, int nr) {
	if (!on) {
		actualLaser = -1;
		for (int i = 0; i < laserNr; i++) {
			laser->setExist(false);
		}
	}
	else {
		if (nr > laserNr) nr = laserNr;
		if (actualLaser != nr) {
			actualLaser = nr;
			for (int i = 0; i < laserNr; i++) {
				if (i < nr)laser->setExist(true);
				else if (i > nr)laser->setExist(false);
			}
		}
	}
}

void Laser::reset() {
	actualLaser = -1;
	for (int i = 0; i < laserNr; i++) {
		laser->setExist(false);
	}
}