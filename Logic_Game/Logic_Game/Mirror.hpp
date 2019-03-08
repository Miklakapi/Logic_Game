#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "VectorConverter.hpp"
#include "Map.hpp"
#include "Door.hpp"
#include "ShootingBlock.hpp"
#include "LaserMachine.hpp"

using namespace sf;
using namespace std;

class Mirror : public RectangleShape{

public:

	enum Direction {
		Up,
		Down,
		Left,
		Right,
		None
	};

	enum Type {
		A1,
		A2,
		A3,
		A4,
		B1,
		B2,
		B3,
		B4,
		C1,
	};

private:

	Laser* laser;

	int laserNr;

	static Texture* texture;

	static IntRect* rect;

	int moveNr;

	Clock clock;

	Direction direction;

	Type type;

	int rectNr;

	bool exist;

	bool on;

	bool newPosition, positionChg;

public:

	Mirror();
	
	static void setBlockTexture(string textureFile = "Img/Mirror.png");

	Laser* getLaser();

	int getLaserNr();

	Type getType();

	void setType(Type type);

	bool isOnNewPosition();

	void setOnNewPosition(bool newPos);

	void setOn(bool on);

	bool isOn();

	int getMoveNumber();

	void destroy();

	bool getExist();

	void push(Direction direction);

	void run();

	void draw(RenderWindow& window);

	void reset();
};