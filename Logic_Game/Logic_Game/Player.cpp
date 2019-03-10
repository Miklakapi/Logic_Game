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

bool Player::movePlayer(Direction direction, Map& map, SlidingBlock* block, int number, Mirror* mirror, int number2, Door* door, int number3,
	ShootingBlock* blockS, int number4, LaserMachine* machine, int number5) {

	if (!live || moveNr != 10) return false;
	if (direction == Player::Direction::None) return false;

	VectorConverter vec(getPosition());
	switch (direction) {
	case Player::Up:
		vec = vec.convert(vec.asXY().x, vec.asXY().y - 1);
		break;
	case Player::Down:
		vec = vec.convert(vec.asXY().x, vec.asXY().y + 1);
		break;
	case Player::Left:
		vec = vec.convert(vec.asXY().x - 1, vec.asXY().y);
		break;
	case Player::Right:
		vec = vec.convert(vec.asXY().x + 1, vec.asXY().y);
		break;
	}

	if (map.getType(vec.asNumber()) == Square::Type::Wall) return false;

	for (int i = 0; i < number; i++) {
		if ((block + i)->getExist() && (block + i)->getPosition() == vec.asVector2f()) return true;
	}

	for (int i = 0; i < number2; i++) {
		if ((mirror + i)->getExist() && (mirror + i)->getPosition() == vec.asVector2f()) return true;
	}
	
	for (int i = 0; i < number3; i++) {
		if (!(door + i)->isOpen() && (door + i)->getPosition() == vec.asVector2f()) return false;
	}

	for (int i = 0; i < number4; i++) {
		if ((blockS + i)->getPosition() == vec.asVector2f()) return false;
	}

	for (int i = 0; i < number5; i++) {
		if ((machine + i)->getPosition() == vec.asVector2f()) return false;
	}

	this->direction = direction;
	moveNr = 0;
	return false;
}

void Player::movePlayer(Player::Direction direction) {
	if (!live || moveNr != 10) return;
	if (direction == Player::Direction::None) return;
	this->direction = direction;
	moveNr = 0;
}

void Player::run(ShootingBlock* block, int number) {
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

Player::~Player() {
	delete [] rect;
}