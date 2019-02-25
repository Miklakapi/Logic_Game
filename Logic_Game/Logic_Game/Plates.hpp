#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "Plate.hpp"
#include "Player.hpp"
#include "SlidingBlock.hpp"
#include "Mirror.hpp"

using namespace sf;
using namespace std;

class Plates{

	Plate* plate;

	int number;

public:

	Plates(int number, string textureFile = "Img/Plate.png");

	void setPlatePosition(int number, Vector2f position);

	void setPlateSize(int number, Vector2f size);

	bool isPressed(int number);

	void setPressure(int number, bool pressed);

	void draw(RenderWindow& window);

	void run(Player& player, SlidingBlock* block, int number, Mirror* mirror, int number2);

	void reset(int number);

	void reset();
	
	~Plates();
};