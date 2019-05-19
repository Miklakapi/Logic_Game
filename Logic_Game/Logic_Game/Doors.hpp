#pragma once

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <string>

#include "Door.hpp"
#include "Player.hpp"
#include "SlidingBlock.hpp"
#include "Mirror.hpp"

using namespace sf;
using namespace std;

class Doors{

	Door* door;

	int number;

public:
	
	Doors(int number, string textureFile = "Img/Door.png");
	
	void setDoorPosition(int number, Vector2f position);

	void setDoorSize(int number, Vector2f size);

	bool isOpen(int number);

	void setOpen(int number, bool open, Player& player, SlidingBlock* block, int number2, Mirror* mirror, int number3);

	Door* getDoor();

	int getNumber();

	void draw(RenderWindow& window);

	void reset(int number);

	void reset();

	~Doors();
};