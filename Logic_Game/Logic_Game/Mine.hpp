#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

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

	void setMinePosition(Vector2f position);

	void setDirection(Direction direction);

	void reset();
};