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

void Player::movePlayer(Direction direction) {
	if (moveNr != 10) return;
	this->direction = direction;
	if (direction == Direction::None) return;
	moveNr = 0;
}

void Player::run() {
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