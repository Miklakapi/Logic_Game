#include "Mirrors.hpp"

Mirrors::Mirrors(int number, string textureFile){
	Mirror::setBlockTexture(textureFile);
	mirror = new Mirror[number];
	this->number = number;
}











/*bool push(int number, SlidingBlock::Direction direction, Map& map,
	Door* door, int number3, ShootingBlock* blockS, int number4,
	LaserMachine* machine, int number5);*/

Mirror* Mirrors::getMirror() {
	return mirror;
}

int Mirrors::getNumber() {
	return number;
}

void Mirrors::draw(RenderWindow& window) {
	for (int i = 0; i < number; i++) {
		(mirror + i)->draw(window);
	}
}

//void Mirrors::run();

void Mirrors::reset(int number) {
	(mirror + number)->reset();
}

void Mirrors::reset() {
	for (int i = 0; i < number; i++) {
		(mirror + i)->reset();
	}
}

Mirrors::~Mirrors(){
	delete [] mirror;
}