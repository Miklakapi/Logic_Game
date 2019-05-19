#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <string>

#include "VectorConverter.hpp"
#include "LaserReceiver.hpp"
#include "Mirror.hpp"
#include "LaserMachine.hpp"

using namespace sf;
using namespace std;

class LaserReceivers{

	LaserReceiver* receiver;

	int number;

public:
	
	LaserReceivers(int number, string textureFile = "Img/LaserReceiver.png");

	void setPosition(int number, Vector2f position);

	void setSize(int number, Vector2f size);

	LaserReceiver::Type getType(int number);

	void setType(int number, LaserReceiver::Type type);

	bool getOn(int number);

	void setOn(int number, bool on);

	LaserReceiver* getReceiver();

	int getNumber();

	void draw(RenderWindow& window);

	void run(Mirror* mirror, int number, LaserMachine* machine, int number2);

	void reset(int number);

	void reset();

	~LaserReceivers();
};