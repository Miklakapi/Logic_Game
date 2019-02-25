#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "TeleportField.hpp"
#include "Player.hpp"
#include "SlidingBlock.hpp"
#include "Mirror.hpp"

using namespace sf;
using namespace std;

class TeleportFields{

	TeleportField* field;

	int number;

public:
	
	TeleportFields(int number, string textureFile = "Img/Teleport.png");

	void setTeleportPosition(int number, Vector2f position);

	void setTeleportSize(int number, Vector2f size);

	void setTeleportPlace(int number, Vector2f position);

	Vector2f getTeleportPlace(int number);

	bool isOpen(int number);

	void setOpen(int number, bool open);

	TeleportField* getTeleportField();

	int getNumber();

	void draw(RenderWindow& window);

	void run(Player& player, SlidingBlock* block, int number, Mirror* mirror, int number2);

	void reset(int number);

	void reset();

	~TeleportFields();
};

