#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "VectorConverter.hpp"
#include "Map.hpp"
#include "Door.hpp"
#include "ShootingBlock.hpp"
#include "SlidingBlock.hpp"
#include "LaserMachine.hpp"
#include "Mirror.hpp"


using namespace sf;
using namespace std;

class Player : public RectangleShape{

public:
	
	enum Direction {
		Up,
		Down,
		Left,
		Right,
		None
	};

private:

	Texture texture;

	IntRect* rect;

	int stage;

	int moveNr;

	Clock clockStage;

	Clock clockMove;
	
	Player::Direction direction;

	bool live;

	void setStage(int stage);

public:

	Player(Vector2f position = Vector2f{ 0,0 }, string textureFile = "Img/Player.png");

	void setPlayerTexture(string textureFile);

	void setLive(bool live);

	bool getLive();

	void movePlayer(Direction direction, Map& map, ShootingBlock* blockS, int number, Door* door, int number2,
		LaserMachine* machine, int number3, SlidingBlock* block, int number4, Mirror* mirror, int number5);

	void run();

	void draw(RenderWindow& window);

	void reset();
};