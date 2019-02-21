#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class TeleportField : public RectangleShape{

	RectangleShape background;

	bool open;

	Color color;

	static Texture* texture;

	Vector2f teleportPlace;

public:

	TeleportField(Vector2f position = Vector2f{ 0,0 }, Color color = Color::Red, string textureFile = "Img/Teleport.png");
	
	void setTeleportPlace(Vector2f position);

	Vector2f getTeleportPlace();

	bool isOpen();

	void setOpen(bool open);

	void draw(RenderWindow& window);

	void reset();
};