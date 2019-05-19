#pragma once

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <string>

#include "Laser.hpp"

using namespace sf;
using namespace std;

class LaserMachine : public RectangleShape{

public:

	enum Type {
		A1,
		A2,
		A3,
		A4,
		B1,
		B2,
		B3,
		B4,
		B5,
		B6,
		C1,
		C2,
		C3,
		C4,
		D1,
	};

private:

	Laser* laser;

	int laserNr;

	static Texture* texture;

	static IntRect* rect;

	Type type;

	RectangleShape background;

	bool on;

public:

	LaserMachine();

	static void setMachineTexture(string textureFile = "Img/LaserMachine.png");

	void setMachinePosition(Vector2f position);

	void setMachineSize(Vector2f size);

	Laser* getLaser();

	int getLaserNr();

	void setType(Type type);

	Type getType();

	void setOn(bool on);

	bool isOn();

	void draw(RenderWindow& window);

	void reset();

	~LaserMachine();
};