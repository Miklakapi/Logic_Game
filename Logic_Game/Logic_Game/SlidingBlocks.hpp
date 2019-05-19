#pragma once

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <string>

#include "VectorConverter.hpp"
#include "SlidingBlock.hpp"
#include "Map.hpp"
#include "Mirror.hpp"
#include "Door.hpp"
#include "ShootingBlock.hpp"
#include "LaserMachine.hpp"
#include "LaserReceiver.hpp"

using namespace sf;
using namespace std;

class SlidingBlocks{

	SlidingBlock* block;

	int number;

public:

	SlidingBlocks(int number, string textureFile = "Img/SlidingBlock.png");

	void setBlockPosition(int number, Vector2f position);

	void setBlockSize(int number, Vector2f size);

	void destroy(int number);

	bool getExist(int number);

	bool push(int number, SlidingBlock::Direction direction, Map& map, Mirror* mirror, int number2, Door* door, int number3,
		ShootingBlock* blockS, int number4, LaserMachine* machine, int number5, LaserReceiver* receiver, int number6);

	SlidingBlock* getBlock();

	int getNumber();

	void run();

	void draw(RenderWindow& window);

	void reset(int number);

	void reset();

	~SlidingBlocks();
};