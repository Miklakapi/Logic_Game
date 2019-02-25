#include "Map.hpp"

Map::Map(){
	square = new Square[198];
	int nr(0);
	for (int y = 0; y < 11; y++) {
		for (int x = 0; x < 18; x++) {
			(square + nr)->setPosition(Vector2f{ float(80 * x),float(80 * y) });
			nr++;
		}
	}
	reset();
	reader.renderLV(1, square);
}

void Map::setType(int number, Square::Type type) {
	(square + number)->setType(type);
}

Square::Type Map::getType(int nr) {
	return (square + nr)->getType();
}

void Map::loadLV(int lv) {
	reader.loadLV(lv);
}

void Map::renderLV() {
	reader.renderLV(square);
}

void Map::renderLV(int lv) {
	reader.renderLV(lv, square);
}

int Map::getActualLV() {
	return reader.getActualLV();
}

void Map::draw(RenderWindow& window) {
	for (int i = 0; i < 198; i++) {
		window.draw(*(square + i));
	}
}

void Map::reset() {
	for (int i = 0; i < 198; i++) {
		(square + i)->reset();
	}
}

Map::~Map(){
	delete [] square;
}
