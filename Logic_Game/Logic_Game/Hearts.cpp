#include "Hearts.hpp"

Hearts::Hearts(Vector2f position, string textureFile) {
	setHeartsTexture(textureFile);
	heart = new RectangleShape[3];
	for (int i = 0; i < 3; i++) {
		(heart + i)->setSize(Vector2f{ 50,50 });
		(heart + i)->setTexture(texture);
	}
	setPosition(position);
	setHealth(3);
}

void Hearts::setHeartsTexture(string textureFile) {
	static int n = 0;
	if (n == 0) {
		texture = new Texture[1];
		n++;
	}
	texture->loadFromFile(textureFile);
}

void Hearts::setPosition(Vector2f position) {
	(heart + 0)->setPosition(position);
	(heart + 1)->setPosition(position + Vector2f{ 55,0 });
	(heart + 2)->setPosition(position + Vector2f{ 110,0 });
}

void Hearts::setHealth(int health) {
	this->health = health;
	switch (health) {
	case 0:
		(heart + 0)->setTextureRect(IntRect{ 0,0,1,1 });
		(heart + 1)->setTextureRect(IntRect{ 0,0,1,1 });
		(heart + 2)->setTextureRect(IntRect{ 0,0,1,1 });
		break;
	case 1:
		(heart + 0)->setTextureRect(IntRect{ 0,0,50,50 });
		(heart + 1)->setTextureRect(IntRect{ 0,0,1,1 });
		(heart + 2)->setTextureRect(IntRect{ 0,0,1,1 });
		break;
	case 2:
		(heart + 0)->setTextureRect(IntRect{ 0,0,50,50 });
		(heart + 1)->setTextureRect(IntRect{ 0,0,50,50 });
		(heart + 2)->setTextureRect(IntRect{ 0,0,1,1 });
		break;
	case 3:
		(heart + 0)->setTextureRect(IntRect{ 0,0,50,50 });
		(heart + 1)->setTextureRect(IntRect{ 0,0,50,50 });
		(heart + 2)->setTextureRect(IntRect{ 0,0,50,50 });
		break;
	default:
		this->health = 3;
		(heart + 0)->setTextureRect(IntRect{ 0,0,50,50 });
		(heart + 1)->setTextureRect(IntRect{ 0,0,50,50 });
		(heart + 2)->setTextureRect(IntRect{ 0,0,50,50 });
		break;
	}
}

int Hearts::getHealth() {
	return health;
}

void Hearts::draw(RenderWindow& window) {
	for (int i = 0; i < 3; i++) {
		window.draw(*(heart + i));
	}
}

void Hearts::reset() {
	setHealth(3);
}

Hearts::~Hearts() {
	delete [] heart;
	delete [] texture;
}