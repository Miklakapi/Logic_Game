#include "ShootingBlock.hpp"

Texture* ShootingBlock::texture;

IntRect* ShootingBlock::rect;

ShootingBlock::ShootingBlock(){
	mine = new Mine[1];
	type = Type::A1;
	setBlockPosition(Vector2f{ 0,0 });
	setBlockSize(Vector2f{ 80,80 });
	setTexture(texture);
	setType(Type::A1);
	background.setFillColor(Color::Red);
	setDelay(0);
	reset();
}

void ShootingBlock::setBlockTexture(string textureFile) {
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

void ShootingBlock::setBlockPosition(Vector2f position) {
	setPosition(position);
	background.setPosition(position);
	setType(type);
}

void ShootingBlock::setBlockSize(Vector2f size) {
	setSize(size);
	background.setSize(size);
}

void ShootingBlock::setDelay(int delay) {
	this->delay = delay;
}

int ShootingBlock::getDelay() {
	return delay;
}

void ShootingBlock::setType(Type type) {
	delete [] mine;
	setTextureRect(*(rect + type));
	this->type = type;
	Vector2f pos = getPosition();
	if (type >= 0 && type < 4) {
		mine = new Mine[1];
		switch (type) {
		case A1:
			mine->setStartPosition(Vector2f{ pos.x + 34,pos.y - 12 });
			mine->setDirection(Mine::Direction::Up);
			break;
		case A2:
			mine->setStartPosition(Vector2f{ pos.x + 80,pos.y + 34 });
			mine->setDirection(Mine::Direction::Right);
			break;
		case A3:
			mine->setStartPosition(Vector2f{ pos.x + 34,pos.y + 80 });
			mine->setDirection(Mine::Direction::Down);
			break;
		case A4:
			mine->setStartPosition(Vector2f{ pos.x - 12,pos.y + 34 });
			mine->setDirection(Mine::Direction::Left);
			break;
		}
		mineNr = 1;
	}
	else if (type > 3 && type < 10) {
		mine = new Mine[2];
		switch (type) {
		case B1:
			(mine + 0)->setStartPosition(Vector2f{ pos.x + 34,pos.y - 12 });
			(mine + 0)->setDirection(Mine::Direction::Up);
			(mine + 1)->setStartPosition(Vector2f{ pos.x + 80,pos.y + 34 });
			(mine + 1)->setDirection(Mine::Direction::Right);
			break;
		case B2:
			(mine + 0)->setStartPosition(Vector2f{ pos.x + 80,pos.y + 34 });
			(mine + 0)->setDirection(Mine::Direction::Right);
			(mine + 1)->setStartPosition(Vector2f{ pos.x + 34,pos.y + 80 });
			(mine + 1)->setDirection(Mine::Direction::Down);
			break;
		case B3:
			(mine + 0)->setStartPosition(Vector2f{ pos.x + 34,pos.y + 80 });
			(mine + 0)->setDirection(Mine::Direction::Down);
			(mine + 1)->setStartPosition(Vector2f{ pos.x - 12,pos.y + 34 });
			(mine + 1)->setDirection(Mine::Direction::Left);
			break;
		case B4:
			(mine + 0)->setStartPosition(Vector2f{ pos.x - 12,pos.y + 34 });
			(mine + 0)->setDirection(Mine::Direction::Left);
			(mine + 1)->setStartPosition(Vector2f{ pos.x + 34,pos.y - 12 });
			(mine + 1)->setDirection(Mine::Direction::Up);
			break;
		case B5:
			(mine + 0)->setStartPosition(Vector2f{ pos.x + 34,pos.y - 12 });
			(mine + 0)->setDirection(Mine::Direction::Up);
			(mine + 1)->setStartPosition(Vector2f{ pos.x + 34,pos.y + 80 });
			(mine + 1)->setDirection(Mine::Direction::Down);
			break;
		case B6:
			(mine + 0)->setStartPosition(Vector2f{ pos.x - 12,pos.y + 34 });
			(mine + 0)->setDirection(Mine::Direction::Left);
			(mine + 1)->setStartPosition(Vector2f{ pos.x + 80,pos.y + 34 });
			(mine + 1)->setDirection(Mine::Direction::Right);
			break;
		}
		mineNr = 2;
	}
	else if (type > 9 && type < 14) {
		mine = new Mine[3];
		switch (type) {
		case C1:
			(mine + 0)->setStartPosition(Vector2f{ pos.x - 12,pos.y + 34 });
			(mine + 0)->setDirection(Mine::Direction::Left);
			(mine + 1)->setStartPosition(Vector2f{ pos.x + 34,pos.y - 12 });
			(mine + 1)->setDirection(Mine::Direction::Up);
			(mine + 2)->setStartPosition(Vector2f{ pos.x + 80,pos.y + 34 });
			(mine + 2)->setDirection(Mine::Direction::Right);
			break;
		case C2:
			(mine + 0)->setStartPosition(Vector2f{ pos.x + 34,pos.y - 12 });
			(mine + 0)->setDirection(Mine::Direction::Up);
			(mine + 1)->setStartPosition(Vector2f{ pos.x + 80,pos.y + 34 });
			(mine + 1)->setDirection(Mine::Direction::Right);
			(mine + 2)->setStartPosition(Vector2f{ pos.x + 34,pos.y + 80 });
			(mine + 2)->setDirection(Mine::Direction::Down);
			break;
		case C3:
			(mine + 0)->setStartPosition(Vector2f{ pos.x + 80,pos.y + 34 });
			(mine + 0)->setDirection(Mine::Direction::Right);
			(mine + 1)->setStartPosition(Vector2f{ pos.x + 34,pos.y + 80 });
			(mine + 1)->setDirection(Mine::Direction::Down);
			(mine + 2)->setStartPosition(Vector2f{ pos.x - 12,pos.y + 34 });
			(mine + 2)->setDirection(Mine::Direction::Left);
			break;
		case C4:
			(mine + 0)->setStartPosition(Vector2f{ pos.x + 34,pos.y + 80 });
			(mine + 0)->setDirection(Mine::Direction::Down);
			(mine + 1)->setStartPosition(Vector2f{ pos.x - 12,pos.y + 34 });
			(mine + 1)->setDirection(Mine::Direction::Left);
			(mine + 2)->setStartPosition(Vector2f{ pos.x + 34,pos.y - 12 });
			(mine + 2)->setDirection(Mine::Direction::Up);
			break;
		}
		mineNr = 3;
	}
	else if (type == 14) {
		mine = new Mine[4];
		switch (type) {
		case D1:
			(mine + 0)->setStartPosition(Vector2f{ pos.x + 34,pos.y - 12 });
			(mine + 0)->setDirection(Mine::Direction::Up);
			(mine + 1)->setStartPosition(Vector2f{ pos.x + 80,pos.y + 34 });
			(mine + 1)->setDirection(Mine::Direction::Right);
			(mine + 2)->setStartPosition(Vector2f{ pos.x + 34,pos.y + 80 });
			(mine + 2)->setDirection(Mine::Direction::Down);
			(mine + 3)->setStartPosition(Vector2f{ pos.x - 12,pos.y + 34 });
			(mine + 3)->setDirection(Mine::Direction::Left);
			break;
		}
		mineNr = 4;
	}
}

ShootingBlock::Type ShootingBlock::getType() {
	return type;
}

void ShootingBlock::setOn(bool on) {
	if (on && this->on != on) background.setFillColor(Color::Green);
	else if (!on && this->on != on) background.setFillColor(Color::Red);
	else {
		return;
	}
	this->on = on;
}

bool ShootingBlock::isOn() {
	return on;
}

void ShootingBlock::draw(RenderWindow& window) {
	window.draw(background);
	window.draw(*this);
	if (type < 4) (mine + 0)->draw(on, window);
	else if (type >= 4 && type < 10) {
		(mine + 0)->draw(on, window);
		(mine + 1)->draw(on, window);
	}
	else if (type >= 10 && type < 14) {
		(mine + 0)->draw(on, window);
		(mine + 1)->draw(on, window);
		(mine + 2)->draw(on, window);
	}
	else if (type == 14) {
		(mine + 0)->draw(on, window);
		(mine + 1)->draw(on, window);
		(mine + 2)->draw(on, window);
		(mine + 3)-> draw(on, window);
	}
}

void ShootingBlock::run(Map& map, Door* door, int number, ShootingBlock* block, int number2) {
	for (int i = 0; i < mineNr; i++) {
		(mine + i)->run(on, map, door, number);
	}
}

void ShootingBlock::reset() {
	setOn(false);
}