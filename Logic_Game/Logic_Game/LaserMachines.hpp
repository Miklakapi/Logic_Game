#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "LaserMachine.hpp"
#include "VectorConverter.hpp"
#include "Map.hpp"
#include "SlidingBLock.hpp"
#include "Mirror.hpp"
#include "Door.hpp"
#include "ShootingBlock.hpp"

using namespace sf;
using namespace std;

class LaserMachines{

	LaserMachine* machine;

	int number;

public:

	LaserMachines(int number, string textureFile = "Img/LaserMachine.png", string textureFile2 = "Img/Laser.png");

	void setPosition(int number, Vector2f position);

	void setSize(int number, Vector2f size);

	Laser* getLaser(int number);

	int getLaserNr(int number);

	void setType(int number, LaserMachine::Type type, Map& map, ShootingBlock* blocks, int number2);

	LaserMachine::Type getType(int number);

	void setOn(int number, bool on);

	bool isOn(int number);

	LaserMachine* getMachine();

	int getNumber();

	void draw(RenderWindow& window);

	void run(SlidingBlock* block, int number, Mirror* mirror, int number2, Door* door, int number3);

	void reset(int number);

	void reset();

	~LaserMachines();
};

