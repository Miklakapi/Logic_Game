#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "Spikes.hpp"
#include "Player.hpp"
#include "SlidingBlock.hpp"
#include "Mirror.hpp"

using namespace sf;
using namespace std;

class Traps{

	Spikes* spikes;

	int number;

public:

	Traps(int number, string textureFile = "Img/Spikes.png");

	void setSpikesPosition(int number, Vector2f position);

	void setSpikesSize(int number, Vector2f size);

	void setOn(int number, bool on);

	bool isOn(int number);

	Spikes* getSpikes();

	int getNumber();

	void run(Player& player, SlidingBlock* block, int number, Mirror* mirror, int number2);

	void draw(RenderWindow& window);

	void reset(int number);

	void reset();
	
	~Traps();
};

