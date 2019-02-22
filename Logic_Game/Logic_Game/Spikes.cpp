#include "Spikes.hpp"

Texture* Spikes::texture;

IntRect* Spikes::rect;

Spikes::Spikes() {
	setTexture(texture);
	setSize(Vector2f{ 80,80 });
	setPosition(Vector2f{ 0,0 });
	reset();
}

void Spikes::loadSpikesTexture(string textureFile) {
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		rect = new IntRect[5];
		*(rect + 0) = IntRect{ 0,0,80,80 };
		*(rect + 1) = IntRect{ 80,0,80,80 };
		*(rect + 2) = IntRect{ 160,0,80,80 };
		*(rect + 3) = IntRect{ 0,80,80,80 };
		*(rect + 4) = IntRect{ 80,80,80,80 };
		a++;
	}
	texture->loadFromFile(textureFile);
}

void Spikes::setOn(bool on) {
	if (!on && this->on != on) direction = Direction::Down;
	else if (on && this->on != on) clock.restart();
	this->on = on;
}

bool Spikes::isOn() {
	return on;
}

void Spikes::run(Player& player, SlidingBlock* block, int number, Mirror* mirror, int number2) {
	if (direction == Direction::Up && on) {
		if (stage > 0 && stage < 4 && clock.getElapsedTime().asSeconds() >= 0.08) {
			clock.restart();
			stage++;
			setTextureRect(*(rect + stage));
		}
		else if (clock.getElapsedTime().asSeconds() >= 2.5 && stage == 0) {
			clock.restart();
			stage++;
			setTextureRect(*(rect + stage));
		}
		else if (stage == 4 && clock.getElapsedTime().asSeconds() >= 0.5) {
			direction = Direction::Down;
		}
	}
	else if (direction == Direction::Down) {
		if (stage > 0 && stage < 4 && clock.getElapsedTime().asSeconds() >= 0.15) {
			clock.restart();
			stage--;
			setTextureRect(*(rect + stage));
		}
		else if (stage == 4) {
			clock.restart();
			stage--;
			setTextureRect(*(rect + stage));
		}
		else if (stage == 0) {
			direction = Direction::Up;
		}
	}
	if (stage == 0) return;
	if (player.getPosition().x < getPosition().x + 80 && player.getPosition().x + 80 > getPosition().x &&
		player.getPosition().y < getPosition().y + 80 && player.getPosition().y + 80 > getPosition().y) {
		player.setLive(false);
	}
	for (int i = 0; i < number; i++) {
		if (!(block + i)->getExist()) continue;
		if ((block + i)->getPosition().x < getPosition().x + 80 && (block + i)->getPosition().x + 80 > getPosition().x &&
			(block + i)->getPosition().y < getPosition().y + 80 && (block + i)->getPosition().y + 80 > getPosition().y) {
			(block + i)->destroy();
		}
	}
	for (int i = 0; i < number2; i++) {
		if (!(mirror + i)->getExist()) continue;
		if ((mirror + i)->getPosition().x < getPosition().x + 80 && (mirror + i)->getPosition().x + 80 > getPosition().x &&
			(mirror + i)->getPosition().y < getPosition().y + 80 && (mirror + i)->getPosition().y + 80 > getPosition().y) {
			(mirror + i)->destroy();
		}
	}
}

void Spikes::draw(RenderWindow& window) {
	window.draw(*this);
}

void Spikes::reset() {
	setTextureRect(*rect);
	on = false;
	stage = 0;
	direction = Direction::Up;
	clock.restart();
}