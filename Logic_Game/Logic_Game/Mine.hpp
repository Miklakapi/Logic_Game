#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Mine : public RectangleShape{

public:

	enum Direction {
		Up,
		Down,
		Left,
		Right
	};

private:

	static Texture* texture;

	Vector2f startPosition;

	int moveNr;

	Direction direction;

	Clock clock;

	bool exist;

public:
	
	Mine();
	
	static void setMineTexture(string textureFile = "Img/Mine.png");

	void setStartPosition(Vector2f position);

	Vector2f getStartPosition();

	void setDirection(Direction direction);

	Direction getDirection();

	void setExist(bool exist);

	bool getExist();

	void draw(RenderWindow& window);

	void run(bool on);

	void reset();
};