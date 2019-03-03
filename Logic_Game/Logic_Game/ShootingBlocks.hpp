#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "VectorConverter.hpp"
#include "ShootingBlock.hpp"
#include "Map.hpp"
#include "Door.hpp"
#include "SlidingBLocks.hpp"
#include "Mirror.hpp"
#include "LaserMachine.hpp"

using namespace sf;
using namespace std;

class ShootingBlocks{

	ShootingBlock* block;

	int number;

public:

	ShootingBlocks(int number, string textureFile = "Img/ShootingBLock.png", string textureFIle2 = "Img/Mine.png");

	void setPosition(int number, Vector2f position);

	void setSize(int number, Vector2f size);

	void setDelay(int number, float delay);

	int getDelay(int number);

	void setType(int number, ShootingBlock::Type type);

	ShootingBlock::Type getType(int number);

	int getMinerNr(int number);

	void setOn(int number, bool on);

	bool isOn(int number);

	ShootingBlock* getBlock();

	int getNumber();

	void draw(RenderWindow& window);

	void run(Map& map, Door* door, int number, SlidingBlock* block, int number2, Mirror* mirror, int number3, LaserMachine* machine, int number4);

	void reset(int number);

	void reset();

	~ShootingBlocks();
};

