#include "Spikes.hpp"

Texture* Spikes::texture;

IntRect* Spikes::rect;

Spikes::Spikes(Vector2f position, string textureFile) {
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		texture->loadFromFile(textureFile);
		rect = new IntRect[5];
		*(rect + 0) = IntRect{0,0,80,80};
		*(rect + 1) = IntRect{80,0,80,80};
		*(rect + 2) = IntRect{160,0,80,80};
		*(rect + 3) = IntRect{0,80,80,80};
		*(rect + 4) = IntRect{80,80,80,80};
		a++;
	}
	setSize(Vector2f{ 80,80 });
	setTexture(texture);
	setPosition(position);
	reset();
}

bool Spikes::getDmg() {
	return dmg;
}

void Spikes::draw(RenderWindow& window) {
	if (lock && ) {

	}
	else if(!lock){
		if (direction == Direction::Up) {
			if (stage > 0 && stage < 4 && clock.getElapsedTime().asSeconds() >= 0.08) {
				clock.restart();
				stage++;
				setTextureRect(*(rect + stage));
			}
			else if (clock.getElapsedTime().asSeconds() >= 2.5 && stage == 0) {
				clock.restart();
				stage++;
				setTextureRect(*(rect + stage));
				dmg = true;
			}
			else if (stage == 4 && clock.getElapsedTime().asSeconds() >= 0.5) {
				direction = Direction::Down;
			}
		}
		else if (direction == Direction::Down) {
			if (stage > 0 && stage < 4 && clock.getElapsedTime().asSeconds() >= 0.2) {
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
				dmg = false;
			}
		}
	}
	window.draw(*this);
}

void Spikes::reset() {
	setTextureRect(*rect);
	dmg = false;
	stage = 0;
	direction = Direction::Up;
	clock.restart();
}