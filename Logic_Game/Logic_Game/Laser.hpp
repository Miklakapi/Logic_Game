#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "VectorConverter.hpp"

using namespace sf;
using namespace std;

class SimpleLaser : public RectangleShape{

public:

	enum Direction {
		Horizontal,
		Vertical
	};

private:

	static Texture* texture;

	static IntRect* rect;

	bool exist;

	Direction direction;

public:
	
	SimpleLaser();
	
	static void setLaserTexture(string textureFile = "Img/Laser.png");

	void setDirection(Direction direction);

	Direction getDirection();

	void setExist(bool exist);

	bool getExist();

	void draw(RenderWindow& window);

	void reset();
};

////////////////////////////////////////////
////////////////////////////////////////////

class Laser{

public:

	enum Direction {
		Up,
		Down,
		Left,
		Right
	};

private:

	SimpleLaser* laser;

	int laserNr;

	Direction direction;

public:

	Laser();

	void setPosition(Vector2f position, Direction direction, int laserNr);

	SimpleLaser* getSimpleLaser();

	int getLaserNr();

	Direction getDirection();

	void draw(RenderWindow& window);

	void on();

	void off();

	void reset();
};