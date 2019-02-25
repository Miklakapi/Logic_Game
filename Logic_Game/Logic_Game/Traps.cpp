#include "Traps.hpp"

Traps::Traps(int number, string textureFile){
	Spikes::loadSpikesTexture(textureFile);
	this->number = number;
	spikes = new Spikes[number];
}

void Traps::setSpikesPosition(int number, Vector2f position) {
	(spikes + number)->setPosition(position);
}

void Traps::setSpikesSize(int number, Vector2f size) {
	(spikes + number)->setSize(size);
}

void Traps::setOn(int number, bool on) {
	(spikes + number)->setOn(on);
}

bool Traps::isOn(int number) {
	return (spikes + number)->isOn();
}

Spikes* Traps::getSpikes() {
	return spikes;
}

int Traps::getNumber() {
	return number;
}

void Traps::run(Player& player, SlidingBlock* block, int number, Mirror* mirror, int number2) {
	for (int i = 0; i < this->number; i++) {
		(spikes + i)->run();
		if ((spikes + i)->getStage() == 0) continue;
		if (player.getLive() &&
			player.getPosition().x < (spikes + i)->getPosition().x + 80 && player.getPosition().x + 80 >(spikes + i)->getPosition().x &&
			player.getPosition().y < (spikes + i)->getPosition().y + 80 && player.getPosition().y + 80 >(spikes + i)->getPosition().y) {
			player.setLive(false);
		}
		for (int j = 0; j < number; j++) {
			if (!(block + j)->getExist()) continue;
			if ((block + j)->getPosition().x < (spikes + i)->getPosition().x + 80 && (block + j)->getPosition().x + 80 >(spikes + i)->getPosition().x &&
				(block + j)->getPosition().y < (spikes + i)->getPosition().y + 80 && (block + j)->getPosition().y + 80 >(spikes + i)->getPosition().y) {
				(block + j)->destroy();
			}
		}
		for (int j = 0; j < number2; j++) {
			if (!(mirror + j)->getExist()) continue;
			if ((mirror + j)->getPosition().x < (spikes + i)->getPosition().x + 80 && (mirror + j)->getPosition().x + 80 >(spikes + i)->getPosition().x &&
				(mirror + j)->getPosition().y < (spikes + i)->getPosition().y + 80 && (mirror + j)->getPosition().y + 80 >(spikes + i)->getPosition().y) {
				(mirror + j)->destroy();
			}
		}
	}
}

void Traps::draw(RenderWindow& window) {
	for (int i = 0; i < number; i++) {
		(spikes + i)->draw(window);
	}
}

void Traps::reset(int number) {
	(spikes + number)->reset();
}

void Traps::reset() {
	for (int i = 0; i < number; i++) {
		(spikes + i)->reset();
	}
}

Traps::~Traps(){
	delete [] spikes;
}