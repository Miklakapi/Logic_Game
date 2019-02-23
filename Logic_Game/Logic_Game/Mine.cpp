#include "Mine.hpp"

Mine::Mine(){

}

void Mine::setMinePosition(Vector2f position) {
	startPosition = position;
}

void Mine::setDirection(Direction direction) {
	this->direction = direction;
}