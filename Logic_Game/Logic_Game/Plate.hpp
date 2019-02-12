#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

class Plate : public RectangleShape{

	RectangleShape background;

	bool pressed;

	Color color;

	static Texture* texture;

public:

	Plate(Vector2f position = Vector2f{ 0,0 }, Color color = Color::Red, string textureFile = "Img/Plate.png");
	
	bool isPressed();

	void setPressure(bool pressed);

	void setColor(Color color);

	void draw(RenderWindow& window);

	void reset();
};

