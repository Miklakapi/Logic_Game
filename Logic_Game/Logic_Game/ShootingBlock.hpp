#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "Mine.hpp"

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

	int mineNr;

	static Texture* texture;

	static IntRect* rect;

	Type type;

	RectangleShape background;

	bool on;

	float delay;

	Clock* clock;

public:
	
	ShootingBlock();

	static void setBlockTexture(string textureFile = "Img/ShootingBlock.png");

	void setBlockPosition(Vector2f position);

	void setBlockSize(Vector2f size);

	void setDelay(float delay);

	int getDelay();

	void setType(Type type);

	Type getType();

	int getMinerNr();

	void setOn(bool on);

	bool isOn();

	Mine* getMine();

	void draw(RenderWindow& window);

	void run();

	void reset();

	~ShootingBlock();
};

