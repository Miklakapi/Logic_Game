#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Spikes : RectangleShape{

	Clock clock;

	static Texture* texture;

	static IntRect* rect;

	bool dmg;

	int stage;

	bool lock;

	int delay;

	enum Direction {
		Up,
		Down
	};

	Direction direction;

public:

	Spikes(Vector2f position = Vector2f{ 0,0 }, string textureFile = "Img/Spikes.png");
	
	void setDelay(int delay);

	bool getDmg();

	void draw(RenderWindow& window);

	void reset();
};

