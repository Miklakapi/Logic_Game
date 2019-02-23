#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "VectorConverter.hpp"
#include "Mine.hpp"
#include "Map.hpp"
#include "Door.hpp"

using namespace sf;
using namespace std;

class ShootingBlock : public RectangleShape{

public:

	enum Type {
		A1,
		A2,
		A3,
		A4,
		B1,
		B2,
		B3,
		B4,
		B5,
		B6,
		C1,
		C2,
		C3,
		C4,
		D1,
	};

private:

	Mine* mine;

	static Texture* texture;

	static IntRect* rect;

	Type type;

	RectangleShape background;

	bool on;

	int delay;

	Clock clock;

public:
	
	ShootingBlock();

	static void setBlockTexture(string textureFile = "Img/ShootingBlock.png");

	void setBlockPosition(Vector2f position);

	void setBlockSize(Vector2f size);

	void setDelay(int delay);

	int getDelay();

	void setType(Type type);

	Type getType();

	void setOn(bool on);

	bool isOn();

	void draw(RenderWindow& window);

	void run(Map& map, Door* door, int number);

	void reset();
};

