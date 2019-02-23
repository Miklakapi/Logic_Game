#include "Player.hpp"


Player::Player(Vector2f position, string textureFile){
	rect = new IntRect[12];
	*(rect + 0) = { 0,0,80,80 };
	*(rect + 1) = { 80,0,80,80 };
	*(rect + 2) = { 160,0,80,80 };
	*(rect + 3) = { 0,80,80,80 };
	*(rect + 4) = { 80,80,80,80 };
	*(rect + 5) = { 160,80,80,80 };
	//
	*(rect + 6) = { 240,0,80,80 };
	*(rect + 7) = { 320,0,80,80 };
	*(rect + 8) = { 400,0,80,80 };
	*(rect + 9) = { 240,80,80,80 };
	*(rect + 10) = { 320,80,80,80 };
	*(rect + 11) = { 400,80,80,80 };
	setPlayerTexture(textureFile);
	setSize(Vector2f{ 80,80 });
	setPosition(Vector2f{ 0,0 });
	reset();
}

void Player::setStage(int stage) {
	if (stage > 5 || stage < 0) stage = 0;
	clockStage.restart();
	setTextureRect(*(rect + stage));
	this->stage = stage;
}

void Player::setPlayerTexture(string textureFile) {
	texture.loadFromFile(textureFile);
	setTexture(&texture);
}

void Player::setLive(bool live) {
	if (!live) {
		setTextureRect(*(rect + stage + 6));
	}
	clockStage.restart();
	this->live = live;
}

bool Player::getLive() {
	return live;
}

void Player::movePlayer(Direction direction, Map& map, ShootingBlock* blockS, int number, Door* door, int number2,
	LaserMachine* machine, int number3, SlidingBlock* block, int number4, Mirror* mirror, int number5) {

	if (moveNr != 10) return;
	if (direction == Direction::None) {
		this->direction = direction;
		return;
	}
	bool a(false);
	Vector2f vec = getPosition();
	VectorConverter convert = VectorConverter::convert(vec);
	switch (direction) {
	case Up:
		if (map.getType(convert.asNumber() - 18) == Square::Type::Wall) return;
		for (int i = 0; i < number; i++) {
			if ((blockS + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 1).asVector2f()) return;
		}
		for (int i = 0; i < number2; i++) {
			if ((door + i)->isOpen()) continue;
			if ((door + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 1).asVector2f()) return;
		}
		for (int i = 0; i < number3; i++) {
			if ((machine + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 1).asVector2f()) return;
		}
		for (int i = 0; i < number4; i++) {
			if ((block + i)->getExist() == false) continue;
			if ((block + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 1).asVector2f()) {
				if ((block + i)->push(SlidingBlock::Up, map, blockS, number, door, number2, machine, number3) == false) return;
				for (int j = 0; j < number5; j++) {
					if ((mirror + j)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 2).asVector2f()) return;
				}
				for (int j = 0; j < number4; j++) {
					if ((block + j)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 2).asVector2f()) return;
				}
				(block + i)->push(SlidingBlock::Up);
				a = true;
				break;
			}
		}
		if (a) break;
		for (int i = 0; i < number5; i++) {
			if ((mirror + i)->getExist() == false) continue;
			if ((mirror + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 1).asVector2f()) {
				if ((mirror + i)->push(Mirror::Up, map, blockS, number, door, number2, machine, number3) == false) return;
				for (int j = 0; j < number5; j++) {
					if ((mirror + j)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 2).asVector2f()) return;
				}
				for (int j = 0; j < number4; j++) {
					if ((block + j)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y - 2).asVector2f()) return;
				}
				(mirror + i)->push(Mirror::Up);
				break;
			}
		}
		break;
	case Down:
		if (map.getType(convert.asNumber() + 18) == Square::Type::Wall) return;
		for (int i = 0; i < number; i++) {
			if ((blockS + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 1).asVector2f()) return;
		}
		for (int i = 0; i < number2; i++) {
			if ((door + i)->isOpen()) continue;
			if ((door + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 1).asVector2f()) return;
		}
		for (int i = 0; i < number3; i++) {
			if ((machine + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 1).asVector2f()) return;
		}
		for (int i = 0; i < number4; i++) {
			if ((block + i)->getExist() == false) continue;
			if ((block + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 1).asVector2f()) {
				if ((block + i)->push(SlidingBlock::Down, map, blockS, number, door, number2, machine, number3) == false) return;
				for (int j = 0; j < number5; j++) {
					if ((mirror + j)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 2).asVector2f()) return;
				}
				for (int j = 0; j < number4; j++) {
					if ((block + j)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 2).asVector2f()) return;
				}
				(block + i)->push(SlidingBlock::Down);
				a = true;
				break;
			}
		}
		if (a) break;
		for (int i = 0; i < number5; i++) {
			if ((mirror + i)->getExist() == false) continue;
			if ((mirror + i)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 1).asVector2f()) {
				if ((mirror + i)->push(Mirror::Down, map, blockS, number, door, number2, machine, number3) == false) return;
				for (int j = 0; j < number5; j++) {
					if ((mirror + j)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 2).asVector2f()) return;
				}
				for (int j = 0; j < number4; j++) {
					if ((block + j)->getPosition() == VectorConverter::convert(convert.asXY().x, convert.asXY().y + 2).asVector2f()) return;
				}
				(mirror + i)->push(Mirror::Down);
				break;
			}
		}
		break;
	case Left:
		if (map.getType(convert.asNumber() - 1) == Square::Type::Wall) return;
		for (int i = 0; i < number; i++) {
			if ((blockS + i)->getPosition() == VectorConverter::convert(convert.asXY().x - 1, convert.asXY().y).asVector2f()) return;
		}
		for (int i = 0; i < number2; i++) {
			if ((door + i)->isOpen()) continue;
			if ((door + i)->getPosition() == VectorConverter::convert(convert.asXY().x - 1, convert.asXY().y).asVector2f()) return;
		}
		for (int i = 0; i < number3; i++) {
			if ((machine + i)->getPosition() == VectorConverter::convert(convert.asXY().x - 1, convert.asXY().y).asVector2f()) return;
		}
		for (int i = 0; i < number4; i++) {
			if ((block + i)->getExist() == false) continue;
			if ((block + i)->getPosition() == VectorConverter::convert(convert.asXY().x - 1, convert.asXY().y).asVector2f()) {
				if ((block + i)->push(SlidingBlock::Left, map, blockS, number, door, number2, machine, number3) == false) return;
				for (int j = 0; j < number5; j++) {
					if ((mirror + j)->getPosition() == VectorConverter::convert(convert.asXY().x - 2, convert.asXY().y).asVector2f()) return;
				}
				for (int j = 0; j < number4; j++) {
					if ((block + j)->getPosition() == VectorConverter::convert(convert.asXY().x - 2, convert.asXY().y).asVector2f()) return;
				}
				(block + i)->push(SlidingBlock::Left);
				a = true;
				break;
			}
		}
		if (a) break;
		for (int i = 0; i < number5; i++) {
			if ((mirror + i)->getExist() == false) continue;
			if ((mirror + i)->getPosition() == VectorConverter::convert(convert.asXY().x - 1, convert.asXY().y).asVector2f()) {
				if ((mirror + i)->push(Mirror::Left, map, blockS, number, door, number2, machine, number3) == false) return;
				for (int j = 0; j < number5; j++) {
					if ((mirror + j)->getPosition() == VectorConverter::convert(convert.asXY().x - 2, convert.asXY().y).asVector2f()) return;
				}
				for (int j = 0; j < number4; j++) {
					if ((block + j)->getPosition() == VectorConverter::convert(convert.asXY().x - 2, convert.asXY().y).asVector2f()) return;
				}
				(mirror + i)->push(Mirror::Left);
				break;
			}
		}
		break;
	case Right:
		if (map.getType(convert.asNumber() + 1) == Square::Type::Wall) return;
		for (int i = 0; i < number; i++) {
			if ((blockS + i)->getPosition() == VectorConverter::convert(convert.asXY().x + 1, convert.asXY().y).asVector2f()) return;
		}
		for (int i = 0; i < number2; i++) {
			if ((door + i)->isOpen()) continue;
			if ((door + i)->getPosition() == VectorConverter::convert(convert.asXY().x + 1, convert.asXY().y).asVector2f()) return;
		}
		for (int i = 0; i < number3; i++) {
			if ((machine + i)->getPosition() == VectorConverter::convert(convert.asXY().x + 1, convert.asXY().y).asVector2f()) return;
		}
		for (int i = 0; i < number4; i++) {
			if ((block + i)->getExist() == false) continue;
			if ((block + i)->getPosition() == VectorConverter::convert(convert.asXY().x + 1, convert.asXY().y).asVector2f()) {
				if ((block + i)->push(SlidingBlock::Right, map, blockS, number, door, number2, machine, number3) == false) return;
				for (int j = 0; j < number5; j++) {
					if ((mirror + j)->getPosition() == VectorConverter::convert(convert.asXY().x + 2, convert.asXY().y).asVector2f()) return;
				}
				for (int j = 0; j < number4; j++) {
					if ((block + j)->getPosition() == VectorConverter::convert(convert.asXY().x + 2, convert.asXY().y).asVector2f()) return;
				}
				(block + i)->push(SlidingBlock::Right);
				a = true;
				break;
			}
		}
		if (a) break;
		for (int i = 0; i < number5; i++) {
			if ((mirror + i)->getExist() == false) continue;
			if ((mirror + i)->getPosition() == VectorConverter::convert(convert.asXY().x + 1, convert.asXY().y).asVector2f()) {
				if ((mirror + i)->push(Mirror::Right, map, blockS, number, door, number2, machine, number3) == false) return;
				for (int j = 0; j < number5; j++) {
					if ((mirror + j)->getPosition() == VectorConverter::convert(convert.asXY().x + 2, convert.asXY().y).asVector2f()) return;
				}
				for (int j = 0; j < number4; j++) {
					if ((block + j)->getPosition() == VectorConverter::convert(convert.asXY().x + 2, convert.asXY().y).asVector2f()) return;
				}
				(mirror + i)->push(Mirror::Right);
				break;
			}
		}
		break;
	}
	this->direction = direction;
	moveNr = 0;
}

void Player::run(Door* door, int number, ShootingBlock* block, int number2) {
	if (live && clockStage.getElapsedTime().asSeconds() >= 0.05) {
		clockStage.restart();
		setStage(++stage);
	}
	if (clockMove.getElapsedTime().asSeconds() >= 0.06 && moveNr < 10 && live) {
		clockMove.restart();
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
	else if (!live && moveNr != -1) {
		if (clockStage.getElapsedTime().asSeconds() >= 0.5) {
			setTextureRect(IntRect{ 0,0,1,1 });
			moveNr = -1;
		}
	}
	if (live) {
		for (int i = 0; i < number; i++) {
			if ((door + i)->isOpen() == false &&
				(door + i)->getPosition().x < getPosition().x + 80 && (door + i)->getPosition().x + 80 > getPosition().x &&
				(door + i)->getPosition().y < getPosition().y + 80 && (door + i)->getPosition().y + 80 > getPosition().y) {
				setLive(false);
			}
		}
		for (int i = 0; i < number2; i++) {
			ShootingBlock::Type type = (block + i)->getType();
			int nr(0);
			if (type < 4) nr = 1;
			else if (type < 10 && type > 3) nr = 2;
			else if (type < 14 && type > 9) nr = 3;
			else if (type == 14) nr = 4;
			for (int j = 0; j < nr; j++) {
				if (((block + i)->getMine() + j)->getExist()) {
					Vector2f pos = ((block + i)->getMine() + j)->getPosition();
					if (pos.x < getPosition().x + 80 && pos.x + 12 > getPosition().x &&
						pos.y < getPosition().y + 80 && pos.y + 12 > getPosition().y) {
						setLive(false);
					}
				}
			}
		}
	}
}

void Player::draw(RenderWindow& window) {
	window.draw(*this);
}

void Player::reset() {
	live = true;
	moveNr = 10;
	clockMove.restart();
	direction = Direction::None;
	setStage(0);
}