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

	static Texture* texture;

	Clock clock;


public:

	Door();

	static void setDoorTexture(string textureFile = "Img/Door.png");

	void setDoorPosition(Vector2f position);

	void setDoorSize(Vector2f size);

	bool isOpen();
	
	void setOpen(bool open);

	void draw(RenderWindow& window);

	

	void reset();
};

