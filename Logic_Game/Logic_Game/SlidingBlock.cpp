#include "SlidingBlock.hpp"

Texture* SlidingBlock::texture;

SlidingBlock::SlidingBlock(Vector2f position, string textureFile){
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		texture->loadFromFile(textureFile);
		a++;
	}
	setSize(Vector2f{ 80,80 });
	setTexture(texture);
	setTextureRect(IntRect{ 0,0,80,80 });
	setPosition(position);
	reset();
}

void SlidingBlock::destroy() {
	clock.restart();
	exist = false;
	setTextureRect(IntRect{ 80,0,80,80 });
}

void SlidingBlock::push(Direction direction) {
	if (moveNr != 10) return;
	this->direction = direction;
	if (direction == Direction::None) return;
	moveNr = 0;
}

bool SlidingBlock::getExist() {
	return exist;
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