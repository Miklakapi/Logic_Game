#include "LaserMachines.hpp"

LaserMachines::LaserMachines(int number, string textureFile, string textureFile2){
	LaserMachine::setMachineTexture(textureFile);
	SimpleLaser::setLaserTexture(textureFile2);
	machine = new LaserMachine[number];
	this->number = number;
}

void LaserMachines::setPosition(int number, Vector2f position) {
	(machine + number)->setMachinePosition(position);
}

void LaserMachines::setSize(int number, Vector2f size) {
	(machine + number)->setMachineSize(size);
}

Laser* LaserMachines::getLaser(int number) {
	return 	(machine + number)->getLaser();
}

int LaserMachines::getLaserNr(int number) {
	return (machine + number)->getLaserNr();
}

void LaserMachines::setType(int number, LaserMachine::Type type) {
	(machine + number)->setType(type);
}

LaserMachine::Type LaserMachines::getType(int number) {
	return (machine + number)->getType();
}

void LaserMachines::setOn(int number, bool on) {
	(machine + number)->setOn(on);
}

bool LaserMachines::isOn(int number) {
	return (machine + number)->isOn();
}

LaserMachine* LaserMachines::getMachine() {
	return machine;
}

int LaserMachines::getNumber() {
	return number;
}

void LaserMachines::draw(RenderWindow& window) {
	for (int i = 0; i < number; i++) {
		(machine + i)->draw(window);
	}
}

void LaserMachines::run(Map& map, SlidingBlock* block, int number, Mirror* mirror, int number2, Door* door, int number3,
	ShootingBlock* blockS, int number4) {

}

void LaserMachines::reset(int number) {
	(machine + number)->reset();
}

void LaserMachines::reset() {
	for (int i = 0; i < number; i++) {
		(machine + i)->reset();
	}
}

LaserMachines::~LaserMachines(){
	delete [] machine;
}