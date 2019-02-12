#include "Door.hpp"

Door::Door(Vector2f position, Color color, string textureFile) {

}

bool Door::isOpen() {
	return open;
}

void Door::draw(RenderWindow& window) {
	window.draw(background);
	window.draw(*this);
}