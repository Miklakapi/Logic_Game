#include "Mirror.hpp"

Texture* Mirror::texture;

IntRect* Mirror::rect;

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
		rect = new IntRect[36];
		//------
		*(rect + 0) = { 0,0,80,80 };
		*(rect + 1) = { 80,0,80,80 };
		*(rect + 2) = { 160,0,80,80 };
		*(rect + 3) = { 240,0,80,80 };
		//
		*(rect + 4) = { 0,80,80,80 };
		*(rect + 5) = { 80,80,80,80 };
		*(rect + 6) = { 160,80,80,80 };
		*(rect + 7) = { 240,80,80,80 };
		//
		*(rect + 8) = { 0,160,80,80 };
		//------
		*(rect + 9) = { 320,0,80,80 };
		*(rect + 10) = { 400,0,80,80 };
		*(rect + 11) = { 480,0,80,80 };
		*(rect + 12) = { 560,0,80,80 };
		//
		*(rect + 13) = { 320,80,80,80 };
		*(rect + 14) = { 400,80,80,80 };
		*(rect + 15) = { 480,80,80,80 };
		*(rect + 16) = { 560,80,80,80 };
		//
		*(rect + 17) = { 320,160,80,80 };
		//------
		*(rect + 18) = { 0,240,80,80 };
		*(rect + 19) = { 80,240,80,80 };
		*(rect + 20) = { 160,240,80,80 };
		*(rect + 21) = { 240,240,80,80 };
		//
		*(rect + 22) = { 0,320,80,80 };
		*(rect + 23) = { 80,320,80,80 };
		*(rect + 24) = { 160,320,80,80 };
		*(rect + 25) = { 240,320,80,80 };
		//
		*(rect + 26) = { 0,400,80,80 };
		//------
		*(rect + 27) = { 320,240,80,80 };
		*(rect + 28) = { 400,240,80,80 };
		*(rect + 29) = { 480,240,80,80 };
		*(rect + 30) = { 560,240,80,80 };
		//
		*(rect + 31) = { 320,320,80,80 };
		*(rect + 32) = { 400,320,80,80 };
		*(rect + 33) = { 480,320,80,80 };
		*(rect + 34) = { 560,320,80,80 };
		//
		*(rect + 35) = { 320,400,80,80 };
		//------
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