#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

enum Direction {
	Up,
	Down,
	Left,
	Right,
	None
};

class SlidingBlock : public RectangleShape{

	static Texture* texture;

	Direction direction;

	Clock clock;

	int moveNr;

	bool exist;

public:

	SlidingBlock(Vector2f position = Vector2f{ 0,0 }, string textureFile = "Img/SlidingBlock.png");

	void destroy();

	void push(Direction direction);

	bool getExist();

	void run();

	void draw(RenderWindow& window);

	void reset();
};

