#include "SlidingBlock.hpp"

Texture* SlidingBlock::texture;

SlidingBlock::SlidingBlock(){
	setSize(Vector2f{ 80,80 });
	setTexture(texture);
	setTextureRect(IntRect{ 0,0,80,80 });
	setPosition(Vector2f{ 0,0 });
	reset();
}

void SlidingBlock::setBlockTexture(string textureFile) {
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		a++;
	}
	texture->loadFromFile(textureFile);
}

int SlidingBlock::getMoveNumber() {
	return moveNr;
}

void SlidingBlock::destroy() {
	clock.restart();
	exist = false;
	setTextureRect(IntRect{ 80,0,80,80 });
}

bool SlidingBlock::getExist() {
	return exist;
}

void SlidingBlock::push(Direction direction) {
	this->direction = direction;
	moveNr = 0;
}

void SlidingBlock::run() {
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
			setTextureRect(IntRect{ 160,0,1,1 });
			moveNr = -1;
		}
	}
}

void SlidingBlock::draw(RenderWindow& window) {
	window.draw(*this);
}

void SlidingBlock::reset() {
	exist = true;
	moveNr = 10;
	clock.restart();
	direction = Direction::None;
}