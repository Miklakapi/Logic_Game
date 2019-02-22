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

class TeleportField : public RectangleShape{

	RectangleShape background;

	bool open;

	static Texture* texture;

	Vector2f teleportPlace;

public:

	TeleportField(Vector2f position = Vector2f{ 0,0 });
	
	static void setTeleportTexture(string textureFile = "Img/Teleport.png");

	void setTeleportPosition(Vector2f position);

	void setTeleportSize(Vector2f size);

	void setTeleportPlace(Vector2f position);

	Vector2f getTeleportPlace();

	void setOpen(bool open);

	void draw(RenderWindow& window);

	void run(Player& player, SlidingBlock* block, int number, Mirror* mirror, int number2);

	void reset();
};