#include "Mine.hpp"

Texture* Mine::texture;

Mine::Mine(){
	setSize(Vector2f{ 12,12 });
	setTexture(texture);
}

void Mine::setMineTexture(string textureFile) {
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		a++;
	}
	texture->loadFromFile(textureFile);
}

void Mine::setMinePosition(Vector2f position) {
	startPosition = position;
	reset();
}

void Mine::setDirection(Direction direction) {
	this->direction = direction;
}

void Mine::reset() {
	exist = false;
	setPosition(startPosition);
}