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

void SlidingBlock::destroy() {
	clock.restart();
	exist = false;
	setTextureRect(IntRect{ 80,0,80,80 });
}

bool SlidingBlock::getExist() {
	return exist;
}

bool SlidingBlock::push(Direction direction, Map& map, ShootingBlock* blockS, int number, Door* door, int number2,
	LaserMachine* machine, int number3, Mirror* mirror, int number4) {

	if (moveNr != 10) return false;
	if (direction == Direction::None) {
		this->direction = direction;
		return false;
	}
	Vector2f vec = getPosition();
	VectorConverter convert = VectorConverter::convert(vec);
	switch (direction) {
	case Up:
		if (map.getType(convert.asNumber() - 18) == Square::Type::Wall) return false;
		for (int i = 0; i < number; i++) {
			if ((blockS + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 1).asVector2f()) return false;
		}
		for (int i = 0; i < number2; i++) {
			if ((door + i)->isOpen()) continue;
			if ((door + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 1).asVector2f()) return false;
		}
		for (int i = 0; i < number3; i++) {
			if ((machine + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 1).asVector2f()) return false;
		}
		for (int i = 0; i < number4; i++) {
			if ((mirror + i)->getExist() == false) continue;
			if ((mirror + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 1).asVector2f()) return false;
		}
		break;
	case Down:
		if (map.getType(convert.asNumber() + 18) == Square::Type::Wall) return false;
		for (int i = 0; i < number; i++) {
			if ((blockS + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 1).asVector2f()) return false;
		}
		for (int i = 0; i < number2; i++) {
			if ((door + i)->isOpen()) continue;
			if ((door + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 1).asVector2f()) return false;
		}
		for (int i = 0; i < number3; i++) {
			if ((machine + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 1).asVector2f()) return false;
		}
		for (int i = 0; i < number4; i++) {
			if ((mirror + i)->getExist() == false) continue;
			if ((mirror + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 1).asVector2f()) return false;
		}
		break;
	case Left:
		if (map.getType(convert.asNumber() - 1) == Square::Type::Wall) return false;
		for (int i = 0; i < number; i++) {
			if ((blockS + i)->getPosition() == VectorConverter::convert(convert.asXY().x - 1, convert.asXY().y).asVector2f()) return false;
		}
		for (int i = 0; i < number2; i++) {
			if ((door + i)->isOpen()) continue;
			if ((door + i)->getPosition() == VectorConverter::convert(convert.asXY().x - 1, convert.asXY().y).asVector2f()) return false;
		}
		for (int i = 0; i < number3; i++) {
			if ((machine + i)->getPosition() == VectorConverter::convert(convert.asXY().x - 1, convert.asXY().y).asVector2f()) return false;
		}
		for (int i = 0; i < number4; i++) {
			if ((mirror + i)->getExist() == false) continue;
			if ((mirror + i)->getPosition() == VectorConverter::convert(convert.asXY().x - 1, convert.asXY().y).asVector2f()) return false;
		}
		break;
	case Right:
		if (map.getType(convert.asNumber() + 1) == Square::Type::Wall) return false;
		for (int i = 0; i < number; i++) {
			if ((blockS + i)->getPosition() == VectorConverter::convert(convert.asXY().x + 1, convert.asXY().y).asVector2f()) return false;
		}
		for (int i = 0; i < number2; i++) {
			if ((door + i)->isOpen()) continue;
			if ((door + i)->getPosition() == VectorConverter::convert(convert.asXY().x + 1, convert.asXY().y).asVector2f()) return false;
		}
		for (int i = 0; i < number3; i++) {
			if ((machine + i)->getPosition() == VectorConverter::convert(convert.asXY().x + 1, convert.asXY().y).asVector2f()) return false;
		}
		for (int i = 0; i < number4; i++) {
			if ((mirror + i)->getExist() == false) continue;
			if ((mirror + i)->getPosition() == VectorConverter::convert(convert.asXY().x + 1, convert.asXY().y).asVector2f()) return false;
		}
		break;
	}
	this->direction = direction;
	moveNr = 0;
	return true;
}

void SlidingBlock::run(Door* door, int number) {
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
	if (exist) {
		for (int i = 0; i < number; i++) {
			if ((door + i)->isOpen() == false &&
				(door + i)->getPosition().x < getPosition().x + 80 && (door + i)->getPosition().x + 80 > getPosition().x &&
				(door + i)->getPosition().y < getPosition().y + 80 && (door + i)->getPosition().y + 80 > getPosition().y) {
				destroy();
			}
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