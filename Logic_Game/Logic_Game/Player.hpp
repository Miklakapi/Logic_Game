#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "VectorConverter.hpp"
#include "Map.hpp"
#include "Door.hpp"
#include "SlidingBlock.hpp"
#include "Mirror.hpp"
#include "ShootingBlock.hpp"
#include "LaserMachine.hpp"

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

	bool movePlayer(Direction direction, Map& map, SlidingBlock* block, int number, Mirror* mirror, int number2, Door* door, int number3,
		ShootingBlock* blockS, int number4, LaserMachine* machine, int number5);

	void run(ShootingBlock* block, int number);

	void draw(RenderWindow& window);

	void reset();
};