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

class SlidingBlock : public RectangleShape{

public:

	enum Direction {
		Up,
		Down,
		Left,
		Right,
		None
	};

private:

	static Texture* texture;

	int moveNr;

	Clock clock;

	Direction direction;

	bool exist;

public:

	SlidingBlock();

	static void setBlockTexture(string textureFile = "Img/SlidingBlock.png");

	int getMoveNumber();

	void destroy();

	bool getExist();

	void push(Direction direction);

	void run();

	void draw(RenderWindow& window);

	void reset();
};

