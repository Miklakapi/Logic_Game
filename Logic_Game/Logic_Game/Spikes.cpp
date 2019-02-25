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

int Spikes::getStage() {
	return stage;
}

void Spikes::setOn(bool on) {
	if (!on && this->on != on) direction = Direction::Down;
	else if (on && this->on != on) clock.restart();
	this->on = on;
}

bool Spikes::isOn() {
	return on;
}

void Spikes::run() {
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