#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "VectorConverter.hpp"

using namespace sf;
using namespace std;

class SimpleLaser : public RectangleShape{

	static Texture* texture;

	static IntRect* rect;

	bool exist;

public:
	
	SimpleLaser();
	
	static void setLaserTexture(string textureFile = "Img/Laser.png");

	void setExist(bool exist);

	bool getExist();

	void draw(RenderWindow& window);

	void reset();
};

////////////////////////////////////////////
////////////////////////////////////////////

class Laser {

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

	int actualLaser;

	Direction direction;

public:

	Laser();

	void setPosition(Vector2f position, Direction direction, int laserNr);

	void draw(RenderWindow& window);

	void run(bool on, int nr);

	void reset();
};