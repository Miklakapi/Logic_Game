#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Mirror.hpp"
#include "Map.hpp"
#include "SlidingBlock.hpp"
#include "Door.hpp"
#include "ShootingBlock.hpp"
#include "LaserMachine.hpp"

using namespace sf;
using namespace std;

class Mirrors{

	Mirror* mirror;

	int number;

public:
	
	Mirrors(int number, string textureFile = "Img/Mirror.png");

	void setPosition(int number, Vector2f position);

	void setSize(int number, Vector2f size);

	Laser* getLaser(int number);

	int getLaserNr(int number);

	void setType(int number, Mirror::Type type, Map& map, 
		ShootingBlock* blocks, int number2, LaserMachine machine, int number3);

	Mirror::Type getType(int number);

	void setOn(int number, bool on);

	bool isOn(int number);

	int getMoveNumber(int number);

	void destroy(int number);

	bool getExist(int number);

	bool push(int number, SlidingBlock::Direction direction, Map& map, 
		Door* door, int number3, ShootingBlock* blockS, int number4,
		LaserMachine* machine, int number5);

	Mirror* getMirror();

	int getNumber();

	void draw(RenderWindow& window);

	void run();

	void reset(int number);

	void reset();

	~Mirrors();
};