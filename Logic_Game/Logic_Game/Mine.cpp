#include "Mine.hpp"

Texture* Mine::texture;

Mine::Mine(){
	setSize(Vector2f{ 12,12 });
	setTexture(texture);
	setPosition({ 0,0 });
	startPosition = { 0,0 };
	direction = Direction::Up;
	reset();
}

void Mine::setMineTexture(string textureFile) {
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		a++;
	}
	texture->loadFromFile(textureFile);
}

void Mine::setStartPosition(Vector2f position) {
	startPosition = position;
	reset();
}

Vector2f Mine::getStartPosition() {
	return startPosition;
}

void Mine::setDirection(Direction direction) {
	this->direction = direction;
	reset();
}

Mine::Direction Mine::getDirection() {
	return direction;
}

void Mine::setExist(bool exist) {
	this->exist = exist;
}

bool Mine::getExist() {
	return exist;
}

void Mine::draw(bool on, RenderWindow& window) {
	if (!exist) return;
	window.draw(*this);
}

int Mine::run(bool on, Map& map, Door* door, int number) {
	if (on == false && exist == false) return -1;
	if (on == true && exist == false) {
		VectorConverter vec(getPosition());
		if (map.getType(vec.asNumber()) == Square::Wall) return -1;
		exist = true;
	}
	if (clock.getElapsedTime().asSeconds() < 0.03 || exist == false) return -1;
	clock.restart();
	VectorConverter vec(getPosition());
	for (int i = 0; i < number; i++) {
		if ((door + i)->isOpen()) continue;
		if ((door + i)->getPosition() == VectorConverter::convert(vec.asXY().x, vec.asXY().y).asVector2f()) {
			reset();
			return -1;
		}
	}
	if (moveNr == 8) {
		switch (direction) {
		case Up:
			if (map.getType(vec.asNumber() - 18) == Square::Wall) {
				reset();
				return -1;
			}
			for (int i = 0; i < number; i++) {
				if ((door + i)->isOpen()) continue;
				if ((door + i)->getPosition() == VectorConverter::convert(vec.asXY().x, vec.asXY().y - 1).asVector2f()) {
					reset();
					return -1;
				}
			}
			break;
		case Down:
			if (map.getType(vec.asNumber() + 18) == Square::Wall) {
				reset();
				return -1;
			}
			for (int i = 0; i < number; i++) {
				if ((door + i)->isOpen()) continue;
				if ((door + i)->getPosition() == VectorConverter::convert(vec.asXY().x, vec.asXY().y + 1).asVector2f()) {
					reset();
					return -1;
				}
			}
			break;
		case Left:
			if (map.getType(vec.asNumber() - 1) == Square::Wall) {
				reset();
				return -1;
			}
			for (int i = 0; i < number; i++) {
				if ((door + i)->isOpen()) continue;
				if ((door + i)->getPosition() == VectorConverter::convert(vec.asXY().x - 1, vec.asXY().y).asVector2f()) {
					reset();
					return -1;
				}
			}
			break;
		case Right:
			if (map.getType(vec.asNumber() + 1) == Square::Wall) {
				reset();
				return -1;
			}
			for (int i = 0; i < number; i++) {
				if ((door + i)->isOpen()) continue;
				if ((door + i)->getPosition() == VectorConverter::convert(vec.asXY().x + 1, vec.asXY().y).asVector2f()) {
					reset();
					return -1;
				}
			}
			break;
		}
	}
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
	if (moveNr == 10) moveNr = 0;
	return moveNr;
}

void Mine::reset() {
	exist = false;
	moveNr = 0;
	setPosition(startPosition);
	clock.restart();
}