#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class LaserReceiver: public RectangleShape{

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
		D1
	};

private:

	bool on;

	Type type;

	static Texture* texture;

	static IntRect* rect;

public:

	LaserReceiver();

	static void setReceiverTexture(string textureFile = "Img/LaserReceiver.png");

	Type getType();

	void setType(Type type);

	bool getOn();

	void setOn(bool on);

	void draw(RenderWindow& window);

	void reset();
};