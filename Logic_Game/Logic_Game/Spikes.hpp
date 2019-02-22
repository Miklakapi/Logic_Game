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

class Spikes : public RectangleShape{

	Clock clock;

	static Texture* texture;

	static IntRect* rect;

	bool dmg;

	int stage;

	enum Direction {
		Up,
		Down
	};

	Direction direction;

	bool on;

public:

	Spikes(Vector2f position = Vector2f{ 0,0 }, string textureFile = "Img/Spikes.png");

	void setOn(bool on);

	bool isOn();

	void run();

	void draw(RenderWindow& window);

	bool run(Player& player);
	
	bool run(SlidingBlock* block, int number);

	bool run(Mirror* mirror, int number);

	void reset();
};

