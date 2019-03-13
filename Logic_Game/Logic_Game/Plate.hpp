#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "Player.hpp"
#include "SlidingBlock.hpp"
#include "Mirror.hpp"

using namespace sf;
using namespace std;

class Plate : public RectangleShape{

	RectangleShape background;

	bool pressed;

	static Texture* texture;

public:

	Plate();
	
	static void setPlateTexture(string textureFile = "Img/Plate.png");

	void setPlatePosition(Vector2f position);

	void setPlateSize(Vector2f size);

	bool isPressed();

	void setPressure(bool pressed);

	void draw(RenderWindow& window);

	void reset();
};