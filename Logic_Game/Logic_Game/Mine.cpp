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

int Mine::getMoveNr() {
	return moveNr;
}

void Mine::draw(RenderWindow& window) {
	if (!exist) return;
	window.draw(*this);
}

void Mine::run(bool on) {
	if (on == false && exist == false) return;
	if (on == true && exist == false) {
		exist = true;
		moveNr = 0;
		setPosition(startPosition);
		clock.restart();
	}
	if (clock.getElapsedTime().asSeconds() < 0.03) return;
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
	if (moveNr == 10) moveNr = 0;
}

void Mine::reset() {
	exist = false;
	moveNr = 0;
	setPosition(startPosition);
	clock.restart();
}