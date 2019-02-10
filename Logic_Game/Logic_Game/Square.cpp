#include "Square.hpp"

Texture* Square::texture;

Square::Square() {
	setSize(Vector2f{ 80,80 });
	setType(Type::Empty);
	setTexture(texture);
}

void Square::setTextureFile(string textureFile) {
	static int a = 0;
	if (a == 0) {
		texture = new Texture();
		a++;
	}
	texture->loadFromFile(textureFile);
}

void Square::setType(Type type) {
	this->type = type;
	switch (type) {
	case Type::Wall:
		setTextureRect(IntRect{ 0,0,80,80 });
		break;
	case Type::Empty:
		setTextureRect(IntRect{ 80,0,80,80 });
		break;
	}
}

Type Square::getType() {
	return type;
}

void Square::reset() {
	setType(Type::Empty);
}