#include "Mirror.hpp"

Texture* Mirror::texture;

Mirror::Mirror(){
	setSize(Vector2f{ 80,80 });
	setTexture(texture);
	setPosition(Vector2f{ 0,0 });
	reset();
}

void Mirror::setBlockTexture(string textureFile) {
	static int a = 0;
	if (a == 0) {
		texture = new Texture;
		a++;
	}
	texture->loadFromFile(textureFile);
}

void Mirror::destroy() {

}

bool Mirror::getExist() {
	return exist;
}

bool Mirror::push(Direction direction, Map& map, ShootingBlock* blockS, int number, Door* door, int number2,
	LaserMachine* machine, int number3){
	return false;
}

void Mirror::push(Direction direction) {

}

void Mirror::run(Door* door, int number) {

}

void Mirror::draw(RenderWindow& window) {
	window.draw(*this);
}

void Mirror::reset() {
	exist = true;
	moveNr = 10;
	clock.restart();
	direction = Direction::None;
}