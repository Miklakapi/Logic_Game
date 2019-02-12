#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Door : public RectangleShape{

	RectangleShape background;

	bool open;

	Color color;

	static Texture* texture;

public:

	Door(Vector2f position = Vector2f{ 0,0 }, Color color = Color::Red, string textureFile = "Img/Door.png");

	bool isOpen();
	
	void draw(RenderWindow& window);

	void reset();
};

