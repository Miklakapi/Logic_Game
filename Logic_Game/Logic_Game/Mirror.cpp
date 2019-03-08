#include "Mirror.hpp"

Texture* Mirror::texture;

IntRect* Mirror::rect;

Mirror::Mirror(){
	laser = new Laser[1];
	laserNr = 1;
	setSize(Vector2f{ 80,80 });
	setTexture(texture);
	setPosition(Vector2f{ 0,0 });
	setType(Type::A1);
	reset();
}

void Mirror::setBlockTexture(string textureFile) {
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		rect = new IntRect[36];
		//------
		*(rect + 0) = { 0,0,80,80 };
		*(rect + 1) = { 80,0,80,80 };
		*(rect + 2) = { 160,0,80,80 };
		*(rect + 3) = { 240,0,80,80 };
		//
		*(rect + 4) = { 0,80,80,80 };
		*(rect + 5) = { 80,80,80,80 };
		*(rect + 6) = { 160,80,80,80 };
		*(rect + 7) = { 240,80,80,80 };
		//
		*(rect + 8) = { 0,160,80,80 };
		//------
		*(rect + 9) = { 320,0,80,80 };
		*(rect + 10) = { 400,0,80,80 };
		*(rect + 11) = { 480,0,80,80 };
		*(rect + 12) = { 560,0,80,80 };
		//
		*(rect + 13) = { 320,80,80,80 };
		*(rect + 14) = { 400,80,80,80 };
		*(rect + 15) = { 480,80,80,80 };
		*(rect + 16) = { 560,80,80,80 };
		//
		*(rect + 17) = { 320,160,80,80 };
		//------
		*(rect + 18) = { 0,240,80,80 };
		*(rect + 19) = { 80,240,80,80 };
		*(rect + 20) = { 160,240,80,80 };
		*(rect + 21) = { 240,240,80,80 };
		//
		*(rect + 22) = { 0,320,80,80 };
		*(rect + 23) = { 80,320,80,80 };
		*(rect + 24) = { 160,320,80,80 };
		*(rect + 25) = { 240,320,80,80 };
		//
		*(rect + 26) = { 0,400,80,80 };
		//------
		*(rect + 27) = { 320,240,80,80 };
		*(rect + 28) = { 400,240,80,80 };
		*(rect + 29) = { 480,240,80,80 };
		*(rect + 30) = { 560,240,80,80 };
		//
		*(rect + 31) = { 320,320,80,80 };
		*(rect + 32) = { 400,320,80,80 };
		*(rect + 33) = { 480,320,80,80 };
		*(rect + 34) = { 560,320,80,80 };
		//
		*(rect + 35) = { 320,400,80,80 };
		//------
		a++;
	}
	texture->loadFromFile(textureFile);
}

Laser* Mirror::getLaser() {
	return laser;
}

int Mirror::getLaserNr() {
	return laserNr;
}

Mirror::Type Mirror::getType() {
	return type;
}

void Mirror::setType(Type type) {
	delete [] laser;
	this->type = type;
	rectNr = type;
	if (type < 4) {
		laser = new Laser[2];
		laserNr = 2;
	}
	else if (type < 8 && type > 3) {
		laser = new Laser[3];
		laserNr = 3;
	}
	else if (type == 8) {
		laser = new Laser[4];
		laserNr = 4;
	}
	reset();
}

bool Mirror::isOnNewPosition() {
	return newPosition;
}

void Mirror::setOnNewPosition(bool newPos) {
	newPosition = newPosition;
}

void Mirror::setOn(bool on) {
	if (this->on == on) return;
	this->on = on;
	if (on) {
		rectNr += 9;
		setTextureRect(*(rect + rectNr));
	}
	else {
		rectNr -= 9;
		setTextureRect(*(rect + rectNr));
		for (int i = 0; i < laserNr; i++) {
			(laser + i)->off();
		}
	}
}

bool Mirror::isOn() {
	return on;
}

int Mirror::getMoveNumber() {
	return moveNr;
}

void Mirror::destroy() {
	if (!exist) return;
	clock.restart();
	exist = false;
	rectNr += 18;
	setTextureRect(*(rect + rectNr));
}

bool Mirror::getExist() {
	return exist;
}

void Mirror::push(Direction direction) {
	this->direction = direction;
	moveNr = 0;
	newPosition = false;
	positionChg = false;
	for (int i = 9; i < laserNr; i++) {
		(laser + i)->off();
	}
}

void Mirror::run() {
	if (clock.getElapsedTime().asSeconds() >= 0.06 && moveNr < 10 && exist) {
		clock.restart();
		switch (direction) {
		case Direction::Up:
			move(Vector2f{ 0, -8 });
			break;
		case Direction::Down:
			move(Vector2f{ 0, 8 });
			break;
		case Direction::Left:
			move(Vector2f{ -8, 0 });
			break;
		case Direction::Right:
			move(Vector2f{ 8, 0 });
			break;
		}
		moveNr++;
	}
	else if (!exist && moveNr != -1) {
		if (clock.getElapsedTime().asSeconds() >= 0.5) {
			setTextureRect(IntRect{ 80,160,1,1 });
			moveNr = -1;
		}
	}
	else if (moveNr == 10 && newPosition == false && positionChg == false) {
		newPosition = true;
		positionChg = true;
	}
}

void Mirror::draw(RenderWindow& window) {
	window.draw(*this);
	for (int i = 0; i < laserNr; i++) {
		(laser + i)->draw(window);
	}
}

void Mirror::reset() {
	exist = true;
	moveNr = 10;
	clock.restart();
	direction = Direction::None;
	on = false;
	rectNr = type;
	setTextureRect(*(rect + rectNr));
	for (int i = 0; i < laserNr; i++) {
		(laser + i)->reset();
	}
	newPosition = true;
	positionChg = true;
}